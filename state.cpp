#include "state.h"
#include <iostream>
#include <random>
#include <chrono>
#include <unordered_map>
#include <stack>
#include <unordered_set>

State::State()
{
    for (int i = 0; i < 24; ++i)
    {
        cube[i] = i;
    }
}

State &State::operator=(const State &rhs)
{
    cube = rhs.cube;
    moves = rhs.moves;
    return *this;
}

void State::printState()
{
    // R
    for (unsigned int i = 0; i < 2; ++i)
    {
        std::cout << "   ";
        for (unsigned int j = 0; j < 2; ++j)
        {
            if (cube[(i * 2) + j] < 10)
                std::cout << " ";
            std::cout << cube[(i * 2) + j] << " ";
        }
        std::cout << std::endl;
    }

    // G,Y,B,W
    for (unsigned int i = 0; i < 2; ++i)
    {
        for (unsigned int j = 1; j < 5; ++j)
        {
            for (unsigned int k = 0; k < 2; ++k)
            {
                if (cube[(i * 2 + j * 4 + k)] < 10)
                    std::cout << " ";
                std::cout << cube[(i * 2 + j * 4 + k)] << " ";
            }
        }
        std::cout << std::endl;
    }

    // O
    for (unsigned int i = 0; i < 2; ++i)
    {
        std::cout << "   ";
        for (unsigned int j = 20; j < 22; ++j)
        {
            if (cube[(i * 2) + j] < 10)
                std::cout << " ";
            std::cout << cube[(i * 2) + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void State::turn(const int direction)
{
    // directions = {"R", "R'", "R2", "U", "U'", "U2", "F", "F'", "F2"};
    const std::vector<std::vector<int>> tapes{
        {1, 3, 9, 11, 21, 23, 18, 16},
        {16, 18, 23, 21, 11, 9, 3, 1},
        {16, 18, 23, 21, 11, 9, 3, 1},
        {5, 7, 20, 21, 14, 12, 3, 2},
        {2, 3, 12, 14, 21, 20, 7, 5},
        {2, 3, 12, 14, 21, 20, 7, 5},
        {19, 18, 15, 14, 11, 10, 7, 6},
        {6, 7, 10, 11, 14, 15, 18, 19},
        {6, 7, 10, 11, 14, 15, 18, 19}};

    const std::vector<std::vector<int>> faces{
        {14, 15, 13, 12},
        {12, 13, 15, 14},
        {12, 13, 15, 14},
        {10, 11, 9, 8},
        {8, 9, 11, 10},
        {8, 9, 11, 10},
        {22, 23, 21, 20},
        {20, 21, 23, 22},
        {20, 21, 23, 22}};

    _turn(tapes[direction], faces[direction]);

    if (direction % 3 == 2)
    {
        _turn(tapes[direction], faces[direction]);
    }

    moves.push_back(direction);
}

void State::_turn(const std::vector<int> &tape, const std::vector<int> &face)
{
    int temp;
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

void State::scramble()
{
    int numMoves = 100;
    int prevFace = -1;
    int direction;
    std::mt19937 random(std::time(0));
    // std::mt19937 random(0);

    std::cout << "scramble: \t";
    for (int i = 0; i < numMoves; ++i)
    {
        direction = random() % 9;
        if ((direction / 3) != prevFace)
        {
            turn(direction);
            prevFace = direction / 3;
            std::cout << direction << " ";
        }
        else
        {
            --i;
        }
    }
    std::cout << std::endl;
    moves = {};
}

bool State::check()
{
    for (int i = 0; i < 24; ++i)
    {
        if (cube[i] != i)
            return false;
    }
    return true;
}

void State::computePattern(std::vector<std::vector<int>> &pattern)
{
    // returns pattern database in pattern
    State curr;
    State newState;

    bool done = false;
    std::string rotations[9] = {"R", "R'", "R2", "U", "U'", "U2", "F", "F'", "F2"};

    std::queue<State> q;

    for (int i = 0; i < 24; ++i)
    {
        for (int j = 0; j < 24; ++j)
        {
            if (((i == j || i == 0) || (i == 4) || (i == 17)) || ((j == 0) || (j == 4) || (j == 17)))
            {
                pattern[i][j] = 0;
            }
            else
            {
                pattern[i][j] = -1;
            }
        }
    }
    q.push(curr);

    while (curr.moves.size() < 4)
    {
        curr = q.front();
        q.pop();

        for (int i = 0; i < 9; ++i)
        {
            newState = curr;

            // turn cube
            newState.turn(i);

            // check cube
            for (int j = 0; j < 24; ++j)
            {
                // if not in the correct position
                if (newState.cube[j] != j)
                {
                    if (pattern[j][newState.cube[j]] == -1)
                    {
                        pattern[j][newState.cube[j]] = newState.moves.size();
                    }
                }
            }
            q.push(newState);
        }
    }
}

bool State::iddfs(int& count)
{
    auto start = std::chrono::high_resolution_clock::now();
    bool found = false;

    for (int i = 0; i < 11; ++i)
    {
        if (dls(i, count))
        {
            found = true;
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - start;

    std::cout << "average visited per second " << count / std::chrono::duration<double>(diff).count() << std::endl;
    return found;
}

bool State::dls(int limit, int &count)
{
    // if at max depth, check if solved
    if (limit == 0)
    {
        if (check())
        {
            std::cout << "solution found " << moves.size();
            return true;
        }
        return false;
    }

    // recurrence dfs
    State newState;
    int prevFace = -1;
    std::string cubeStr;
    if (moves.size() != 0)
    {
        prevFace = moves.back() / 3;
    }
    for (int i = 0; i < 9; ++i)
    {
        // skip if moving same face
        if (prevFace != i / 3)
        {
            newState = *this;
            newState.turn(i);
            count++;

            if (newState.dls(limit - 1, count))
                return true;
        }
    }

    // goal not found
    return false;
}

bool State::biddfs(int& count)
{
    std::unordered_map<std::string, State> edges1;
    std::unordered_map<std::string, State> edges2;
    bool solved;
    for (int k = 0; k < 6; ++k)
    {
        // std::cout << "k:\t" << k << std::endl;
        edges1.clear();
        State goal1;
        goal1.biddfs_goal(k, edges1, count);

        edges2.clear();
        State goal2;
        goal2.biddfs_goal(k + 1, edges2, count);

        std::unordered_map<std::string, int> visited;

        std::stack<State> frontier;
        frontier.push(*this);
        State curr;

        int prevFace;
        bool solved = false;
        int solution;

        std::string cubeStr;
        cubeStr.reserve(38);

        while (!frontier.empty())
        {
            curr = frontier.top();
            frontier.pop();
            count++;

            // if curr is at limit, compare to goal edges
            if (curr.moves.size() == k)
            {
                cubeStr = "";
                cubeStr.reserve(38);
                for (int j = 0; j < 24; ++j)
                {
                    cubeStr += std::to_string(curr.cube[j]);
                }

                auto it = edges1.find(cubeStr);
                if (it != edges1.end())
                {
                    std::cout << "solution found in " << it->second.moves.size() + curr.moves.size() << std::endl;
                    return true;
                }
                it = edges2.find(cubeStr);
                if (it != edges2.end())
                {
                    solved = true;
                    solution = it->second.moves.size() + curr.moves.size();
                }
            }
            else
            {
                if (curr.moves.size() != 0)
                {
                    prevFace = curr.moves.back() / 3;
                }
                else
                {
                    prevFace = -1;
                }

                for (int i = 0; i < 9; ++i)
                {
                    // skip if moving same face
                    if (prevFace != i / 3)
                    {
                        State newState = curr;
                        newState.turn(i);

                        cubeStr = "";
                        cubeStr.reserve(38);

                        for (int j = 0; j < 24; ++j)
                        {
                            cubeStr += std::to_string(newState.cube[j]);
                        }

                        // if is not already visited, add to stack
                        if (visited.count(cubeStr) == 0)
                        {
                            visited[cubeStr] = newState.moves.size();
                            frontier.push(newState);
                        }
                        // elif already visited and improved, add to stack
                        else if (visited[cubeStr] > newState.moves.size())
                        {
                            visited[cubeStr] = newState.moves.size();
                            frontier.push(newState);
                        }
                    }
                }
            }
        }
        if (solved)
        {
            std::cout << "solution found in " << solution << std::endl;
            return true;
        }
    }
    return false;
}

void State::biddfs_goal(int limit, std::unordered_map<std::string, State> &edges, int& count)
{
    std::unordered_map<std::string, int> visited;

    std::stack<State> frontier;
    frontier.push(*this);
    State curr;

    int prevFace;
    bool solved = true;

    std::string cubeStr;
    cubeStr.reserve(38);

    while (!frontier.empty())
    {
        curr = frontier.top();
        frontier.pop();

        // if curr is at limit, add to edges
        if (curr.moves.size() == limit)
        {
            cubeStr = "";
            cubeStr.reserve(38);

            for (int j = 0; j < 24; ++j)
            {
                cubeStr += std::to_string(curr.cube[j]);
            }
            edges[cubeStr] = curr;
        }
        else
        {
            if (curr.moves.size() != 0)
            {
                prevFace = curr.moves.back() / 3;
            }
            else
            {
                prevFace = -1;
            }

            for (int i = 0; i < 9; ++i)
            {
                // skip if moving same face
                if (prevFace != i / 3)
                {
                    State newState = curr;
                    newState.turn(i);

                    cubeStr = "";
                    cubeStr.reserve(38);

                    for (int j = 0; j < 24; ++j)
                    {
                        cubeStr += std::to_string(newState.cube[j]);
                    }

                    // if is not already visited, add to stack
                    if (visited.count(cubeStr) == 0)
                    {
                        visited[cubeStr] = newState.moves.size();
                        frontier.push(newState);
                    }
                    // elif already visited and improved, add to stack
                    else if (visited[cubeStr] > newState.moves.size())
                    {
                        visited[cubeStr] = newState.moves.size();
                        frontier.push(newState);
                    }
                    count++;
                }
            }
        }
    }
}

int State::misplacedHeuristic()
{
    // returns the number of misplaced tiles
    int count = 0;
    for (int i = 0; i < 24; ++i)
    {
        if (cube[i] != i)
            count++;
    }
    return count;
}

double State::patternHeuristic(std::vector<std::vector<int>> &pattern)
{
    double total = 0;
    for (int i = 0; i < 24; ++i)
    {
        total += pattern[i][cube[i]];
    }
    return total / 12.0;
}

bool State::ida(int &count)
{
    std::vector<std::vector<int>> pattern(
        24,
        std::vector<int>(24));
    computePattern(pattern);
    int threshold = patternHeuristic(pattern);

    return idaHelper(threshold, pattern, count);
}

bool State::idaHelper(double threshold, std::vector<std::vector<int>> &pattern, int &count)
{
    // std::cout << "curr threshold\t:" << threshold << std::endl;
    double min = MAXFLOAT;
    std::stack<State> frontier;
    frontier.push(*this);
    State curr;

    int prevFace;
    double f;

    while (!frontier.empty())
    {
        curr = frontier.top();
        frontier.pop();
        count++;

        // check if solution
        if (curr.check())
        {
            std::cout << "solution found in\t" << curr.moves.size() << std::endl;
            return true;
        }
        if (curr.moves.size() != 0)
        {
            prevFace = curr.moves.back() / 3;
        }
        else
        {
            prevFace = -1;
        }

        for (int i = 0; i < 9; ++i)
        {
            // skip if moving same face
            if (prevFace != i / 3)
            {
                State newState = curr;
                newState.turn(i);

                f = newState.moves.size() + newState.patternHeuristic(pattern);
                if (f <= threshold)
                {
                    frontier.push(newState);
                }
                else if (f < min)
                {
                    min = f;
                }
            }
        }
    }
    // once frontier is completed, re run with new threshold
    return idaHelper(min, pattern, count);
}

void State::testBench()
{
    int count = 0;
    auto start = std::chrono::high_resolution_clock::now();

    // cube[0] = -1;
    std::unordered_map<std::string, int> visited;

    // dls(12, visited, count);


    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - start;

    std::cout << "visited: " << count << std::endl
              << "average visited per second " << count / std::chrono::duration<double>(diff).count() << std::endl;
}

void State::testBench2()
{
    State state;

    std::unordered_map<std::string, int> temp;
    int count = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1; ++i)
    {
        state.scramble();
        // state.biddfs();
        state.ida(count);
        // state.biddfs(count);
        // state.iddfs(count);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - start;

    std::cout << "visited: " << count << std::endl
              << "average visited per second " << count / std::chrono::duration<double>(diff).count() << std::endl;
}