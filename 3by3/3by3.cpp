#include "state.h"
#include <time.h>
#include <vector>
#include <random>
#include <iostream>
#include <chrono>

using namespace std;

void testBench(int);

int main()
{
    srand(time(0));
    testBench(1);
    // state cube = state();

    // cube.printCube();

    // vector<string> solution = {};
    // vector<string> scramble = {};
    // cube.scramble(scramble);
    // for (unsigned int i = 0; i < scramble.size(); ++i)
    // {
    //     cout << scramble.at(i) << " ";
    // }
    // cout << endl;

    // cube.printCube();

    // cube.solve(solution);
    // for (unsigned i = 0; i < solution.size(); ++i)
    // {
    //     cout << solution.at(i) << " ";
    // }
    // cout << endl;

    // int num = 10;

    // vector<string> moves = {"R", "R'", "R2", "L", "L'", "L2", "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2"};
    // vector<string> scramble;
    // for (unsigned int i = 0; i < num; ++i)
    // {
    //     int temp = rand() % 18;
    //     cout << moves.at(temp) << " ";
    //     cube.turn(moves.at(temp));
    // }

    return 0;
}

void testBench(int num)
{
    auto start = chrono::high_resolution_clock::now();

    vector<string> solution;
    vector<string> scramble;
    int moves = 0;
    int visited = 0;

    for (int i = 0; i < num; ++i)
    {
        solution = {};
        scramble = {};
        state cube;
        cube.scramble(scramble, 10);
        // cube.printCube();
        visited += cube.solve(solution);
        moves += solution.size();
    }

    auto end = chrono::high_resolution_clock::now();
    auto diff = end - start;
    cout << "Total tests: " << num << endl
         << "Average moves: " << moves / num << endl
         << "Average time: " << chrono::duration<double>(diff).count() / num << " seconds " << endl
         << "Average visited: " << visited / num << endl
         << "Average visited per second: " << visited / num / (chrono::duration<double>(diff).count() / num) << endl;
}