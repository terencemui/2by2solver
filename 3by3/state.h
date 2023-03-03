#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>

using namespace std;

struct state
{
    string cube;
    vector<string> moves;

    state();
    state(string&, vector<string> moves);

    void printCube();
    void turn(string);
    void turn(int[8], int[4]);
    void scramble(vector<string>&, int);
    int solve(vector<string>&);
    void reverse(vector<string>&);
};
#endif