#include<solvers.h>


Index BackTrackSolver::findUnassigned(vector<vector<int>> entries){
    for(int i=0;i<entries.size();i++)
        for(int j=0;j<entries[0].size();j++)
            if(entries[i][j]==0)
                return make_tuple(i,j);

    return make_tuple(-1,-1);
}

set<int> BackTrackSolver::possibilities(Sudoku sudoku, Index unassigned){
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
    
    Index unassigned = this->findUnassigned(sudoku.entries);

    set<int> possibilities = this->possibilities(sudoku, unassigned); 
    if(possibilities.size()==0)
        return false;
    
    for(const int& possibility: possibilities){
        sudoku.entries[get<0>(unassigned)][get<1>(unassigned)] = possibility;
        bool solved = Solver(sudoku);
        if(solved)
            return true;
    }

    sudoku.entries[get<0>(unassigned)][get<1>(unassigned)] = 0;
    return false;
}