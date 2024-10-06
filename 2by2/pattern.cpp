// cube = "RRRRGGGGYYYYBBBBWWWWOOOO";
#include "state.h"
#include <iostream>
#include <queue>

int main()
{
    State curr;
    State newState;

    bool done = false;
    std::string rotations[9] = {"R", "R'", "R2", "U", "U'", "U2", "F", "F'", "F2"};

    std::array<std::array<int, 24>, 24> pattern;
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
        // std::cout << curr.moves.size() << std::endl;

        // std::cout << "curr" << std::endl;
        // curr.printState();

        for (int i = 0; i < 9; ++i)
        {
            newState = curr;
            // TODO = operator

            // turn cube
            newState.turn(i);
            // newState.printState();

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
    for (int j = 0; j < 24; ++j)
    {
        for (int k = 0; k < 24; ++k)
        {
            std::cout << pattern[j][k] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
