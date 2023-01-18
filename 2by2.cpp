#include <iostream>
#include <unordered_set>
#include <chrono>
#include "state.h"

using namespace std;
// using namespace std;

int main()
{
    state cube;

    string possibleMoves[6] = {"R", "R'", "U", "U'", "F", "F'"};

    vector<int> moveList = {0, 5, 2, 1, 4, 4, 2, 5, 0, 2, 2, 5, 3, 5, 2};

    for (unsigned int i = 0; i < moveList.size(); ++i)
    {
        cout << possibleMoves[moveList[i]] << " ";
        cube.turn(possibleMoves[moveList[i]]);
    }
    cout << endl;

    cube.printCube();
    

    auto start = chrono::high_resolution_clock::now();
    cube.solve();
    auto end = chrono::high_resolution_clock::now();
    auto diff = end - start;

    cout << chrono::duration <double> (diff).count() << " seconds " << endl;

    return 0;
}