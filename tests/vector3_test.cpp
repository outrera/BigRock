#include "vector3.h"
#include <iostream>

using namespace std;
using namespace bigrock;

int main(int argc, char const *argv[])
{
    cout << "Vector3 test" << endl;
    float x,y,z;
    cout << "Enter three numbers to construct a Vector3" << endl;
    cin >> x >> y >> z;
    Vector3 vec(x, y, z);
    cout << "Constructed Vector3: (" << vec.x << ", " << vec.y << ", " << vec.z << ")" << endl;
    cout << "Comparing distances between (0,0,0) and (1,1,1)" << endl;
    const float dist = 1.73205080757;
    cout << "Expected: " << dist << " Actual: " << Vector3(0,0,0).distance_to(Vector3(1,1,1)) << endl;
    cout << "Comparing squared distances between (0,0,0) and (1,1,1)" << endl;
    cout << "Expected: " << (dist * dist) << " Actual: " << Vector3(0,0,0).distance_squared_to(Vector3(1,1,1)) << endl;
    return 0;
}
