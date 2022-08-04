#include<solvers.h>


vector<int> BackTrackSolver::findUnassigned(vector<vector<int>> entries){
    for(int i=0;i<entries.size();i++)
        for(int j=0;j<entries[0].size();j++)
            if(entries[i][j]==0)
                return vector<int>{i,j};

    return vector<int>(-1,-1);
}

set<int> BackTrackSolver::possibilities(Sudoku sudoku, vector<int> unassigned){
    set<int> res;
    for(int i=1;i<10;i++)
        res.insert(i);
    
    // row elimination
    for(const int& entry: sudoku.getRow(unassigned))
        res.erase(entry);
    
    // column elimination
    for(const int& entry: sudoku.getCol(unassigned))
        res.erase(entry);

    // box elimination
    for(const int& entry: sudoku.getBox(unassigned))
        res.erase(entry);

    return res;
}

bool BackTrackSolver::Solver(Sudoku& sudoku){
    if(sudoku.checkComplete())
        return true;
    
    vector<int> unassigned = this->findUnassigned(sudoku.entries);

    set<int> possibilities = this->possibilities(sudoku, unassigned); 
    if(possibilities.size()==0)
        return false;
    
    for(const int& possibility: possibilities){
        sudoku.entries[unassigned[0]][unassigned[1]] = possibility;
        bool solved = Solver(sudoku);
        if(solved)
            return true;
    }

    sudoku.entries[unassigned[0]][unassigned[1]] = 0;
    return false;
}