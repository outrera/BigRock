#ifndef BIGROCK_OCTREE_H
#define BIGROCK_OCTREE_H

#include <stdint.h>
#include "vector3.h"

namespace bigrock
{
    const Vector3 CUBE_VERTICES[8] = {
        Vector3(0,0,0),
        Vector3(1,0,0),
        Vector3(0,1,0),
        Vector3(1,1,0),
        Vector3(0,0,1),
        Vector3(1,0,1),
        Vector3(0,1,1),
        Vector3(1,1,1)
    };

    struct OctreePoint // Abstract class, extend for custom data
    {
        // Constructors
        OctreePoint();
        OctreePoint(const OctreePoint &other); // Copy constructor

        virtual OctreePoint *interpolate(const OctreePoint *other, float t) = 0; // Return a new OctreePoint class representing the point t between this and other.
        virtual bool can_collapse(const OctreePoint *other); // Check if two OctreePoints are similar enough to be collapsed into one. I.E. two boolean Points are the same, or two float values are both above/below the isolevel.
    };

    template <class PointType>
    class Octree;

    template <class PointType> // PointType should be a class that extends OctreePoint
    class Octant
    {
    protected:
        // In-memory variables, can be calculated at init and don't need to be serialized
        uint16_t depth; // Max depth: 65,535
        char index; // byte, not char. This is the index of this Octant in the parent.
        
        Octree<PointType> *root;
        Octant<PointType> *parent;

        // Serialized variables, needed for proper initialization
        bool has_children; // Tag for the union
        union
        {
            Octant<PointType> *children[8]; // has_children == true
            PointType data; // has_children == false
        };

        // Methods
        void collapse(); // Collapse child octants into single leaf octant
        void subdivide(); // Split octant into 8 octants

        public:
        inline bool is_leaf_node() {return !has_children;}
        inline bool is_root_node() {return this == root;}

        int get_octant_index(); // Get this octant's index in the parent octant, or 0 if this is the root
        int get_octant_index_containing_position(Vector3 target); // Get the octant this point is contained in, or -1 if the point is outside of bounds

        Octant *get_child(int index);
        inline Octant *get_parent() {return this->parent;} // Return the parent of this octant
        PointType get_data(); // Returns the data in this octant if it's a leaf, or the data of child[0] if it's a parent

        virtual Vector3 get_size() {return root->get_size() / (depth + 2);}
        virtual Vector3 get_position();

        // Iteratively moves down this Octant's children and gets the value (interpolated if max_depth is reached)
        // If max_depth is -1, keep going until a leaf node is reached, THEN interpolate if needed
        PointType get_data_at_position(Vector3 target, int max_depth = -1);
    };

    template <class PointType>
    class Octree : public Octant<PointType>
    {
    protected:
        Vector3 size;

    public:
        Vector3 get_size() {return this->size;}
        Vector3 get_position() {return Vector3();} // Root nodes are always at {0,0,0}
    };
}

#endif