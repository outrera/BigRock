#include <iostream>

#include "octree.h"
#include "standard_lib.h"

using namespace std;
using namespace bigrock;

int main(int argc, char const *argv[])
{
    try
    {
        Octree<OctreePointLerp<float> > octree(Vector3(3, 3, 3), OctreePointLerp<float>(5.5));
        cout << "Constructed octree" << endl;
        cout << "octree.get_data().data = " << octree.get_data().data << endl;
        cout << "octree.can_collapse() = " << octree.can_collapse() << endl;
        cout << "Performing octree.collapse()" << endl;
        octree.collapse();
        cout << "Completed collapse" << endl;
        cout << "octree.is_leaf_node() = " << octree.is_leaf_node() << endl;
        cout << "Performing octree.subdivide()" << endl;
        octree.subdivide();
        cout << "Completed subdivide" << endl;
        for(int i = 0; i < 8; i++)
        {
            cout << "Child " << i << " data: " << octree.get_child(i)->get_data().data << endl;
            cout << "Child " << i << " has_children: " << !octree.get_child(i)->is_leaf_node() << endl;
            cout << "Child " << i << " size: " << octree.get_size() << endl;
            cout << "Child " << i << " position: " << octree.get_position() << endl;
        }
        cout << "octree.is_leaf_node() = " << octree.is_leaf_node() << endl;
        cout << "octree.can_collapse() = " << octree.can_collapse() << endl; // Crashes silently
        cout << "Performing octree.optimize()" << endl;
        octree.optimize();
        cout << "Completed optimize" << endl;
        return 0;
    }
    catch(const std::exception &e)
    {
        cout << "Exception occurred." << endl;
        cout << e.what() << endl;
        return 1;
    }
}
