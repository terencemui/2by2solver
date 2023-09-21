#include "state.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <string>
#include <time.h>
#include <random>
#include <thread>

// hello world

state::state()
{
    moves.reserve(20);
    cube = "RRRRGGGGYYYYBBBBWWWWOOOO";
}

state::state(const string &c, vector<string> m)
{
    moves = std::move(m);
    cube = c;
}

void state::printCube()
{
    // R
    for (unsigned int i = 0; i < 2; ++i)
    {
        cout << "    ";
        for (unsigned int j = 0; j < 2; ++j)
        {
            cout << cube[(i * 2) + j] << " ";
        }
        cout << endl;
    }

    // G,Y,B,W
    for (unsigned int i = 0; i < 2; ++i)
    {
        for (unsigned int j = 1; j < 5; ++j)
        {
            for (unsigned int k = 0; k < 2; ++k)
            {
                cout << cube[(i * 2 + j * 4 + k)] << " ";
            }
        }
        cout << endl;
    }

    // O
    for (unsigned int i = 0; i < 2; ++i)
    {
        cout << "    ";
        for (unsigned int j = 20; j < 22; ++j)
        {
            cout << cube[(i * 2) + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// RGW IS CENTER
void state::turn(const string &direction)
{
    // R
    if (direction == "R")
    {
        int tape[8] = {1, 3, 9, 11, 21, 23, 18, 16};
        int face[4] = {14, 15, 13, 12};
        _turn(tape, face);
    }
    else if (direction == "R'")
    {
        int tape[8] = {16, 18, 23, 21, 11, 9, 3, 1};
        int face[4] = {12, 13, 15, 14};
        _turn(tape, face);
    }
    else if (direction == "R2")
    {
        int tape[8] = {16, 18, 23, 21, 11, 9, 3, 1};
        int face[4] = {12, 13, 15, 14};
        _turn(tape, face);
        _turn(tape, face);
    }
    else if (direction == "U")
    {
        int tape[8] = {5, 7, 20, 21, 14, 12, 3, 2};
        int face[4] = {10, 11, 9, 8};
        _turn(tape, face);
    }
    else if (direction == "U'")
    {
        int tape[8] = {2, 3, 12, 14, 21, 20, 7, 5};
        int face[4] = {8, 9, 11, 10};
        _turn(tape, face);
    }
    else if (direction == "U2")
    {
        int tape[8] = {2, 3, 12, 14, 21, 20, 7, 5};
        int face[4] = {8, 9, 11, 10};
        _turn(tape, face);
        _turn(tape, face);
    }
    else if (direction == "F")
    {
        int tape[8] = {19, 18, 15, 14, 11, 10, 7, 6};
        int face[4] = {22, 23, 21, 20};
        _turn(tape, face);
    }
    else if (direction == "F'")
    {
        int tape[8] = {6, 7, 10, 11, 14, 15, 18, 19};
        int face[4] = {20, 21, 23, 22};
        _turn(tape, face);
    }
    else if (direction == "F2")
    {
        int tape[8] = {6, 7, 10, 11, 14, 15, 18, 19};
        int face[4] = {20, 21, 23, 22};
        _turn(tape, face);
        _turn(tape, face);
    }
    else
    {
        cout << "Invalid direction: " << direction << endl;
    }
    moves.push_back(direction);
}

void state::_turn(const int tape[8], const int face[4])
{
    char temp;
    for (int j = 0; j < 2; ++j)
    {
        temp = cube[tape[j]];
        for (int i = 0; i < 3; ++i)
        {
            cube[tape[(2 * i + j)]] = cube[tape[(2 * i + j + 2)]];
        }
        cube[tape[6 + j]] = temp;
    }

    temp = cube[face[0]];
    for (int i = 0; i < 3; ++i)
    {
        cube[face[i]] = cube[face[i + 1]];
    }
    cube[face[3]] = temp;
}

int state::solve(vector<string> &output)
{
    int visited = 0;

    queue<state> scrambledQ;
    queue<state> solvedQ;

    state currScrambled = state(cube, moves);
    scrambledQ.push(currScrambled);

    state currSolved;
    solvedQ.push(currSolved);

    unordered_map<string, vector<string>> scrambledMap;
    unordered_map<string, vector<string>> solvedMap;

    while (!scrambledQ.empty())
    {
        visited += 2;
        currScrambled = scrambledQ.front();
        scrambledQ.pop();

        currSolved = solvedQ.front();
        solvedQ.pop();

        auto findScrambled = scrambledMap.find(currScrambled.cube);
        auto findSolved = solvedMap.find(currSolved.cube);

        auto findScramSolv = solvedMap.find(currScrambled.cube); // find scrambled in solve
        auto findSolvScram = scrambledMap.find(currSolved.cube); // find solved in scramble

        if (findScrambled != scrambledMap.end() && findSolved != solvedMap.end())
        {
            // do nothing
        }
        else if (findScramSolv != solvedMap.end()) // if scrambled is in solvedMap
        {
            for (unsigned int i = 0; i < currScrambled.moves.size(); ++i)
            {
                output.push_back(currScrambled.moves.at(i));
            }
            reverse(findScramSolv->second);
            for (unsigned int i = 0; i < findScramSolv->second.size(); ++i)
            {
                output.push_back(findScramSolv->second.at(i));
            }
            return visited;
        }
        else if (findSolvScram != scrambledMap.end()) // if solved is in scrambledMap
        {
            for (unsigned int i = 0; i < findSolvScram->second.size(); ++i)
            {
                output.push_back(findSolvScram->second.at(i));
            }
            reverse(currSolved.moves);
            for (unsigned int i = 0; i < currSolved.moves.size(); ++i)
            {
                output.push_back(currSolved.moves.at(i));
            }
            return visited;
        }
        else if (findScrambled == scrambledMap.end() && findSolved == solvedMap.end()) // if they're both new
        {
            scrambledMap.insert({currScrambled.cube, currScrambled.moves});
            solvedMap.insert({currSolved.cube, currSolved.moves});

            // thread thread1(&state::move, this, currScrambled, std::ref(scrambledQ));
            // thread thread2(&state::move, this, currSolved, std::ref(solvedQ));
            // thread1.join();
            // thread2.join();
            move(currScrambled, scrambledQ);
            move(currSolved, solvedQ);
        }
        else if (findScrambled == scrambledMap.end())
        {
            scrambledMap.insert({currScrambled.cube, currScrambled.moves});
            move(currScrambled, scrambledQ);
        }
        else if (findSolved == solvedMap.end())
        {
            solvedMap.insert({currSolved.cube, currSolved.moves});
            move(currSolved, solvedQ);
        }
    }
    return 0;
}

void state::reverse(vector<string> &turns)
{
    int size = turns.size();
    vector<string> temp(size);
    temp.reserve(size);
    for (unsigned int i = 0; i < size; ++i)
    {
        if (turns.at(i).size() == 1)
        {
            temp.at(size - i - 1) = (turns.at(i) + "'");
        }
        else if (turns.at(i).at(1) == '\'')
        {
            temp.at(size - i - 1) = turns.at(i).at(0);
        }
        else
        {
            temp.at(size - i - 1) = turns.at(i);
        }
    }
    turns = temp;
}

void state::scramble(vector<string> &scramble)
{
    if (scramble.size() != 0)
    {
        for (int i = 0; i < scramble.size(); ++i)
        {
            turn(scramble.at(i));
        }
        moves = {};
        return;
    }
    string possibleMoves[9] = {"R", "R'", "R2", "U", "U'", "U2", "F", "F'", "F2"};

    int numMoves = 20;
    scramble.reserve(numMoves);
    char temp = ' ';
    string move;
    for (int i = 0; i < numMoves; ++i)
    {
        if (scramble.size() != 0)
        {
            temp = scramble.back().at(0);
        }
        move = possibleMoves[rand() % 9];
        if (move.at(0) != temp)
        {
            scramble.push_back(move);
            turn(move);
        }
        else
        {
            --i;
        }
    }
    moves = {};
}

void state::move(const state &currState, queue<state> &currQ)
{
    char temp;
    string rotations[9] = {"R", "R'", "R2", "U", "U'", "U2", "F", "F'", "F2"};
    temp = ' ';
    if (currState.moves.size() != 0)
    {
        temp = (currState.moves.back()).at(0);
    }
    for (unsigned int i = 0; i < 9; ++i)
    {
        if (rotations[i].at(0) != temp)
        {
            state newState = state(currState.cube, currState.moves);
            newState.turn(rotations[i]);
            currQ.push(newState);
        }
    }
}
