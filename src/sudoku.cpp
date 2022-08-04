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

vector<vector<int>> Sudoku::getRowIndices(vector<int> index){
	int row = index[0];
	int col = index[1];
	vector<vector<int>> RowIndices;
	for(int j=0;j<9;j++)
	{
		if(j==col)
			continue;
		RowIndices.push_back(vector<int>{row,j});
	}
	return RowIndices;
}

vector<vector<int>> Sudoku::getColIndices(vector<int> index){
	int row = index[0];
	int col = index[1];
	vector<vector<int>> ColIndices;
	for(int i=0;i<9;i++)
	{
		if(i==row)
			continue;
		ColIndices.push_back(vector<int>{i,col});
	}
	return ColIndices;
}

vector<vector<int>> Sudoku::getBoxIndices(vector<int> index){
	int row = index[0];
	int col = index[1];
	int box_x = row/3;
	int box_y = col/3;

	vector<vector<int>> BoxIndices;
	for(int i=3*box_x;i<3*box_x+3;i++)
	{
		for(int j=3*box_y;j<3*box_y+3;j++){
			if(i==row && j==col)
				continue;
			BoxIndices.push_back(vector<int>{i,j});
		}
	}
	return BoxIndices;
}

vector<int> Sudoku::getRow(vector<int> index){
	vector<vector<int>> rowIndices = getRowIndices(index);
	vector<int> row;
	for(vector<int> index: rowIndices)
		row.push_back(entries[index[0]][index[1]]);
	return row;
}

vector<int> Sudoku::getCol(vector<int> index){
	vector<vector<int>> colIndices = getColIndices(index);
	vector<int> col;
	for(vector<int> index: colIndices)
		col.push_back(entries[index[0]][index[1]]);
	return col;
}

vector<int> Sudoku::getBox(vector<int> index){
	vector<vector<int>> BoxIndices = getBoxIndices(index);
	vector<int> Box;
	for(vector<int> index: BoxIndices)
		Box.push_back(entries[index[0]][index[1]]);
	return Box;
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

