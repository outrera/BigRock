#ifndef BIGROCK_OCTREE_POINT_H
#define BIGROCK_OCTREE_POINT_H

namespace bigrock
{
    struct OctreePoint // Data container used for point interpolation in the octree. Extend this for custom data
    {
        // Constructors
        OctreePoint(); // Default constructor
        OctreePoint(const OctreePoint &other); // Copy constructor

        // Methods
        virtual OctreePoint interpolate(const OctreePoint &other, float t); // Override this for custom interpolation of objects. By default performs nearest-neighbor interpolation
        virtual bool can_collapse(const OctreePoint &other) const; // Check if these OctreePoints are similar enough to be collapsed into one. Override for checking if data is similar, or if two scalars are above/below an isolevel, etc.
    };
}

#endif