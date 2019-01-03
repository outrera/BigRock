#include "octree_point.h"
#include <iostream>

using namespace std;
using namespace bigrock;

int main(int argc, char const *argv[])
{
    cout << "Octree Point Test (no Octree)" << endl;
    OctreePoint o;
    cout << "Constructed OctreePoint. (No print representation)" << endl;
    OctreePoint other;
    cout << "Performing pointless interpolation" << endl;
    OctreePoint third = other.interpolate(o, 0.7);
    cout << "Interpolated" << endl;
    cout << "Checking can_collapse between other and third" << endl;
    cout << "Result is " << other.can_collapse(third) << endl;
    return 0;
}
