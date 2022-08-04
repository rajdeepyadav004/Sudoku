#ifndef SOLVER
#define SOLVER

#include<bits/stdc++.h>
#include<sudoku.h>
using namespace std;

class BackTrackSolver{
public:
    Index findUnassigned(Sudoku sudoku);
    set<int> possibilities(Sudoku sudoku, Index unassigned);
    bool Solver(Sudoku& sudoku);
};

// // Wavefunction Collapse backtrack
// class WFCBackTrack{
// };

#endif