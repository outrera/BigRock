#include <iostream>

#include "vector3.h"

using namespace std;
using namespace bigrock;

int main(int argc, char const *argv[])
{
    cout << "Vector3 test" << endl;
    Vector3 v;
    cout << "Vector3 constructed: " << v << endl;
    cout << "Passing numbers 3, 5, 2" << endl;
    v = Vector3(3, 5, 2);
    cout << "Vector constructed: " << v << endl;
    float mul = 3.5;
    cout << "Multiplying by " << mul << endl;
    v *= mul;
    cout << "Multiplied: " << v << endl;
    Vector3 add = Vector3(1, 2, 3);
    cout << "Adding " << add << endl;
    v += add;
    cout << "Added: " << v << endl;
    return 0;
}
