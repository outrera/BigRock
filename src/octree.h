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
        OctreePoint() {};
        OctreePoint(const OctreePoint &other) {}; // Copy constructor

        virtual OctreePoint interpolate(const OctreePoint &other, float t) // Return a new OctreePoint class representing the point t between this and other.
        {
            if(t > 0.5)
                return other;
            else
                return *this;
        }
        
        virtual bool can_collapse(const OctreePoint &other) {return true;}; // Check if two OctreePoints are similar enough to be collapsed into one. I.E. two boolean Points are the same, or two float values are both above/below the isolevel.
        // By default returns true, just override this
    };

    template <class PointType>
    class Octree;

    template <class PointType> // PointType should be a class that extends OctreePoint
    class Octant
    {
    protected:
        // In-memory variables, can be calculated at init and don't need to be serialized
        uint16_t depth; // Max depth: 65,535
        
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

        // Collapse child octants into single leaf octant
        // This method will truncate any unique data in the
        // children without checking. If you want to safely
        // collapse the Octant, call can_collapse() before
        // this.
        void collapse();

        void subdivide(); // Split octant into 8 octants

        bool can_collapse(); // Checks if any of this octree's children has unique point data.

        Octant(Octant<PointType> *parent, Octree<PointType> *root, uint16_t depth, PointType data); // Child constructor

        public:
        const uint16_t MAX_DEPTH = 65535;

        inline bool is_leaf_node() {return !has_children;}
        inline bool is_root_node() {return this == root;}
        
        // Attempts to collapse this octant and all of its children.
        //
        // If optimize_children is true, it will step through its children and attempt
        // to collapse them individually before attempting to collapse this octant.
        // That way, even if this octant can't be optimized, some of it's children
        // might be.
        void optimize(bool optimize_children=true);

        int get_octant_index(); // Get this octant's index in the parent octant, or 0 if this is the root
        int get_octant_index_containing_position(Vector3 target); // Get the octant this point is contained in, or -1 if the point is outside of bounds

        Octant *get_child(int index);
        inline Octant *get_parent() {return this->parent;} // Return the parent of this octant
 
        PointType get_data(); // Returns the data in this octant if it's a leaf, or the data of child[0] if it's a parent
        void set_data(PointType data);

        virtual Vector3 get_size() {return root->get_size() / (depth + 2);}
        virtual Vector3 get_position();

        // Iteratively moves down this Octant's children and gets the value (interpolated if max_depth is reached)
        // If max_depth is -1, keep going until a leaf node is reached, THEN interpolate if needed
        PointType get_data_at_position(Vector3 target, int max_depth = -1);

        // Same as get_data_at_position, but simply does nearest-neighbor interpolation instead of
        // attempting trilinear interpolation.
        Vector3 get_closest_data_at_position(Vector3 target, PointType &out, int max_depth = -1);

        // Iteratively moves down this Octant's children until either the target position is reached or the max depth
        // is reached. Sets the data at the lowest position and returns the actual position of the set data.
        Vector3 set_data_at_position(Vector3 target, PointType data, int max_depth = -1);
    };

    template <class PointType>
    class Octree : public Octant<PointType>
    {
    protected:
        Vector3 size;

    public:
        Octree(Vector3 size, PointType default_data); // Root constructor
        Octree(Vector3 size);
        Octree();

        inline Vector3 get_size() {return this->size;}
        inline void set_size(Vector3 size) {this->size = size;}

        inline Vector3 get_position() {return Vector3();} // Root nodes are always at {0,0,0}
    };
}

#endif