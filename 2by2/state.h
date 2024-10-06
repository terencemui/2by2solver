#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

class State
{
    public:
        std::array<int, 24> cube;
        std::vector<int> moves;

    public:
        State();
        State& operator=(const State&);
        void printState();
        void turn(const int);
        void _turn(const std::vector<int>&, const std::vector<int>&);
        void scramble();
        bool check();

        void computePattern(std::vector<std::vector<int>>&);

        bool iddfs(int&);
        bool dls(int, int&);
        bool biddfs(int&);
        void biddfs_goal(int, std::unordered_map<std::string, State>&, int&);
        int misplacedHeuristic();
        double patternHeuristic(std::vector<std::vector<int>>&);
        bool ida(int&);
        bool idaHelper(double, std::vector<std::vector<int>>&, int&);


        void testBench();
        void testBench2();
};
#endif