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
	
	friend ostream& operator<<(ostream& os, const Sudoku& sudoku);
	friend class BackTrackSolver;
	friend class BackTrackPlus;
};

#endif