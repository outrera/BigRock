#include "standard_lib.h"

#include <iostream>
#include "vector3.h"

using namespace std;
using namespace bigrock;

int main(int argc, char const *argv[])
{
    cout << "BigRock Standard Library Test" << endl;
    cout << "OctreePointNearest<Vector3>" << endl;
    OctreePointNearest<Vector3> near_vec3(Vector3(5, 5, 5));
    cout << "Constructed. Data: " << near_vec3.data << endl;
    OctreePointNearest<Vector3> near_vec3_2(Vector3(-5, -3, 4));
    cout << "Second point constructed. Data: " << near_vec3_2.data << endl;
    cout << "Checking collapse between two points" << endl;
    cout << "near_vec3.can_collapse(near_vec3_2) == " << near_vec3.can_collapse(near_vec3_2) << endl;
    cout << "near_v3c.interpolate(near_vec3_2, 0.7).data == " << near_vec3.interpolate(near_vec3_2, 0.7).data << endl;
    cout << endl;
    cout << "OctreePointLerp<Vector3>" << endl;
    OctreePointLerp<Vector3> lerp_vec3(Vector3(5,5,5));
    OctreePointLerp<Vector3> lerp_vec3_2(Vector3(-5, -3, 4));
    cout << "Constructed. Data: " << lerp_vec3.data << endl;
    cout << "Second point constructed. Data: " << lerp_vec3_2.data << endl;
    cout << "lerp_vec3.can_collapse(lerp_vec3_2) == " << lerp_vec3.can_collapse(lerp_vec3_2) << endl;
    cout << "lerp_vec3.interpolate(lerp_vec3_2, 0.7).data == " << lerp_vec3.interpolate(lerp_vec3_2, 0.7).data << endl;
    return 0;
}
