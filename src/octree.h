#ifndef BIGROCK_OCTREE_H
#define BIGROCK_OCTREE_H

#include <cstdint>

#include "vector3.h"

namespace bigrock
{
    struct OctantData
    {
        float value;
        int material_index;

        static OctantData trilinear_interpolate(Vector3 positions[8], OctantData values[8], Vector3 target);
    };

    // A child of either the octree itself or another octant
    class Octant
    {
        protected:
        uint8_t depth; // 0-511
        OctantData *data; // The data of this leaf node, if it has no children

        Octree *root; // The root octree that this node is under
        Octant *children[8]; // The 8 corners of the children of this octant, if they exist
        Octant *parent; // The parent of this octant, or nullptr if the parent is the root
        
        public:
        bool is_leaf_node(); // Check if this octant has children
        Vector3 get_size(); // Divide the root's size by (depth + 1)
        Vector3 get_position(); // Start from root, check octant position, add the offset of the octant and move down until this octant is reached
        OctantData get_data(); // Return the data of this octant if this is a leaf, otherwise move down until you find a leaf
    };

    // The root of the octree, contains all octants and handles size
    class Octree
    {
        protected:
        Vector3 size; // The overall size of this octree. This is subdivided per depth level.
    };
}

#endif