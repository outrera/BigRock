#include "octree.h"
#include <assert.h>

namespace bigrock
{
    #pragma region Octant
    template <class PointType>
    Octant<PointType>::Octant(Octant<PointType> *parent, Octree<PointType> *root, uint16_t depth, PointType data)
    {
        this->parent = parent;
        this->root = root;
        this->depth = depth;
        this->has_children = false;
        this->data = data;
    }

    template <class T>
    int Octant<T>::get_octant_index()
    {
        if (parent == nullptr)
            return 0;
        else
        {
            for(int i = 0; i < 8; i++)
            {
                if(parent->children[i] == this)
                    return i;
            }
            throw std::runtime_error("parent does not contain child octant");
        }
    }

    template <class T>
    int Octant<T>::get_octant_index_containing_position(Vector3 target)
    {
        Vector3 pos = get_position();
        Vector3 size = get_size();
        #ifdef BIGROCK_OCTREE_CHECK_BOUNDS
        Vector3 bounds = pos + size;
        if(target.x > bounds.x || target.y > bounds.y || target.z > bounds.z)
            return -1;
        else if(target.x < pos.x || target.y < pos.y || target.z < pos.z)
            return -1;
        else
        {
        #endif

        int index = 0;
        if(target.x >= pos.x + (size.x / 2))
            index |= 1;
        if(target.y >= pos.y + (size.y / 2))
            index |= 2;
        if(target.z >= pos.z + (size.z / 2))
            index |= 4;
        return index;

        #ifdef BIGROCK_OCTREE_CHECK_BOUNDS
        }
        #endif
    }

    template <class PointType>
    Octant<PointType> *Octant<PointType>::get_child(int index)
    {
        if(!this->has_children)
            throw std::logic_error("attempted to get the child of a leaf octree")
        if(index < 0 || index > 7)
            throw std::logic_error("attempted to get a child of an octree out of index bounds")
        
        return this->children[index];
    }

    template <class PointType>
    PointType Octant<PointType>::get_data()
    {
        if(!this->has_children)
            return this->data;
        else
        { // Iteratively step down children until the leaf is found
            Octant *current_octant = children[0];
            while(!current_octant->is_leaf_node())
                current_octant = current_octant->children[0];
            return current_octant->data;
        }
    }

    template <class PointType>
    void Octant<PointType>::set_data(PointType data)
    {
        if(!this->has_children)
        {
            this->data = data;
        }
        else
        {
            Octant *current_octant = children[0];
            while(!current_octant->is_leaf_node())
                current_octant = current_octant->children[0];
            current_octant->data = data;
        }
    }

    template <class PointType>
    PointType Octant<PointType>::get_data_at_position(Vector3 target, int max_depth)
    {
        #ifdef BIGROCK_OCTREE_CHECK_BOUNDS
        Vector3 position = this->get_position();
        Vector3 size = this->get_size();
        Vector3 bounds = position + size;
        if (target.x > bounds.x || target.y > bounds.y || target.z > bounds.z || target.x < position.x || target.y < position.y || target.z < position.z)
            throw std::logic_error("attempted to get data at position outside of Octant bounds");
        #endif

        if(max_depth < 0 || max_depth > MAX_DEPTH)
            max_depth = MAX_DEPTH;

        Octant *current_octant = this; // Start here
        while(current_octant->has_children && (current_octant->depth < max_depth))
        {
            int next_index = current_octant->get_octant_index_containing_position(target);
            current_octant = current_octant->get_child(next_index);
        }
        // Check if the current position is the target
        Vector3 pos = current_octant->get_position();

        if(pos == target)
        {
            return current_octant->get_data();
        }
        else // Trilinearly interpolate the data
        {
            Octant *grid = current_octant->get_parent(); // Use the parent as a grid, since it contains the point and has 8 corners
            
            Vector3 start = grid->children[0]->get_position(); // (0,0,0)
            Vector3 end = grid->children[7]->get_position(); // (1,1,1)
            Vector3 t = (end - start) * (target - start); // Relative position within grid

            // First, interpolate on the 4 X edges
            PointType x_edges[4];
            for(int i = 0; i < 4; i++)
                x_edges[i] = grid->children[i*2]->get_data().interpolate(grid->children[(i*2)|1]->get_data(), t.x);

            // Now, interpolate the 2 Y edges from the 4 X edges
            PointData y_edges[2];
            for(int i = 0; i < 2; i++)
                y_edges[i] = x_edges[i].interpolate(x_edges[i+1], t.y);

            // Finally, interpolate on the Z edge
            PointData z_edge = y_edges[0].interpolate(y_edges[1], t.z);
            return z_edge;
        }
    }

    template <class T>
    Vector3 Octant<T>::get_position()
    {
        // Traverse up this Octant until the root is reached, adding to the offset as we go
        Vector3 offset;
        Octant *current_octant = this;
        while(current_octant != root)
        {
            offset += current_octant->size * CUBE_VERTICES[current_octant->get_octant_index()];
        }
        return offset;
    }

    template <class PointType>
    Vector3 Octant<PointType>::get_closest_data_at_position(Vector3 target, PointType &out, int max_depth = -1)
    {
        #ifdef BIGROCK_OCTREE_CHECK_BOUNDS
        Vector3 position = this->get_position();
        Vector3 size = this->get_size();
        Vector3 bounds = position + size;
        if (target.x > bounds.x || target.y > bounds.y || target.z > bounds.z || target.x < position.x || target.y < position.y || target.z < position.z)
            throw std::logic_error("attempted to get data at position outside of Octant bounds");
        #endif

        if(max_depth < 0 || max_depth > MAX_DEPTH)
            max_depth = MAX_DEPTH;
        
        Octant *current_octant = this;
        Vector3 offset = this->get_position();
        while(current_octant->has_children && (current_octant->depth < max_depth))
        {
            int next_index = current_octant->get_octant_index_containing_position(target);
            offset += (current_octant->get_size() / 2) * CUBE_VERTICES[next_index];
            current_octant = current_octant->children[next_index];
        }
        out = PointType(current_octant->get_data());

        #ifndef NDEBUG
        assert(offset == current_octant->get_position()) // Debug assertion
        #endif

        return offset;
    }

    template <class PointType>
    Vector3 Octant<PointType>::set_data_at_position(Vector3 target, PointType data, int max_depth = -1)
    {
        #ifdef BIGROCK_OCTREE_CHECK_BOUNDS
        Vector3 position = this->get_position();
        Vector3 size = this->get_size();
        Vector3 bounds = position + size;
        if (target.x > bounds.x || target.y > bounds.y || target.z > bounds.z || target.x < position.x || target.y < position.y || target.z < position.z)
            throw std::logic_error("attempted to get data at position outside of Octant bounds");
        #endif

        if(max_depth < 0 || max_depth > MAX_DEPTH)
            max_depth = MAX_DEPTH;

        Octant *current_octant = this;
        Vector3 offset = this->get_position();
        // Go down existing children
        while(current_octant->has_children && (current_octant->depth < max_depth))
        {
            int next_index = current_octant->get_octant_index_containing_position(target);
            offset += (get_size() / 2) * CUBE_VERTICES[next_index];
            current_octant = current_octant->children[next_index];
        }
        if(offset == target || current_octant->get_data().can_collapse(data))
            // Either we are at the target, or the data is acceptably similar for collapse
            current_octant->set_data(data);
            // Since we didnt have to subdivide, check if collapse can be done
        else
        {
            while(offset != target && (current_octant->depth < max_depth))
            {
                current_octant->subdivide();
                int next_index = current_octant->get_octant_index_containing_position(target);
                offset += (current_octant->get_size() / 2) * CUBE_VERTICES[next_index];
                current_octant = current_octant->children[next_index];
            }
            // We've either reached the target or the max depth. Set the data
            current_octant->data = data;
        }

        #ifndef NDEBUG
        assert(offset == current_octant->get_position()) // Debug assertion
        #endif

        return offset;
    }

    template <class PointType>
    void Octant<PointType>::collapse()
    { // TODO: Make this iterative instead of recursive
        if(!this->has_children)
            return; // Already a leaf, no collapse required
        
        PointType data = children[0]->data;

        for(int i = 0; i < 8; i++)
        {
            children[i]->collapse();
            delete children[i];
        }
        has_children = false;
        this->data = data;
    }

    template <class PointType>
    void Octant<PointType>::subdivide()
    {
        if (this->has_children)
            return; // Already subdivided
        
        PointType data = this->data;
        this->has_children = true;
        
        for(int i = 0; i < 8; i++)
        {
            children[i] = new Octant<PointType>(this, root, this->depth + 1, data);
        }
    }

    template <class PointType>
    bool Octant<PointType>::can_collapse()
    { // TODO: Make this iterative instead of recursive
        if(this->has_children)
        {
            bool collapse = true;
            // We need to check if the 8 children this octant has can be turned into one
            for(int i = 0; collapse && i < 8; i++)
            {
                // First, if the child isn't a leaf node, recursively check if it can collapse.
                if(!children[i]->is_leaf_node())
                {
                    collapse = collapse && children[i]->can_collapse();
                }
                else if(i > 0)
                { // If the child is a leaf, and it isn't the first octant, check if it's collapsable against the previous node
                    collapse = collapse && children[i]->data.can_collapse(children[i-1]->get_data());
                    // We can skip i=0 because collapsability is transient.
                    // If i=0 is collapsable with i=1, and i=1 is collapsable
                    // with i=2, then it can be assumed that i=0 is collapsable
                    // with i=2.
                }
            }
            return collapse;
        }
        else
        {
            return false; // Can't collapse, already collapsed
        }
    }

    template <class PointType>
    void Octant<PointType>::optimize(bool optimize_children=true)
    { // TODO: Make this iterative instead of recursive
        if(optimize_children && this->has_children)
        {
            bool collapseable = true;
            for(int i = 0; collapseable && i < 8; i++)
            {
                if(children[i]->can_collapse())
                {
                    children[i]->collapse();
                }
                else
                {
                    collapseable = collapseable && !children[i]->has_children;
                }
            }
        }
        else
        {
            if(this->can_collapse())
                this->collapse();
        }
    }
    #pragma endregion

    #pragma region Octree

    template <class PointType>
    Octree<PointType>::Octree(Vector3 size, PointType default_data)
    {
        this->size = size;
        this->data = data;
    }

    template <class PointType>
    Octree<PointType>::Octree(Vector3 size) : Octree(size, PointType()) {}

    template <class PointType>
    Octree<PointType>::Octree() : Octree(Vector3(1,1,1), PointType()) {}

    #pragma endregion
}