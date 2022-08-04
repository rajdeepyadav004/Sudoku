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
	entries.resize(9, vector<int>(9,0));
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			int position = i*9 + j;
			char entry = line[position];
			if(entry == '.')
				(*this)[{i,j}] = 0;
			else
				(*this)[{i,j}]= (int)entry - (int)'0';
		}
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

vector<Index> Sudoku::getRowIndices(Index index){
	int row = get<0>(index);
	int col = get<1>(index);
	vector<Index> RowIndices;
	for(int j=0;j<9;j++)
	{
		if(j==col)
			continue;
		RowIndices.push_back(make_tuple(row,j));
	}
	return RowIndices;
}

vector<Index> Sudoku::getColIndices(Index index){
	int row = get<0>(index);
	int col = get<1>(index);
	vector<Index> ColIndices;
	for(int i=0;i<9;i++)
	{
		if(i==row)
			continue;
		ColIndices.push_back(make_tuple(i,col));
	}
	return ColIndices;
}

vector<Index> Sudoku::getBoxIndices(Index index){
	int row = get<0>(index);
	int col = get<1>(index);
	int box_x = row/3;
	int box_y = col/3;

	vector<Index> BoxIndices;
	for(int i=3*box_x;i<3*box_x+3;i++)
	{
		for(int j=3*box_y;j<3*box_y+3;j++){
			if(i==row && j==col)
				continue;
			BoxIndices.push_back(make_tuple(i,j));
		}
	}
	return BoxIndices;
}

vector<int> Sudoku::getRow(Index index){
	vector<Index> rowIndices = getRowIndices(index);
	vector<int> row;
	for(Index index: rowIndices)
		row.push_back((*this)[index]);
	return row;
}

vector<int> Sudoku::getCol(Index index){
	vector<Index> colIndices = getColIndices(index);
	vector<int> col;
	for(Index index: colIndices)
		col.push_back((*this)[index]);
	return col;
}

vector<int> Sudoku::getBox(Index index){
	vector<Index> BoxIndices = getBoxIndices(index);
	vector<int> Box;
	for(Index index: BoxIndices)
		Box.push_back((*this)[index]);
	return Box;
}

int& Sudoku::operator[](const Index& index){
	return entries[get<0>(index)][get<1>(index)];
}

int Sudoku::operator[](const Index& index) const{
	return entries[get<0>(index)][get<1>(index)];
}

ostream& operator<<(ostream& os, const Sudoku& sudoku){
	os<<endl;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++)
			os<<sudoku[{i,j}]<<" ";
		os<<endl;
	}
	os<<endl;
	return os;
}

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
