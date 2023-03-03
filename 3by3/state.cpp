#include "state.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <queue>

// Y up, O forwrad
state::state()
{
    moves.reserve(20);
    cube = "RRRRRRRRRGGGYYYBBBWWWGGGYYYBBBWWWGGGYYYBBBWWWOOOOOOOOO";
}

state::state(string &c, vector<string> m)
{
    moves.reserve(20);
    cube = c;
    this->moves = m;
}

void state::printCube()
{
    // R
    for (int i = 0; i < 3; ++i)
    {
        cout << "      ";
        for (int j = 0; j < 3; ++j)
        {
            cout << cube[(i * 3 + j)] << " ";
        }
        cout << endl;
    }

    // G, Y, B, W
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            cout << cube[9 + i * 12 + j] << " ";
        }
        cout << endl;
    }

    // O
    for (int i = 0; i < 3; ++i)
    {
        cout << "      ";
        for (int j = 0; j < 3; ++j)
        {
            cout << cube[45 + i * 3 + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void state::turn(string direction)
{
    if (direction == "R")
    {
        int tape[12] = {14, 26, 38, 47, 50, 53, 42, 30, 18, 2, 5, 8};
        int face[8] = {27, 39, 40, 41, 29, 17, 16, 15};
        turn(tape, face);
    }
    else if (direction == "R'")
    {
        int tape[12] = {8, 5, 2, 18, 30, 42, 53, 50, 47, 38, 26, 14};
        int face[8] = {15, 16, 17, 29, 41, 40, 39, 27};
        turn(tape, face);
    }
    else if (direction == "R2")
    {
        turn("R");
        turn("R");
    }
    else if (direction == "L")
    {
        int tape[12] = {6, 3, 0, 20, 32, 44, 51, 48, 45, 36, 24, 12};
        int face[8] = {21, 33, 34, 35, 23, 11, 10, 9};
        turn(tape, face);
    }
    else if (direction == "L'")
    {
        int tape[12] = {12, 24, 36, 45, 48, 51, 44, 32, 20, 0, 3, 6};
        int face[8] = {9, 10, 11, 23, 35, 34, 33, 21};
        turn(tape, face);
    }
    else if (direction == "L2")
    {
        turn("L");
        turn("L");
    }
    else if (direction == "U")
    {
        int tape[12] = {11, 23, 35, 45, 46, 47, 39, 27, 15, 8, 7, 6};
        int face[8] = {24, 36, 37, 38, 26, 14, 13, 12};
        turn(tape, face);
    }
    else if (direction == "U'")
    {
        int tape[12] = {6, 7, 8, 15, 27, 39, 47, 46, 45, 35, 23, 11};
        int face[8] = {12, 13, 14, 26, 38, 37, 36, 24};
        turn(tape, face);
    }
    else if (direction == "U2")
    {
        turn("U");
        turn("U");
    }
    else if (direction == "D")
    {
        int tape[12] = {53, 52, 51, 33, 21, 9, 0, 1, 2, 17, 29, 41};
        int face[8] = {43, 44, 32, 20, 19, 18, 30, 42};
        turn(tape, face);
    }
    else if (direction == "D'")
    {
        int tape[12] = {41, 29, 17, 2, 1, 0, 9, 21, 33, 51, 52, 53};
        int face[8] = {42, 30, 18, 19, 20, 32, 44, 43};
        turn(tape, face);
    }
    else if (direction == "D2")
    {
        turn("D");
        turn("D");
    }
    else if (direction == "F")
    {
        int tape[12] = {44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33};
        int face[8] = {48, 51, 52, 53, 50, 47, 46, 45};
        turn(tape, face);
    }
    else if (direction == "F'")
    {
        int tape[12] = {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44};
        int face[8] = {45, 46, 47, 50, 53, 52, 51, 48};
        turn(tape, face);
    }
    else if (direction == "F2")
    {
        turn("F");
        turn("F");
    }
    else if (direction == "B")
    {
        int tape[12] = {9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
        int face[8] = {6, 7, 8, 5, 2, 1, 0, 3};
        turn(tape, face);
    }
    else if (direction == "B'")
    {
        int tape[12] = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9};
        int face[8] = {3, 0, 1, 2, 5, 8, 7, 6};
        turn(tape, face);
    }
    else if (direction == "B2")
    {
        turn("B");
        turn("B");
    }
    else
    {
        cout << "Invalid move: " << direction << endl;
    }
}

void state::turn(int tape[12], int face[8])
{
    char temp;
    for (int i = 0; i < 3; ++i)
    {
        temp = cube[tape[i]];
        for (int j = 0; j < 3; ++j)
        {
            cube[tape[3 * j + i]] = cube[tape[3 * (j + 1) + i]];
        }
        cube[tape[9 + i]] = temp;
    }

    for (int i = 0; i < 2; ++i)
    {
        temp = cube[face[i]];
        for (int j = 0; j < 3; ++j)
        {
            cube[face[i + j * 2]] = cube[face[i + j * 2 + 2]];
        }
        cube[face[i + 6]] = temp;
    }
}

void state::scramble(vector<string> &scramble, int numMoves)
{
    if (scramble.size() != 0)
    {
        return;
    }
    string possibleMoves[18] = {"R", "R'", "R2", "L", "L'", "L2", "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2"};

    scramble.reserve(numMoves);
    char temp = ' ';
    string move;
    for (int i = 0; i < numMoves; ++i)
    {
        if (scramble.size() != 0)
        {
            temp = scramble.back().at(0);
        }
        move = possibleMoves[rand() % 18];
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
}

int state::solve(vector<string> &output)
{
    int visited = 0;
    string rotations[18] = {"R", "R'", "R2", "L", "L'", "L2", "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2"};

    char temp = ' ';

    queue<state> scrambledQ;
    queue<state> solvedQ;

    state currScrambled = state(cube, moves);
    scrambledQ.push(currScrambled);

    state currSolved;
    solvedQ.push(currSolved);

    unordered_map<string, vector<string>> scrambledMap;
    unordered_map<string, vector<string>> solvedMap;

    solvedMap.insert({currSolved.cube, currSolved.moves});

    while (!scrambledQ.empty())
    {
        visited += 2;
        currScrambled = scrambledQ.front();
        scrambledQ.pop();

        currSolved = solvedQ.front();
        solvedQ.pop();

        auto findScrambled = scrambledMap.find(currScrambled.cube);
        auto findSolved = solvedMap.find(currScrambled.cube);

        auto findScramSolv = solvedMap.find(currScrambled.cube); // find scrambled in solve
        auto findSolvScram = scrambledMap.find(currSolved.cube); // find solved in scramble

        if (findScrambled != scrambledMap.end()) // if in scrambledMap
        {
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
        else
        {
            scrambledMap.insert({currScrambled.cube, currScrambled.moves});
            for (unsigned int i = 0; i < 18; ++i)
            {
                temp = ' ';
                if (currScrambled.moves.size() != 0)
                {
                    temp = (currScrambled.moves.back()).at(0);
                }
                if (rotations[i].at(0) != temp)
                {
                    state newScrambled = state(currScrambled.cube, currScrambled.moves);
                    newScrambled.turn(rotations[i]);
                    // newScrambled.moves.push_back(rotations[i]);
                    scrambledQ.push(newScrambled);
                }
            }
        }

        if (findSolved != solvedMap.end())
        {
        }
        else if (findSolvScram != scrambledMap.end())
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
        else
        {
            solvedMap.insert({currSolved.cube, currSolved.moves});
            for (unsigned int i = 0; i < 18; ++i)
            {
                temp = ' ';
                if (currSolved.moves.size() != 0)
                {
                    temp = (currSolved.moves.back()).at(0);
                }
                if (rotations[i].at(0) != temp)
                {
                    state newSolved = state(currSolved.cube, currSolved.moves);
                    newSolved.turn(rotations[i]);
                    // newSolved.moves.push_back(rotations[i]);
                    solvedQ.push(newSolved);
                }
            }
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