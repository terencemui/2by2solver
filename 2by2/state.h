#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include <queue>

using namespace std;

struct state
{
    string cube;
    vector<string> moves;

    state();
    state(const string&, vector<string>);

    void printCube();
    void turn(const string &);
    void _turn(const int[8], const int[4]);
    int solve(vector<string>&);
    void reverse(vector<string>&);
    void scramble(vector<string>&);
    void move(state&, queue<state>&);
};
#endif