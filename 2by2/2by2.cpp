#include <iostream>
#include <unordered_set>
#include <chrono>
#include <time.h>
#include <random>
#include "state.h"

using namespace std;
// using namespace std;
void testBench(int);
int main()
{
    srand(time(0));
    testBench(100);

    return 0;
}

void testBench(int num)
{
    auto start = chrono::high_resolution_clock::now();

    vector<string> solution;
    vector<string> scramble;
    int moves = 0;
    int visited = 0;
    bool print = false;

    for (int i = 0; i < num; ++i)
    {
        solution = {};
        scramble = {};
        state cube;
        cube.scramble(scramble);
        // cube.printCube();
        visited += cube.solve(solution);
        moves += solution.size();
    }

    if (print)
    {
        for (int i = 0; i < solution.size(); ++i)
        {
            cout << solution.at(i) << " ";
        }
        cout << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    auto diff = end - start;
    cout << "Total tests: " << num << endl
         << "Average moves: " << moves / num << endl
         << "Average time: " << chrono::duration<double>(diff).count() / num << " seconds " << endl
         << "Average visited: " << visited / num << endl
         << "Average visited per second: " << visited / num / (chrono::duration<double>(diff).count() / num) << endl;
}