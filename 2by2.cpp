#include <iostream>
#include <unordered_set>
#include <chrono>
#include <time.h>
#include <random>
#include "state.h"

using namespace std;
// using namespace std;

int main()
{
    state cube;
    string possibleMoves[9] = {"R", "R'", "R2", "U", "U'", "U2", "F", "F'", "F2"};

    srand(time(0));
    int numMoves = 20;
    vector<int> moveList(numMoves);
    for (int i = 0; i <numMoves; ++i)
    {
        moveList.at(i) = rand() % 9;
    }

    cout << "Scramble: ";
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
    // cube.solve();
    cube.solveMiddle();
    // cube.printCube();
    // cout << cube.test() << endl;;

    auto end = chrono::high_resolution_clock::now();
    auto diff = end - start;

    cout << chrono::duration<double>(diff).count() << " seconds " << endl;

    return 0;
}