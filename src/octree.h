#ifndef BIGROCK_OCTREE
#define BIGROCK_OCTREE

#include <stdint.h>

#include "vector3.h"

namespace bigrock
{
    // Creating custom OctreePoint types
    //
    // To use a custom class for OctreePoint, the class needs the following methods:
    // A default constructor : Type()
    // A copy constructor : Type(const Type &other)
    // An interpolation method : Type interpolate(const Type &other, float t)
    // A method for checking collapsability : bool can_collapse(const Type &other)
    // (Basically, if two Points are similar enough that they can be acceptably truncated into one)

    static const Vector3 CUBE_VERTICES[8] = { // Vertices of a cube, organized for bitwise operations
        Vector3(0,0,0), // 0 : 0000 0000
        Vector3(1,0,0), // 1 : 1000 0000
        Vector3(0,1,0), // 2 : 0100 0000
        Vector3(1,1,0), // 3 : 1100 0000
        Vector3(0,0,1), // 4 : 0010 0000
        Vector3(1,0,1), // 5 : 1010 0000
        Vector3(0,1,1), // 6 : 0110 0000
        Vector3(1,1,1)  // 7 : 1110 0000
    };

    template <class PointType>
    class Octree;

    template <class PointType>
    class Octant
    {
    protected:
        Octant() {}; // Dont use this

        // Performance variables (Not required for rebuilding the Octree, dont serialize these)
        unsigned short depth;

        Vector3 relative_position; // Vector3 containing position relative to the Octree's size ( (0,0,0) to (1,1,1) )

        Octree<PointType> *root;
        Octant<PointType> *parent;

        // Required variables (Save these for reconstructing this Octant)
        bool has_children;
        union
        {
            Octant<PointType> *children[8];
            PointType data;
        };

        Octant(Octant<PointType> *parent, Octree<PointType> *root, uint8_t index, PointType data); // Child constructor
        ~Octant();

        public:

        // Constants
        static const uint16_t MAX_DEPTH = 65535;

        // Methods

        // Collapse child Octants into a single leaf Octant.
        // This method will truncate any unique data in the
        // children without checking. If you dont want to lose
        // distinct data, check can_collapse() beforehand.
        void collapse();

        // Expands this leaf node into 8 child nodes, all
        // carrying the original's data. Does nothing
        // if this node already has children.
        void subdivide();

        // Check if this Octant's children can be acceptably truncated
        // (i.e. all values are the same, isovalues are both above/below isolevel, etc.)
        //
        // Does NOT check grandchildren data.
        bool can_collapse();

        // Attempts to optimize the Octant by truncating similar child Octants into leafs
        void optimize();

        // Returns this Octant's data if it's a leaf, or the lowest leaf at the same position
        // if it's a parent.
        PointType get_data();
        // Tries to find the data at the given position in the Octree.
        // If the Octree isn't detailed enough to reach the target,
        // interpolates between existing data and returns the result.
        PointType get_data(Vector3 target);

        // Sets the data of this leaf Octant. Throws an exception
        // if this Octant is not a leaf.
        void set_data(PointType data);

        // Attempts to emplace data as close as possible to target, and returns the actual position
        // that data was emplaced at.
        Vector3 set_data(Vector3 target, PointType data, unsigned short max_depth=MAX_DEPTH);

        Octant<PointType> *get_child(int index);

        inline Octant<PointType> *get_parent() {return this->parent;}
        inline Octree<PointType> *get_root() {return this->root;}
        inline bool is_leaf_node() {return !this->has_children;}
        inline bool is_root() {return root == this;}

        inline Vector3 get_position()
        {
            return this->relative_position * this->root->size;
        }

        inline Vector3 get_relative_position()
        {
            return this->relative_position;
        }

        inline Vector3 get_size()
        {
            return this->root->size / (1 << (this->depth + 1)); // Fast bit-shift replacing pow(2, depth)
        }

        inline Vector3 get_relative_size()
        {
            return Vector3(1,1,1) / (1 << (this->depth + 1));
        }

        int get_octant_index(Vector3 target);
    };

    template <class PointType>
    class Octree : public Octant<PointType>
    {
        public:
        Octree(Vector3 size, PointType data)
        {
            this->parent = NULL;
            this->root = this;
            this->depth = 0;
            this->has_children = false;
            this->relative_position = Vector3(0,0,0);
            this->data = data;
            this->size = size;
        }

        Octree(Vector3 size) : Octree<PointType>(size, PointType()) {}
        Octree() : Octree<PointType>(Vector3(), PointType()) {}

        Vector3 size; // Used for getting position and size of Octants
    };
}

#include "octree.tpp"

#endif