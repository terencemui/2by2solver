#include "state.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <string>
#include <time.h>
#include <random>
#include <thread>

void test(state currState, string &move, queue<state> scrambledQ, char prev);

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
void state::turn(string direction)
{
    // cout << "test" << endl;
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
    this->moves.push_back(direction);
    // cout << "pushing back: " << direction << endl;
}

void state::_turn(int tape[8], int face[4])
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
    string rotations[9] = {"R", "R'", "R2", "U", "U'", "U2", "F", "F'", "F2"};

    queue<state> scrambledQ;
    queue<state> solvedQ;

    state currScrambled = state(cube, moves);
    scrambledQ.push(currScrambled);

    state currSolved;
    solvedQ.push(currSolved);

    unordered_map<string, vector<string>> scrambledMap;
    unordered_map<string, vector<string>> solvedMap;

    // solvedMap.insert({currSolved.cube, currSolved.moves});

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

            // if (findScrambled != scrambledMap.end()) // if in scrambledMap
            // {
            // }
            // else if (findScramSolv != solvedMap.end()) // if scrambled is in solvedMap
            // {
            //     for (unsigned int i = 0; i < currScrambled.moves.size(); ++i)
            //     {
            //         output.push_back(currScrambled.moves.at(i));
            //     }
            //     reverse(findScramSolv->second);
            //     for (unsigned int i = 0; i < findScramSolv->second.size(); ++i)
            //     {
            //         output.push_back(findScramSolv->second.at(i));
            //     }
            //     return visited;
            // }
            // else
            // {
            //     scrambledMap.insert({currScrambled.cube, currScrambled.moves});
            //     move(currScrambled, scrambledQ);
            // }

            // if (findSolved != solvedMap.end())
            // {
            // }
            // else if (findSolvScram != scrambledMap.end())
            // {
            //     for (unsigned int i = 0; i < findSolvScram->second.size(); ++i)
            //     {
            //         output.push_back(findSolvScram->second.at(i));
            //     }
            //     reverse(currSolved.moves);
            //     for (unsigned int i = 0; i < currSolved.moves.size(); ++i)
            //     {
            //         output.push_back(currSolved.moves.at(i));
            //     }
            //     return visited;
            // }
            // else
            // {
            //     solvedMap.insert({currSolved.cube, currSolved.moves});
            //     move(currSolved, solvedQ);
            // }
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

void state::move(state currState, queue<state> &currQ)
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

// int state::compare()
// {
//     int misplaced = 0;
//     string key = "RRRRGGGGYYYYBBBBWWWWOOOO";
//     for (int i = 0; i < key.size(); ++i)
//     {
//         if (key[i] == cube[i])
//         {
//             misplaced++;
//         }
//     }
//     return misplaced;
// }

// void state::solve()
// {
//     // pop from the queue
//     // check the cube
//     // turn it 6 ways
//     // if it isn't in the set, add it to the queue

//     queue<state> q;
//     state tempState = state(cube, moves);
//     q.push(tempState);

//     unordered_set<string> visited;
//     // visited.insert(tempState.cube);

//     state solved;
//     // solved.cube = "RRRRGGGGYYYYBBBBWWWWOOOJ";
//     state currState;

//     string rotations[9] = {"R", "R'", "R2", "U", "U'", "U2", "F", "F'", "F2"};

//     string input;
//     int repeated = 0;

//     while (!q.empty())
//     {
//         currState = q.front();
//         q.pop();

//         if (visited.count(currState.cube) == 1)
//         {
//             ++repeated;
//         } // if it hasn't been visited
//         else if (strcmp(currState.cube.c_str(), solved.cube.c_str()) == 0)
//         {
//             cout << "visited: " << visited.size() << " repeated: " << repeated << endl
//                  << "solved in " << currState.moves.size() << " moves" << endl;
//             for (unsigned int i = 0; i < currState.moves.size(); ++i)
//             {
//                 cout << currState.moves[i] << " ";
//             }
//             cout << endl;
//             return;
//         }
//         else
//         {
//             visited.insert(currState.cube);
//             for (unsigned int i = 0; i < 9; ++i)
//             {
//                 char temp = ' ';
//                 if (currState.moves.size() != 0)
//                 {
//                     temp = (currState.moves.back()).at(0);
//                 }
//                 if (rotations[i].at(0) != temp)
//                 {

//                     state newState = state(currState.cube, currState.moves);
//                     newState.turn(rotations[i]);
//                     newState.moves.push_back(rotations[i]);
//                     q.push(newState);
//                 }
//             }
//         }
//     }
//     cout << "no solution found in " << visited.size() << " states " << endl
//          << currState.moves.size() << " moves" << endl;
// }

// bool state::checkCubette(int pos[])
// {
//     state solved;
//     for (int i = 0; i < 3; ++i)
//     {
//         if (solved.cube[pos[i]] != cube[pos[i]])
//         {
//             return false;
//         }
//     }
//     return true;
// }

// int state::findHeuristic()
// {
//     int cubettes[7][3] = {2, 5, 8, 3, 9, 12, 7, 10, 20, 11, 14, 21, 15, 18, 23, 6, 22, 19, 1, 13, 16};

//     int goalPos[3];
//     int sum = 0;

//     queue<state> q;
//     state currState;
//     state tempState;
//     unordered_set<string> visited;
//     string rotations[6] = {"R", "R'", "U", "U'", "F", "F'"};

//     for (int i = 0; i < 7; ++i)
//     {
//         for (int j = 0; j < 3; ++j)
//         {
//             goalPos[j] = cubettes[i][j];
//         }

//         tempState = state(cube, moves);
//         q.push(tempState);

//         visited.insert(tempState.cube);

//         while (!q.empty())
//         {
//             currState = q.front();
//             q.pop();

//             if (currState.checkCubette(goalPos))
//             {
//                 for (int k = 0; k < currState.moves.size(); ++k)
//                 {
//                     // cout << currState.moves.at(k) << " ";
//                 }
//                 // cout << endl;
//                 sum += currState.moves.size();
//                 sum -= moves.size();
//                 q = {};
//                 visited = {};
//             }
//             else
//             {
//                 for (int k = 0; k < 6; ++k)
//                 {
//                     if (rotations[k] != currState.moves.back())
//                     {
//                         state newState = state(currState.cube, currState.moves);
//                         newState.turn(rotations[k]);
//                         newState.moves.push_back(rotations[k]);
//                         // if it doesn't exist already, add it to the queue
//                         if (visited.count(newState.cube) == 0)
//                         {
//                             q.push(newState);
//                             visited.insert(newState.cube);
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     // cout << "sum: " << sum / 4 << endl;
//     return sum / 4;
// }

// int state::test()
// {

//     int sum = 0;
//     int cubettes[7][3] = {3, 9, 12, 11, 14, 21, 7, 10, 20, 2, 5, 8, 1, 13, 16, 15, 18, 23, 6, 22, 19};

//     state solved;

//     unordered_map<string, int> solvedMap;
//     unordered_map<string, int> currMap;

//     vector<int> order;
//     order.reserve(14);

//     string curr;
//     curr.reserve(3);
//     string solvedStr;
//     solvedStr.reserve(3);

//     int i = 0;

//     for (unsigned int i = 0; i < 7; ++i)
//     {
//         curr = "";
//         solvedStr = "";
//         for (unsigned int j = 0; j < 3; ++j)
//         {
//             curr.push_back(cube[cubettes[i][j]]);
//             solvedStr.push_back(solved.cube[cubettes[i][j]]);
//         }

//         sort(curr.begin(), curr.end());
//         sort(solvedStr.begin(), solvedStr.end());

//         auto temp = currMap.find(solvedStr);

//         if (temp != currMap.end()) // if solvedStr exists in curr
//         {
//             order.push_back(temp->second);
//             order.push_back(i);
//         }
//         else
//         {
//             solvedMap.insert({solvedStr, i});
//         }

//         temp = solvedMap.find(curr);

//         if (temp != solvedMap.end())
//         {
//             order.push_back(i);
//             order.push_back(temp->second);
//         }
//         else
//         {
//             currMap.insert({curr, i});
//         }
//     }

//     int diff;
//     for (unsigned int i = 0; i < 7; ++i)
//     {
//         int pos1[2] = {order.at(i) / 4, order.at(i) % 4};
//         int pos2[2] = {order.at(i + 1) / 4, order.at(i + 1) % 4};

//         if (pos1[0] != pos2[0])
//         {
//             sum++;
//         }
//         diff = pos1[1] - pos2[1];
//         if (diff == 2 || diff == -2)
//         {
//             sum += 2;
//         }
//         else if (diff == 0)
//         {
//             if (!checkCubette(cubettes[i]))
//             {
//                 sum += 2;
//             }
//         }
//         else
//         {
//             ++sum; // can be fixed
//         }
//     }
//     return sum / 4;
// }
