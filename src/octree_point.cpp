#include "octree_point.h"

namespace bigrock
{
    OctreePoint::OctreePoint() {}
    OctreePoint::OctreePoint(const OctreePoint &other) {}

    OctreePoint OctreePoint::interpolate(const OctreePoint &other, float t)
    {
        if(t > 0.5)
            return *this;
        else
            return other;
    }

    bool OctreePoint::can_collapse(const OctreePoint &other) const
    {
        return true; // Returns true since these hold no data. MAKE SURE TO OVERRIDE THIS!
    }
}