#ifndef BIGROCK_STANDARD_LIB
#define BIGROCK_STANDARD_LIB

namespace bigrock
{
    template <class T>
    struct OctreePointNearest // Uses nearest-neighbor interpolation, supports any data type
    {
        OctreePointNearest() {data = T();}
        OctreePointNearest(const OctreePointNearest &other) {this->data = other.data;}
        OctreePointNearest(const T &data) {this->data = data;}

        T data;

        OctreePointNearest interpolate(const OctreePointNearest &other, float t)
        {
            if(t > 0.5)
                return OctreePointNearest<T>(other);
            else
                return OctreePointNearest<T>(*this);
        }

        bool can_collapse(const OctreePointNearest &other)
        {
            return other.data == this->data;
        }

        operator T() {return data;}
    };

    template <class T>
    struct OctreePointLerp // Attempts to use linear interpolation. Requires a data type that can be multiplied by a scalar and added/subtracted by itself.
    {
        OctreePointLerp() {data = T();}
        OctreePointLerp(const OctreePointLerp<T> &other) {this->data = other.data;}
        OctreePointLerp(const T &data) {this->data = data;}

        T data;

        OctreePointLerp<T> interpolate(const OctreePointLerp<T> &other, float t)
        {
            if(t <= 0)
                return *this;
            else if(t >= 1)
                return other;
            else
            {
                return this->data + ((other.data - this->data) * t);
            }
        }

        bool can_collapse(const OctreePointLerp<T> &other)
        {
            return this->data == other.data;
        }

        operator T() {return data;}
    };
}

#endif