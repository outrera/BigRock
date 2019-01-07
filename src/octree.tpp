#include "octree.h"

namespace bigrock
{
    #pragma region Octant
    template <class PointType>
    Octant<PointType>::Octant(Octant<PointType> *parent, Octree<PointType> *root, uint8_t index, PointType data)
    {
        this->data = new PointType(data);
        this->parent = parent;
        this->root = root;
        this->depth = parent->depth + 1;
        this->has_children = false;
        this->relative_position = parent->relative_position + (CUBE_VERTICES[index] / (1 << depth));
    }

    template <class PointType>
    Octant<PointType>::~Octant()
    {
        if(has_children)
        {
            for(int i = 0; i < 8; i++)
                delete children[i];
            delete [] children;
        }
        else
            delete data;
    }

    template <class PointType>
    void Octant<PointType>::collapse()
    {
        if (!has_children)
            return;
        
        PointType data = children[0]->get_data();
        
        for(int i = 0; i < 8; i++)
            delete children[i];
        
        delete [] children;
        
        this->has_children = false;
        this->data = new PointType(data);
    }

    template <class PointType>
    void Octant<PointType>::subdivide()
    {
        if(has_children)
            return; // Already subdivided
        
        const PointType data = *this->data; // Copy data so it doesn't get destroyed
        
        delete this->data;

        has_children = true;
        children = new Octant<PointType>*[8];
        for(int i = 0; i < 8; i++)
        {
            children[i] = new Octant<PointType>(this, this->root, i, data);
        }
    }

    template <class PointType>
    bool Octant<PointType>::can_collapse()
    {
        if (!has_children)
            return false; // Already collapsed!
        
        bool collapse = true;
        PointType refdata = children[0]->get_data(); // Check this against all other data
        for(int i = 1; collapse && i < 8; i++)
        {
            collapse = collapse && refdata.can_collapse(children[i-1]->get_data()); // Check if this point can collapse to the previous point
                // Ideally, collapsability should be transitive. If a can collapse with b, and b can collapse
                // with c, then a should be able to collapse with c.
        }

        return collapse;
    }

    template <class PointType>
    void Octant<PointType>::optimize()
    {
        if(has_children)
        {
            bool should_collapse = true;
            for(int i = 0; i < 8; i++)
            {
                if(children[i]->has_children)
                    children[i]->optimize(); // TODO: See if this can be made iterative?
                
                should_collapse = should_collapse && !children[i]->has_children; // If the children didn't collapse, optimize won't collapse the parent
            }

            if(should_collapse && this->can_collapse())
                this->collapse();
        }
    }

    template <class PointType>
    PointType Octant<PointType>::get_data()
    {
        if(this->has_children)
        {
            Octant<PointType> *current_octant = this;

            while(current_octant->has_children)
                current_octant = current_octant->children[0];
            
            return current_octant->get_data();
        }
        else
        {
            return *this->data;
        }
    }

    template <class PointType>
    PointType Octant<PointType>::get_data(Vector3 target)
    {
        if(!has_children) // Can't do anything, returns own data
            return this->data;
        else
        { // Iteratively step through children
            Octant<PointType> *current_octant = this;
            while(current_octant->has_children)
            {
                int next_index = current_octant->get_octant_index();
                current_octant = current_octant->get_child(next_index);
            }

            // We've gone as low as we can
            return *current_octant->data;
        }
    }

    template <class PointType>
    void Octant<PointType>::set_data(PointType data)
    {
        if(has_children)
        {
            Octant<PointType> *current_octant = this->children[0];
            while(current_octant->has_children)
                current_octant = current_octant->children[0];
            current_octant->data = data;
        }
        else
            this->data = new PointType(data);
    }

    template <class PointType>
    Vector3 Octant<PointType>::set_data(Vector3 target, PointType data, unsigned short max_depth)
    {
        Octant<PointType> *current_octant = this;
        Vector3 offset = current_octant->get_position();
        while(target != offset && (current_octant->depth < max_depth))
        { // TODO: Replace Vector3 == Vector3 operations with something more approximate
            if(!current_octant->has_children)
                current_octant->subdivide();
            
            int next = current_octant->get_octant_index(target);
            offset += current_octant->get_size() * CUBE_VERTICES[next];
            current_octant = current_octant->children[next];
        }

        while(current_octant->has_children)
            current_octant = current_octant->children[0];
        
        current_octant->set_data(data);
        return offset;
    }

    template <class PointType>
    Octant<PointType> *Octant<PointType>::get_child(int index) const
    {
        if(!has_children)
            throw std::logic_error("Attempted to get child of leaf octant");
        else if(index < 0 || index > 7)
            throw std::logic_error("Attempted to get child out of bounds from octant");
        
        return children[index];
    }

    template <class PointType>
    int Octant<PointType>::get_octant_index(Vector3 target) const
    {
        int cube_index = 0;

        Vector3 position = this->get_position();
        Vector3 half_size = this->get_size() / 2;

        Vector3 mid_point = position + half_size;

        if(target.x > mid_point.x)
            cube_index |= 1;
        if(target.y > mid_point.y)
            cube_index |= 2;
        if(target.z > mid_point.z)
            cube_index |= 4;
        
        return cube_index;
    }

    template <class PointType>
    bool Octant<PointType>::intersects_point(const Vector3 &point) const
    {
        Rectangle oct_shape(this->get_position(), this->get_size());

        return oct_shape.point_intersects(point);
    }

    template <class PointType>
    bool Octant<PointType>::intersects_shape(const Shape &shape) const
    {
        Rectangle oct_shape(this->get_position(), this->get_size());

        return oct_shape.interacts_with_shape(shape);
    }

    template <class PointType>
    unsigned char Octant<PointType>::get_intersecting_children(const Shape &shape) const
    {
        if(!this->has_children)
            return 0;
        
        char val = 0;
        
        for(int i = 0; i < 8; i++)
        {
            if(children[i]->intersects_shape(shape))
                val |= (1 << i);
        }
        
        return val;
    }

    template <class PointType>
    unsigned int Octant<PointType>::query_shape(const Shape &shape, std::vector<Octant<PointType>*> &octants, const unsigned short max_depth)
    {
        if (!this->has_children)
            return 0;

        std::vector<Octant<PointType>*> octants;
        Rectangle oct_shape(this->get_position(), this->get_size());

        if (!root->intersects_shape(oct_shape)) // Shape does not intersect with Octant
            return 0;
        
        int oct_count = 0;
        for(int i = 0; i < 8; i++)
        {
            if(children[i]->has_children)
                oct_count += children[i]->query_shape(shape, octants, max_depth);
            else if(children[i]->intersects_shape(shape))
            {
                octants.push_back(children[i]);
                oct_count += 1;
            }
        }
        return oct_count;
    }

    template <class PointType>
    void Octant<PointType>::apply_shape_data(const Shape &shape, const PointType &data, unsigned short subdiv_depth)
    {
        if(!this->has_children || this->depth >= max_depth)
        {
            if(this->intersects_shape(shape))
                this->set_data(data);
            return;
        }

        if(!this->intersects_shape(shape))
            return;

        if(depth + 1 < max_depth)
        {
            for(int i = 0; i < 8; i++)
            {
                if(children[i]->intersects_shape(shape))
                {
                    if(depth + 2 < max_depth)
                        children[i]->subdivide();

                    children[i]->apply_shape_data(shape, data, max_depth);
                }
            }
        }
        else
        {
            for(int i = 0; i < 8; i++)
            {
                if(children[i]->intersects_shape(shape))
                    children[i]->set_data(data);
            }
        }
    }

    #pragma endregion // Octant

    #pragma region Octree
    template <class PointType>
    Octree<PointType>::Octree(Vector3 size, PointType data)
    {
        this->parent = NULL;
        this->root = this;
        this->depth = 0;

        this->has_children = false;
        this->data = new PointType(data);

        this->relative_position = Vector3(0,0,0);
        this->size = size;
    }

    template <class PointType>
    Octree<PointType>::Octree(Vector3 size)
    {
        this->parent = NULL;
        this->root = this;
        this->depth = 0;

        this->has_children = false;
        this->data = new PointType();

        this->size = size;
        this->relative_position = Vector3(0,0,0);
    }

    template <class PointType>
    Octree<PointType>::Octree()
    {
        this->parent = NULL;
        this->root = this;
        this->depth = 0;
        
        this->has_children = false;
        this->data = new PointType();
        
        this->size = Vector3(1,1,1);
        this->relative_position = Vector3(0,0,0);
    }

    #pragma endregion // Octree
}