#include <sudoku.h>


bool IsUnique(vector<int> list){
	sort(list.begin(), list.end());
	auto it = unique(list.begin(), list.end());
	return (it==list.end());
};


Sudoku::Sudoku(vector<vector<int>> arg_entries){
	entries = arg_entries;
}

Sudoku::Sudoku(string line){
	for(int i=0;i<9;i++)
	{
		vector<int>row;
		for(int j=0;j<9;j++)
		{
			int position = i*9 + j;
			char entry = line[position];
			if(entry == '.')
				row.push_back(0);
			else
				row.push_back((int)entry - (int)'0');
		}
		entries.push_back(row);
	}
}

bool Sudoku::checkComplete(){
	bool Complete = true;
	for(const vector<int>& row: entries)
		for(const int& entry: row)
			if(entry == 0){
				Complete = false;
				break;
			}
	return Complete;
}

bool Sudoku::CheckCorrect(){

	// Completeness Check
	if(!this->checkComplete())
		return false;

	// Check Rows
	for(const vector<int>& row: entries){
		if(!IsUnique(row))
			return false;
	}

	// Check Columns
	for(int j=0;j<entries[0].size();j++){
		vector<int> column;
		for(int i=0;i<entries.size();i++)
			column.push_back(entries[i][j]);
		if(!IsUnique(column))
			return false;
	}

	// Check Boxes
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			vector<int> box;
			for(int x=0;x<3;x++)
				for(int y=0;y<3;y++)
					box.push_back(entries[i*3+x][j*3+y]);
			if(!IsUnique(box))
				return false;
		}
	}
	return true;
}

ostream& operator<<(ostream& os, const Sudoku& sudoku){
	os<<endl;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++)
			os<<sudoku.entries[i][j]<<" ";
		os<<endl;
	}
	os<<endl;
	return os;
}

