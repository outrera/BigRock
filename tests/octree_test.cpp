#include "vector3.h"
#include "octree.h"
#include "standard_data.h"

#include <iostream>

using namespace std;
using namespace bigrock;

void main(int argc, char const *argv[])
{
    cout << "Beginning octree test" << endl;
    Vector3 size(32,32,32);
    Octree<OctreePointNN<char>> nearest_neighbor(size, '\0');
    cout << "Octree constructed with size " << size << endl;
    cout << "Enter three numbers to emplace data at, separated by spaces or returns" << endl;
    Vector3 pos;
    cin >> pos.x >> pos.y >> pos.z;
    cout << "Enter the max depth, or -1 for no max depth" << endl;
    int max_depth;
    cin >> max_depth;
    cout << "Enter a single character to emplace at the point" << endl;
    char data;
    cin >> data;
    
    cout << "Beginning emplacement of data \'" << data << "\' at position " << pos << " with max depth " << max_depth << endl;
    Vector3 actual_pos = nearest_neighbor.set_data_at_position(pos, OctreePointNN<char>(data), max_depth);
    cout << "Data placed at " << actual_pos << endl;
    cout << "Test 1: Retrieve data at actual position " << actual_pos << endl;
    char retrieve = nearest_neighbor.get_data_at_position(actual_pos, max_depth);
    cout << "Test 1 result: " << retrieve << endl;
    cout << "Test 2: Retrieve data at given position " << pos << endl;
    retrieve = nearest_neighbor.get_data_at_position(pos, max_depth);
    cout << "Test 2 results: " << retrieve << endl;
}
