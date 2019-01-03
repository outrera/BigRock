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

    // Vector3 operations
    cout << "VECTOR3 OPERATIONS" << endl;
    cout << "Addition" << endl;
    Vector3 add = Vector3(3, 5, 2);
    cout << v << " + " << add << " = " << (v + add) << endl;
    v += add;
    cout << "The Vector3 is now " << v << endl;

    cout << endl << "Subtraction" << endl;
    Vector3 sub = Vector3(2,1,3);
    cout << v << " - " << sub << " = " << (v - sub) << endl;
    v -= sub;
    cout << "The Vector3 is now " << v << endl;

    cout << endl << "Multiplication" << endl;
    Vector3 mul = Vector3(3, 3, 3);
    cout << v << " * " << mul << " = " << (v * mul) << endl;
    v *= mul;
    cout << "The Vector3 is now " << v << endl;

    cout << endl << "Division" << endl;
    Vector3 div = Vector3(2, 4, 3);
    cout << v << " / " << div << " = " << v / div << endl;
    v /= div;
    cout << "The Vector3 is now " << v << endl;

    // Scalar operations
    cout << endl << "SCALAR OPERATIONS" << endl;
    cout << "Multiplication" << endl;
    float scal_mul = 4.6;
    cout << v << " * " << scal_mul << " = " << (v * scal_mul) << endl;
    v *= scal_mul;
    cout << "The Vector3 is now " << v << endl;

    cout << endl << "Division" << endl;
    float scal_div = 3.5;
    cout << v << " / " << scal_div << " = " << (v / scal_div) << endl;
    v /= scal_div;
    cout << "The Vector3 is now " << v << endl;

    // Comparisons
    cout << endl << "COMPARISON OPERATORS" << endl;
    Vector3 comp = Vector3(5, 7, 8.3);
    cout << "(" << comp << " == " << comp << ") = " << (comp == comp) << endl;
    cout << "(" << comp << " != " << comp << ") = " << (comp != comp) << endl;
    cout << "(" << v << " == " << comp << ") = " << (v == comp) << endl;
    cout << "(" << v << " != " << comp << ") = " << (v != comp) << endl;
    return 0;
}
