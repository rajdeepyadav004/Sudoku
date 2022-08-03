#include<bits/stdc++.h>
#include<fstream>
#include<sudoku.h>

using namespace std;

class BackTrackSolver{
	
public:
	vector<int> findUnassigned(vector<vector<int>> entries){
		for(int i=0;i<entries.size();i++)
			for(int j=0;j<entries[0].size();j++)
				if(entries[i][j]==0)
					return vector<int>{i,j};

		return vector<int>(-1,-1);
	}

	set<int> possibilities(vector<vector<int>> entries, vector<int> unassigned){
		
		set<int> res;
		for(int i=1;i<10;i++)
			res.insert(i);
		
		int row = unassigned[0];
		int column = unassigned[1];
		int box_x = row / 3, box_y = column/3;

		// row elimination
		for(const int& entry: entries[row])
			res.erase(entry);
		
		// column elimination
		for(int i=0;i<9;i++){
			res.erase(entries[i][column]);
		}

		// box elimination
		for(int i=box_x*3;i<box_x*3+3;i++){
			for(int j=box_y*3;j<box_y*3+3;j++){
				res.erase(entries[i][j]);
			}
		}

		return res;
	}

	bool Solver(Sudoku& sudoku){
			if(sudoku.checkComplete())
				return true;
			
			vector<int> unassigned = this->findUnassigned(sudoku.entries);

			set<int> possibilities = this->possibilities(sudoku.entries, unassigned); 
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
};


class BackTrackPlus: public BackTrackSolver{

	vector<vector<set<int>>> wavefunction;
public:

	void initWave(vector<vector<int>> entries){

		for(int i=0;i<9;i++){
			vector<set<int>> row;
			for(int j=0;j<9;j++){
				row.push_back(set<int>{1,2,3,4,5,6,7,8,9});
			}
			wavefunction.push_back(row);
		}

		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				if(entries[i][j]!=0)
					this->wavefunctionCollapse(vector<int>{i,j}, entries[i][j]);
			}
		}

	}

	vector<vector<int>> wavefunctionCollapse(vector<int> position, int state){
		
		int row = position[0];
		int column = position[1];
		int box_x = row / 3, box_y = column/3;

		vector<vector<int>> res; 
		// row Collapse
		for(int j=0;j<9;j++){
			if(j==column)
				continue;
			res.push_back(vector<int>{row,j});
			this->wavefunction[row][j].erase(state);
		}
		
		// column elimination
		for(int i=0;i<9;i++){
			if(i==row)
				continue;
			res.push_back(vector<int>{i,column});
			this->wavefunction[i][column].erase(state);
		}

		// box elimination
		for(int i=box_x*3;i<box_x*3+3;i++){
			for(int j=box_y*3;j<box_y*3+3;j++){
				if(i==row && j==column)
					continue;
				res.push_back(vector<int>{i,j});
				this->wavefunction[i][j].erase(state);
			}
		}
		
		return res;
	}

	void wavefunctionRemake(vector<int> position, int state);

	bool Solver(Sudoku& sudoku){

		if(sudoku.checkComplete())
			return true;
		
		if(wavefunction.size()==0)
			this->initWave(sudoku.entries);

		vector<int> unassigned = this->findUnassigned(sudoku.entries);

		if(wavefunction[unassigned[0]][unassigned[1]].size()==0)
			return false;
		
		set<int> CurrCellWavefunction = this->wavefunction[unassigned[0]][unassigned[1]];
		for(const int& possibility: wavefunction[unassigned[0]][unassigned[1]]){
			
			sudoku.entries[unassigned[0]][unassigned[1]] = possibility;
			vector<vector<int>> removed_positions = this->wavefunctionCollapse(unassigned, possibility);
			bool solved = Solver(sudoku);
			if(solved)
				return true;
			for(const vector<int>& position: removed_positions){
				this->wavefunction[position[0]][position[1]].insert(possibility);
			}
		}

		this->wavefunction[unassigned[0]][unassigned[1]] = CurrCellWavefunction;
		sudoku.entries[unassigned[0]][unassigned[1]] = 0;
		return false;
	}
};

vector<Sudoku> PuzzleListFromFile(string filename, int num_puzzles){

	ifstream file(filename);
	vector<Sudoku> puzzles;
	string puzzle;
	int count = 0;
	while(getline(file, puzzle)){

		if(puzzle.size()==0 || puzzle[0]=='#')
			continue;
		puzzles.push_back(Sudoku(string(puzzle)));
		
		++count;
		if(count==num_puzzles)
			break;

	}
	return puzzles;
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