#include<bits/stdc++.h>
#include<fstream>
#include<sudoku.h>
#include<solvers.h>

using namespace std;

inline void printVector(vector<int> vec){
	for(auto ele: vec)
		cout<<ele<<" ";
	cout<<endl;
}


int main(){
	
	vector<Sudoku> puzzles = PuzzleListFromFile("..\\data\\puzzles0_kaggle", 10);
	
	for(Sudoku& puzzle: puzzles){
		BackTrackSolver mySolver;
		mySolver.Solver(puzzle);
		cout<<puzzle.CheckCorrect()<<endl;
	}

	return 0;
}