#include <iostream>

#include "octree.h"
#include "standard_lib.h"
#include "shape.h"

using namespace std;
using namespace bigrock;

template <class T>
void print_octree(const Octant<T> &octant, ostream &out)
{
    if(octant.is_leaf_node())
    {
        out << "Octant(";
        out << "size:" << octant.get_size() << ", ";
        out << "position:" << octant.get_position() << ", ";
        out << "data:" << octant.get_data() << ")";
    }
    else
    {
        for(int i = 0; i < 8; i++)
        {
            Octant<T> *child = octant.get_child(i);
            print_octree(*child, out);
        }
    }
}

int main(int argc, char const *argv[])
{
    Octree<OctreePointLerp<float> > octree(Vector3(64,64,64), -1.0);
    Sphere data_sphere(Vector3(0,0,0), 12);
    int max_depth = 5;
    float data = 3.2;

    cout << "Emplacing data..." << endl;
    octree.apply_shape_data(data_sphere, data, max_depth);
    cout << "Emplace finished. Optimizing..." << endl;
    //octree.optimize();
    cout << "Optimized. Printing resulting octree..." << endl << endl;
    cout << "Octree.is_leaf_node() = " << octree.is_leaf_node() << endl;

    print_octree(octree, cout);

    return 0;
}
