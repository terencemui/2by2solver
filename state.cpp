#include "state.h"

#include <iostream>
#include <unordered_set>
#include <queue>
#include <string>

state::state()
{
    moves.reserve(20);
    cube = "RRRRGGGGYYYYBBBBWWWWOOOO";
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
void state::turn(string &direction)
{
    // R
    if (direction == "R")
    {
        int tape[8] = {1, 3, 9, 11, 21, 23, 18, 16};
        int face[4] = {14, 15, 13, 12};
        turn(tape, face);
    }
    else if (direction == "R'")
    {
        int tape[8] = {16, 18, 23, 21, 11, 9, 3, 1};
        int face[4] = {12, 13, 15, 14};
        turn(tape, face);
    }
    else if (direction == "U")
    {
        int tape[8] = {5, 7, 20, 21, 14, 12, 3, 2};
        int face[4] = {10, 11, 9, 8};
        turn(tape, face);
    }
    else if (direction == "U'")
    {
        int tape[8] = {2, 3, 12, 14, 21, 20, 7, 5};
        int face[4] = {8, 9, 11, 10};
        turn(tape, face);
    }
    else if (direction == "F")
    {
        int tape[8] = {19, 18, 15, 14, 11, 10, 7, 6};
        int face[4] = {22, 23, 21, 20};
        turn(tape, face);
    }
    else if (direction == "F'")
    {
        int tape[8] = {6, 7, 10, 11, 14, 15, 18, 19};
        int face[4] = {20, 21, 23, 22};
        turn(tape, face);
    }
}

void state::turn(int tape[8], int face[4])
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

int state::compare()
{
    int misplaced = 0;
    string key = "RRRRGGGGYYYYBBBBWWWWOOOO";
    for (int i = 0; i < key.size(); ++i)
    {
        if (key[i] == cube[i])
        {
            misplaced++;
        }
    }
    return misplaced;
}

void state::solve()
{
    // pop from the queue
    // check the cube
    // turn it 6 ways
    // if it isn't in the set, add it to the queue

    queue<state> q;
    state tempState = state(cube, moves);
    q.push(tempState);

    unordered_set<string> visited;
    visited.insert(tempState.cube);

    state solved;
    state currState;

    int count = 0;
    string rotations[6] = {"R", "R'", "U", "U'", "F", "F'"};

    string input;
    int repeated = 0;
    int undo = 0;

    while (!q.empty())
    {
        ++count;
        currState = q.front();
        q.pop();

        // if the same, if solved
        if (strcmp(currState.cube.c_str(), solved.cube.c_str()) == 0)
        {
            cout << "visited: " << visited.size() << " repeated: " << repeated << endl;
            cout << "solved in " << currState.moves.size() << " moves" << endl
                 << "checked " << count << " iterations" << endl;
            //  << "avoided " << undo << " undos" << endl;
            for (unsigned int i = 0; i < currState.moves.size(); ++i)
            {
                cout << currState.moves[i] << " ";
            }
            cout << endl;
            return;
        }
        else
        {
            for (unsigned int i = 0; i < 6; ++i)
            {
                if (rotations[i] != currState.moves.back())
                {
                    state newState = state(currState.cube, currState.moves);
                    newState.turn(rotations[i]);
                    newState.moves.push_back(rotations[i]);
                    // if it doesn't exist already, add it to the queue
                    if (visited.count(newState.cube) == 0)
                    {
                        q.push(newState);
                        visited.insert(newState.cube);
                    }
                    else
                    {
                        repeated++;
                    }
                }
                else
                {
                    undo++;
                }
            }
        }
    }
    cout << "no solution found in " << count << " permutations " << endl
         << currState.moves.size() << " moves" << endl;
}

void state::calculateMisplaced()
{
    queue<state> q;
    state tempState = state();
    q.push(tempState);

    unordered_set<string> visited;
    visited.insert(tempState.cube);

    state solved;
    state currState;

    string rotations[6] = {"R", "R'", "U", "U'", "F", "F'"};

    int sum[16]{};
    int count[16]{};

    cout << sum[0] << endl;

    // int sum = 0;
    // int count = 0;

    int revisited = 0;

    while (!q.empty())
    {
        currState = q.front();
        q.pop();

        // compare currState
        // add misplaced to the sum

        // cout << "moves: " << currState.moves.size() << " misplaced: " << currState.compare() << endl;

        // if (currState.moves.size() == 16)
        // {
        //     for (unsigned int i = 0; i < 15; ++i)
        //     {
        //         cout << sum[i] << " " << count[i] << " " << "mean: " << sum[i] / count[i] << endl;
        //     }
        //     // return;
        // }

        // sum[currState.moves.size()] += currState.compare();
        // count[currState.moves.size()]++;

        for (unsigned int i = 0; i < 6; ++i)
        {
            if (rotations[i] != currState.moves.back())
            {
                state newState = state(currState.cube, currState.moves);
                newState.turn(rotations[i]);
                newState.moves.push_back(rotations[i]);
                // if it doesn't exist already, add it to the queue
                if (visited.count(newState.cube) == 0)
                {
                    q.push(newState);
                    visited.insert(newState.cube);
                }
                else
                {
                    revisited++;
                }
            }
        }
    }
    cout << "revisited: " << revisited << endl;

    // cout << sum << " " << count << " " << "mean: " << sum / count << endl;

    // cout << "test" << endl;

    // for (unsigned int i = 0; i < 16; ++i)
    // {
    //     cout << sum[i] / count[i] << " ";
    // }
    // cout << endl;
}

void state::findShortest()
{
    // 20 possible options

    int cubettes[7][3] = {2, 5, 8, 3, 9, 12, 7, 10, 20, 11, 14, 21, 15, 18, 23, 6, 22, 19, 1, 13, 16};

    int currPos[3];
    int goalPos[3];

    for (unsigned int i = 0; i < 3; ++i)
    {
        currPos[i] = cubettes[0][i];
    }

    char currColor[3];
    char goalColor[3];

    // if curr = goal, return num of moves
    // else, move 6 ways
    // if it isn't in the set, add to queue
    // increment moveCounter


    // if (currColor == goalPos)
    // {

    // }


}