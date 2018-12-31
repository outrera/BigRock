#include "octree.h"

namespace bigrock
{
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
    PointType get_data_at_position(Vector3 target, int max_depth = -1)
    {
        #ifdef BIGROCK_OCTREE_CHECK_BOUNDS
        Vector3 position = this->get_position();
        Vector3 size = this->get_size();
        Vector3 bounds = position + size;
        if (target.x > bounds.x || target.y > bounds.y || target.z > bounds.z || target.x < position.x || target.y < position.y || target.z < position.z)
            throw std::logic_error("attempted to get data at position outside of Octant bounds");
        #endif

        Octant *current_octant = this; // Start here
        while(current_octant->has_children && (max_depth == -1 || current_octant->depth < max_depth))
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
        
    }
}