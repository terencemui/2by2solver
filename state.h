#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>

using namespace std;

struct state
{
    // char cube[24];
    string cube;
    vector<string> moves;

    state();
    state(string&, vector<string> moves);

    void printCube();
    void turn(string);
    void turn(int[8], int[4]);
    void solve();
    void reverse(vector<string>&);

    // int compare();
    // void solve();
    // bool checkCubette(int[]);
    // int findHeuristic();
    // int test();

};
#endif