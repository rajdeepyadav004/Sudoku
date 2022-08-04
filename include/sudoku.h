#ifndef SUDOKU
#define SUDOKU

#include <bits/stdc++.h>

using namespace std;

class Sudoku{

private:
	vector<vector<int>> entries;
public:

    Sudoku(vector<vector<int>> arg_entries);
    Sudoku(string line);
    bool checkComplete(); 
    bool CheckCorrect();

    vector<vector<int>> getRowIndices(vector<int> index);
    vector<vector<int>> getColIndices(vector<int> index);
    vector<vector<int>> getBoxIndices(vector<int> index);

    vector<int> getRow(vector<int> index);
    vector<int> getCol(vector<int> index);
    vector<int> getBox(vector<int> index);
	
	friend ostream& operator<<(ostream& os, const Sudoku& sudoku);
	friend class BackTrackSolver;
	friend class BackTrackPlus;
};

#endif