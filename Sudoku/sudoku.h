#include<iostream>
#include<cstdbool>
#include<ctime>

#ifndef SUDOKU
#define SUDOKU

class Sudoku
{
private:
	bool check_row(int y, int v);
	bool check_col(int x, int v);
	bool check_box(int x, int y, int v);
	void first_square();
	bool prev_square();
	bool next_square();
	void last_square();
	int grid[9][9];
	int fixed[9][9];

	int *first, *prev, *next, *last;
	int x, y;
public:
	Sudoku(int n);
	bool solve();
	void print_grid();

};


#endif
