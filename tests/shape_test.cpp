#include "vector3.h"
#include "shape.h"

#include <iostream>

using namespace std;
using namespace bigrock;

int main(int argc, char const *argv[])
{
    cout << "Shape test" << endl;
    Sphere s;
    s.radius = 5;
    cout << "Created sphere with radius " << s.radius << " at position " << s.position << endl;
    cout << "Checking point intersection" << endl;
    Vector3 p1(1.5, 1.5, 1);
    cout << p1 << " intersects: " << s.point_intersects(p1) << endl;
    Vector3 p2(3, 4, 1);
    cout << p2 << " intersects: " << s.point_intersects(p2) << endl;
    return 0;
}