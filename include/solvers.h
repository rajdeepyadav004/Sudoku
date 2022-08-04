#ifndef SOLVER
#define SOLVER

#include<bits/stdc++.h>
#include<sudoku.h>
using namespace std;

class BackTrackSolver{

public:
    vector<int> findUnassigned(vector<vector<int>> entries);
    set<int> possibilities(Sudoku sudoku, vector<int> unassigned);
    bool Solver(Sudoku& sudoku);
};

#endif