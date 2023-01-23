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
    // visited.insert(tempState.cube);

    state solved;
    state currState;

    int count = 0;
    string rotations[6] = {"R", "R'", "U", "U'", "F", "F'"};

    string input;
    int repeated = 0;
    int undo = 0;
    int prune = 0;

    while (!q.empty())
    {
        ++count;
        currState = q.front();
        q.pop();

        if (visited.count(currState.cube) == 1)
        {
            ++repeated;
        } // if it hasn't been visited
        else if (strcmp(currState.cube.c_str(), solved.cube.c_str()) == 0)
        {
            cout << "visited: " << visited.size() << " repeated: " << repeated << endl;
            cout << "solved in " << currState.moves.size() << " moves" << endl
                 << "checked " << count << " iterations" << endl
                 << "pruned: " << prune << endl
                 << "undoed: " << undo << endl;
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
            visited.insert(currState.cube);
            // cout << "test" << endl;
            string undoTurn = inverseTurn(currState.moves.back());
            for (unsigned int i = 0; i < 6; ++i)
            {
                if (rotations[i] != undoTurn)
                // if (rotations[i] != (currState.moves.back()))
                {
                    state newState = state(currState.cube, currState.moves);
                    newState.turn(rotations[i]);
                    newState.moves.push_back(rotations[i]);
                    // if it doesn't exist already, add it to the queue
                    // if (visited.count(newState.cube) == 0)
                    {
                        q.push(newState);
                        // visited.insert(newState.cube);
                    }
                    // else
                    {
                        // ++prune;
                    }
                }
                else
                {
                    ++undo;
                }
            }
        }
    }
    cout << "no solution found in " << count << " permutations " << endl
         << currState.moves.size() << " moves" << endl
         << "pruned: " << prune << endl;
}

string state::inverseTurn(string input)
{
    if (input.size() == 1)
    {
        return input + "'";
    }
    else if (input.size() == 2)
    {
        string temp(1, input.at(0));
        return temp;
    }
    return "";
}

bool state::checkCubette(int pos[])
{
    state solved;
    for (int i = 0; i < 3; ++i)
    {
        if (solved.cube[pos[i]] != cube[pos[i]])
        {
            return false;
        }
    }
    return true;
}

int state::findHeuristic()
{
    int cubettes[7][3] = {2, 5, 8, 3, 9, 12, 7, 10, 20, 11, 14, 21, 15, 18, 23, 6, 22, 19, 1, 13, 16};

    int goalPos[3];
    int sum = 0;

    queue<state> q;
    state currState;
    state tempState;
    unordered_set<string> visited;
    string rotations[6] = {"R", "R'", "U", "U'", "F", "F'"};

    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            goalPos[j] = cubettes[i][j];
        }

        tempState = state(cube, moves);
        q.push(tempState);

        visited.insert(tempState.cube);

        while (!q.empty())
        {
            currState = q.front();
            q.pop();

            if (currState.checkCubette(goalPos))
            {
                for (int k = 0; k < currState.moves.size(); ++k)
                {
                    // cout << currState.moves.at(k) << " ";
                }
                // cout << endl;
                sum += currState.moves.size();
                sum -= moves.size();
                q = {};
                visited = {};
            }
            else
            {
                for (int k = 0; k < 6; ++k)
                {
                    if (rotations[k] != currState.moves.back())
                    {
                        state newState = state(currState.cube, currState.moves);
                        newState.turn(rotations[k]);
                        newState.moves.push_back(rotations[k]);
                        // if it doesn't exist already, add it to the queue
                        if (visited.count(newState.cube) == 0)
                        {
                            q.push(newState);
                            visited.insert(newState.cube);
                        }
                    }
                }
            }
        }
    }
    // cout << "sum: " << sum / 4 << endl;
    return sum / 4;
}

// void state::calculateMisplaced()
// {
//     queue<state> q;
//     state tempState = state();
//     q.push(tempState);

//     unordered_set<string> visited;
//     visited.insert(tempState.cube);

//     state solved;
//     state currState;

//     string rotations[6] = {"R", "R'", "U", "U'", "F", "F'"};

//     int sum[16]{};
//     int count[16]{};

//     cout << sum[0] << endl;

//     // int sum = 0;
//     // int count = 0;

//     int revisited = 0;

//     while (!q.empty())
//     {
//         currState = q.front();
//         q.pop();

//         // compare currState
//         // add misplaced to the sum

//         // cout << "moves: " << currState.moves.size() << " misplaced: " << currState.compare() << endl;

//         // if (currState.moves.size() == 16)
//         // {
//         //     for (unsigned int i = 0; i < 15; ++i)
//         //     {
//         //         cout << sum[i] << " " << count[i] << " " << "mean: " << sum[i] / count[i] << endl;
//         //     }
//         //     // return;
//         // }

//         // sum[currState.moves.size()] += currState.compare();
//         // count[currState.moves.size()]++;

//         for (unsigned int i = 0; i < 6; ++i)
//         {
//             if (rotations[i] != currState.moves.back())
//             {
//                 state newState = state(currState.cube, currState.moves);
//                 newState.turn(rotations[i]);
//                 newState.moves.push_back(rotations[i]);
//                 // if it doesn't exist already, add it to the queue
//                 if (visited.count(newState.cube) == 0)
//                 {
//                     q.push(newState);
//                     visited.insert(newState.cube);
//                 }
//                 else
//                 {
//                     revisited++;
//                 }
//             }
//         }
//     }
//     cout << "revisited: " << revisited << endl;

//     // cout << sum << " " << count << " " << "mean: " << sum / count << endl;

//     // cout << "test" << endl;

//     // for (unsigned int i = 0; i < 16; ++i)
//     // {
//     //     cout << sum[i] / count[i] << " ";
//     // }
//     // cout << endl;
// }

// void state::findShortest()
// {
//     // 20 possible options

//     int cubettes[7][3] = {2, 5, 8, 3, 9, 12, 7, 10, 20, 11, 14, 21, 15, 18, 23, 6, 22, 19, 1, 13, 16};

//     // char currColor[3];
//     char goalColor[3];

//     // let currCubette be the cubette we look at
//     // find the correct position of the currCubette
//     // if the colors at correctPos are correct, return
//     // else, rotate and add to queue

//     char currColor[3];
//     currColor[0] = cube[11];
//     currColor[1] = cube[14];
//     currColor[2] = cube[21];

//     int goalPos[3];
//     this->findPos(currColor, goalPos);

//     for (int i = 0; i < 3; ++i)
//     {
//         cout << goalPos[i] << " ";
//     }

//     queue<state> q;
//     state tempState = state(cube, moves);
//     q.push(tempState);

//     unordered_set<string> visited;
//     visited.insert(tempState.cube);

//     // state solved;
//     state currState;

//     string rotations[6] = {"R", "R'", "U", "U'", "F", "F'"};

//     while (!q.empty())
//     {

//         currState = q.front();
//         q.pop();

//         if (currState.moves.size() == 2)
//         {
//             return;
//         }

//         if (currState.checkCubette(goalPos))
//         {
//             cout << "moves: " << currState.moves.size() << endl;
//             return;
//         }
//         else
//         {
//             cout << "not solved " << endl;
//             for (unsigned int i = 0; i < 6; ++i)
//             {
//                 if (rotations[i] != currState.moves.back())
//                 {
//                     state newState = state(currState.cube, currState.moves);
//                     newState.turn(rotations[i]);
//                     newState.moves.push_back(rotations[i]);
//                     // if it doesn't exist already, add it to the queue
//                     if (visited.count(newState.cube) == 0)
//                     {
//                         q.push(newState);
//                         visited.insert(newState.cube);
//                     }
//                 }
//             }
//         }
//     }
// }

// void state::findPos(char colors[], int result[])
// {
//     int cubettes[7][3] = {2, 5, 8, 3, 9, 12, 7, 10, 20, 11, 14, 21, 15, 18, 23, 6, 22, 19, 1, 13, 16};
//     state solved;
//     // 15, 18, 23

//     unordered_set<char> s;

//     for (size_t i = 0; i < 3; ++i)
//     {
//         s.insert(colors[i]);
//     }

//     int side = 0;
//     for (int i = 0; i < 7; ++i)
//     {
//         if (s.count(solved.cube[cubettes[i][side]]) == 1) // if it exists
//         {
//             side++;
//             // check if all 3 sides are correct
//             if (side == 3)
//             {
//                 cout << "correct " << endl;
//                 for (int j = 0; j < 3; ++j)
//                 {
//                     // cout << cubettes[i][j] << " ";
//                     result[j] = cubettes[i][j];
//                 }
//                 cout << endl;
//                 return;
//             }
//             --i;
//         }
//         else
//         {
//             side = 0;
//         }
//     }
// }
