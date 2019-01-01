#ifndef BIGROCK_EXCLUDE_STANDARD_DATA // Define this to remove the standard OctreePoint implementations. Useful if you only need custom OctreePoint classes.

#ifndef BIGROCK_STANDARD_DATA_H
#define BIGROCK_STANDARD_DATA_H

#include "octree.h"

namespace bigrock
{
    template <class T>
    struct OctreePointLerp : public OctreePoint // Holds a single variable of the given data type, and attempts to linearly interpolate it.
    { // To use this class, T must have a multiply-by-float operator
        OctreePointLerp<T>(const OctreePointLerp<T> &other);
        OctreePointLerp<T>();
        
        T data;

        OctreePointLerp<T> interpolate(const OctreePointLerp<T> &other, float t); // Linearly interpolate between two OctreePointLerps of the same data type
        bool can_collapse(const OctreePointLerp<T> &other); // If both values are the same, they can be collapsed

        // Conversions
        #ifndef BIGROCK_STD_DISALLOW_CONVERSION // Define this to prevent use of implicit conversions
        OctreePointLerp<T>(const T &from) {this->data = from;}
        operator T() const {return this->data;}
        #endif
    };

    template <class T>
    struct OctreePointNN : public OctreePoint // Holds a single variable of the given data type, and performs nearest-neighbor interpolation.
    { // This class can work with any data type
        OctreePointNN<T>(const OctreePointNN<T> &other);
        OctreePointNN<T>();

        T data;

        OctreePointNN<T> interpolate(const OctreePointNN<T> &other, float t); // Perform nearest-neighbor interpolation
        bool can_collapse(const OctreePointNN<T> &other); // If both values are the same, they can be collapsed

        // Conversions
        #ifndef BIGROCK_STD_DISALLOW_CONVERSION
        OctreePointNN<T>(const T &from) {this->data = from;}
        operator T() const {return this->data;}
        #endif
    };
}

#endif

#endif