#include "octree.h"

namespace bigrock
{
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
            for(int i = 0; i < 8; i++)
                delete children[i];
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
        
        this->has_children = false;
        this->data = new PointType(data);
    }

    template <class PointType>
    void Octant<PointType>::subdivide()
    {
        if(has_children)
            return; // Already subdivided
        
        const PointType data = *this->data; // Copy data so it doesn't get destroyed

        has_children = true;
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
            throw std::logic_error("Attempted to set data of a non-leaf Octant");
        else
            this->data = new PointType(data);
    }

    template <class PointType>
    Vector3 Octant<PointType>::set_data(Vector3 target, PointType data, unsigned short max_depth)
    {
        Octant<PointType> *current_octant = this;
        Vector3 offset = current_octant->get_position();
        while(target != offset && (current_octant->depth < max_depth))
        {
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
    Octant<PointType> *Octant<PointType>::get_child(int index)
    {
        if(!has_children)
            throw std::logic_error("Attempted to get child of leaf octant");
        else if(index < 0 || index > 7)
            throw std::logic_error("Attempted to get child out of bounds from octant");
        
        return children[index];
    }

    template <class PointType>
    int Octant<PointType>::get_octant_index(Vector3 target)
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
}