#ifndef SUDOKU
#define SUDOKU

#include <bits/stdc++.h>

using namespace std;

typedef tuple<int,int> Index;

class Sudoku{

private:
	vector<vector<int>> entries;
public:

    Sudoku(vector<vector<int>> arg_entries);
    Sudoku(string line);
    bool checkComplete(); 
    bool CheckCorrect();

    vector<Index> getRowIndices(Index index);
    vector<Index> getColIndices(Index index);
    vector<Index> getBoxIndices(Index index);

    vector<int> getRow(Index index);
    vector<int> getCol(Index index);
    vector<int> getBox(Index index);
	
	friend ostream& operator<<(ostream& os, const Sudoku& sudoku);
	friend class BackTrackSolver;
	friend class BackTrackPlus;
};

vector<Sudoku> PuzzleListFromFile(string filename, int num_puzzles);

#endif