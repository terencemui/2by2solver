#include <iostream>
#include <unordered_set>
#include <chrono>
#include <time.h>
#include <random>
#include "state.h"

using namespace std;
// using namespace std;
void testBench();
int main()
{
    // srand(time(0));

    // state cube;
    // vector<string> scramble;
    // vector<string> solution;

    // cube.scramble(scramble);
    // cube.solve(solution);

    // cout << "Scramble: ";
    // for (unsigned int i = 0; i < scramble.size(); ++i)
    // {
    //     cout << scramble.at(i) << " ";
    // }
    // cout << endl;

    // cout << "Solved in " << solution.size() << " moves: " << endl;
    // for (unsigned int i = 0; i < solution.size(); ++i)
    // {
    //     cout << solution.at(i) << " ";
    // }
    // cout << endl;

    testBench();

    return 0;
}

void testBench()
{
    auto start = chrono::high_resolution_clock::now();

    int tests = 20;
    vector<string> solution;
    vector<string> scramble;
    int moves = 0;

    for (int i = 0; i < tests; ++i)
    {
        solution = {};
        scramble = {};
        state cube;
        cube.scramble(scramble);
        // cube.printCube();
        cube.solve(solution);
        moves += solution.size();
    }

    auto end = chrono::high_resolution_clock::now();
    auto diff = end - start;
    cout << "Total tests: " << tests << endl
         << "Average moves: " << moves / tests << endl
         << "Average time: " << chrono::duration<double>(diff).count() / tests << " seconds " << endl;
}