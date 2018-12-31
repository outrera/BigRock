#ifndef BIGROCK_EXCLUDE_STANDARD_DATA

#include "standard_data.h"

namespace bigrock
{
    template <class T>
    OctreePointLerp<T>::OctreePointLerp(const OctreePointLerp<T> &other)
    {
        this->data = other.data;
    }

    template <class T>
    OctreePointLerp<T> OctreePointLerp<T>::interpolate(const OctreePointLerp<T> &other, float t)
    {
        OctreePointLerp<T> ret;

        if(t <= 0.0)
            ret.data = this->data;
        else if(t >= 1.0)
            ret.data = other.data;
        else
        {
            T difference = other.data - this->data; // The difference between this and other's data
            ret.data = this->data + (difference * t);
        }

        return ret;
    }

    template <class T>
    bool OctreePointLerp<T>::can_collapse(const OctreePointLerp<T> &other)
    {
        return this->data == other.data;
    }

    template <class T>
    OctreePointNN<T>::OctreePointNN(const OctreePointNN<T> &other)
    {
        this->data = other.data;
    }

    template <class T>
    OctreePointNN<T> OctreePointNN<T>::interpolate(const OctreePointNN<T> &other, float t)
    {
        if(t > 0.5)
            return OctreePointNN<T>(other);
        else
            return OctreePointNN<T>(*this);
    }

    template <class T>
    bool OctreePointNN<T>::can_collapse(const OctreePointNN<T> &other)
    {
        return this->data == other.data;
    }
}

#endif