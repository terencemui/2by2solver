#include <iostream>
#include <unordered_set>
#include <chrono>
#include "state.h"

using namespace std;
// using namespace std;

int main()
{
    state cube;

    string possibleMoves[9] = {"R", "R'", "R2", "U", "U'", "U2", "F", "F'", "F2"};

    vector<int> moveList = {0, 5, 2, 4, 0, 3, 2, 7, 4, 8};
    // vector<int> moveList = {0, 2};
    // vector<int> moveList = {2, 5, 3};

    for (unsigned int i = 0; i < moveList.size(); ++i)
    {
        cout << possibleMoves[moveList[i]] << " ";
        cube.turn(possibleMoves[moveList[i]]);
    }
    cout << endl;

    cube.printCube();

    auto start = chrono::high_resolution_clock::now();
    // cube.findShortest();
    // cout << cube.findHeuristic() << endl;
    // cube.inverseTurn("R");
    cube.solve();
    // cube.calculateMisplaced();
    auto end = chrono::high_resolution_clock::now();
    auto diff = end - start;

    cout << chrono::duration<double>(diff).count() << " seconds " << endl;

    return 0;
}