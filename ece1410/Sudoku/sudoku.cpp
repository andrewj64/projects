#include"sudoku.h"

using namespace std;

/**********************************************************************
* Function title: Sudoku constructor
***********************************************************************
* Pseudocode
* Begin
*	Initialize grids to 0
*	Loop
*		generate random position
*		If position is empty
*			generate random number
*			If number is valid at (x,y)
*				Place number
*				Add 1 to count
*			EndIf
*		EndIf
*	EndLoop when count = n
* End
***********************************************************************/

Sudoku::Sudoku(int n)
{
	char x, y, i, j;
	int count, v;
	srand(time(NULL));

	for (i = 0; i < 9; i++)		// Initialize grids to 0
	{
		for (j = 0; j < 9; j++)
		{
			grid[i][j] = 0;
			fixed[i][j] = 0;
		}
	}
	//cout << "initialized\n";
	//Loop
	
	for (count = 0; count < n;)			// Populate the grid with n random numbers 1-9
	{

		x = rand() % 9;			// generates 0-8
		y = rand() % 9;
		//cout << "random value!\n";
		if (fixed[x][y] == 0)										// check if square is empty
		{
			v = (rand() % 9 + 1);
			if (!(check_box(x, y, v)) && !check_col(x, v) && !check_row(y, v))	// check if valid
			{
				grid[x][y] = v;
				fixed[x][y] = 1;
				count++;
			}
			//cout << "value\n";
		}
	}
	
}

/**********************************************************************
* Function title: solve
***********************************************************************
* Pseudocode
* Begin
*	find first square
	n = 1
	Loop
	
	If grid[x][y] != n
		grid[x][y] = n
		move forward
	Else
		n++
		If n == 10
			move back
			If off grid
				FAIL
			Else
				n =  grid[x][y] + 1
			EndIf
		EndIf
	EndIf
	EndLoop
***********************************************************************/

bool Sudoku::solve()
{
	int n, *p;
	first_square();
	last_square();
	p = first;
	n = 1;
	do
	{
		if (!(check_box(x, y, n)) && !check_col(x, n) && !check_row(y, n))			// If no violations
		{
			grid[x][y] = n;															// Place n at (x,y)
			//fixed[x][y] = 1;
			if (x == 8 && y == 8)													// cases that mean the grid is solved. Not all were needed, but at least one of them works :)
				return true;
			if (*last != 0)
				return true;
			if (!(next_square()))
				return true;
			//cout << "next\n";
			//cout << "n = " << n << endl;
			//cout << "[" << x << "]" << "[" << y << "]" << endl;
			n = 1;																	// Set n = 1
			//print_grid();
			//cout << "\n\n";
		}
		else
		{
			
			if (n < 9)																// Don't increment n above 9 (bad things happen)
			{
				n++;	
			}
			else
			{
				grid[x][y] = 0;														// Clear square and move back
				if (!(prev_square()))												
				{
					return false;													// Check if off grid
				}
								// exit
				//cout << "back\n";
				if (grid[x][y] < 9)
				{
					n = grid[x][y] + 1;												// Set n to (x,y) + 1
				}

			}
			/*if (n > 9)
			{
				grid[x][y] = 0;
				if (!(prev_square()))			// move back and check if off grid
					return false;			// exit
				//cout << "back\n";
				if (grid[x][y] < 9)
				{
					n = grid[x][y] + 1;
				}
				else
				{
					prev_square();
				}
			}*/
		}

		if (n == 9 && &fixed[x][y] == first)											// mostly ignore these if statements. I don't think they work :)
			return false;
		//cout << "solve loop\n";
		if (&fixed[x][y] == last && fixed[x][y] == 1)
			return true;
	} while (x < 9 || y < 9);															// EndLoop when off the grid
	
	return true;
}

/**********************************************************************
* Function title: print_grid
***********************************************************************
* Pseudocode
* Begin
*	Loop through grid and print
*		Print * for empty spaces
*		Print number 
*	EndLoop
* End
***********************************************************************/

void Sudoku::print_grid()
{
	int x, y;
	for (y = 0; y < 9; y++)					// Step through grid and print 
	{
		for(x=0; x < 9; x++)
		{ 
			if (grid[x][y] == 0)			// Print a * for empty spaces
			{
				cout << "*\t";
			}
			else
			{
				cout << grid[x][y] << "\t";	// Print number
			}
			if (x == 8)
			{
				cout << "\n\n\n";			// new row
			}
		}
		
	}
}

/**********************************************************************
* Function title: check_row
***********************************************************************
* Pseudocode
* Begin
*	Loop through row
*		If values match
*			Duplicate found
*	EndLoop
*	No duplicates
* End
***********************************************************************/

bool Sudoku::check_row(int y, int v)
{
	int *p = &grid[0][y];
	for (int i = 0; i < 9; p++, i++)
	{
		if (grid[i][y] == v)
		{
			//cout << "row bad\n";
			return true;		// duplicate found
		}
	}
	//cout << "row good\n";
	return false;		// no duplicates
}

/**********************************************************************
* Function title: check_col
***********************************************************************
* Pseudocode
* Begin
*	Loop through column
*		If values match
*			no duplicates
*	EndLoop
*	No duplicates!
* End
***********************************************************************/
bool Sudoku::check_col(int x, int v)
{
	int *p = &grid[x][0];
	for (int i = 0; i < 9; i++)
	{
		if (grid[x][i] == v)		// duplicate found
		{
			//cout << "col bad\n";
			return true;
		}
	}
	//cout << "col good\n";
	return false;				// no duplicates
}

/**********************************************************************
* Function title: check_box
***********************************************************************
* Pseudocode
* Begin
*	Set position to top left of box
*	Loop through box
*		If values match
*			duplicate found
*	EndLoop
*	No duplicates!
* End
***********************************************************************/

bool Sudoku::check_box(int x, int y, int v)
{
	int xx = x - (x % 3);							//Set position to top left of box
	int yy = y - (y % 3);
	for (int j = 0; j < 3; j++)						// Loop through box
	{
		for (int i = 0; i < 3; i++)
		{
			if (grid[xx + i][yy + j] == v)
			{
				//cout << "box bad\n";
				return true;						// duplciate found
			}
		}
	}
	//cout << "box good\n";
	return false;									// no duplicates!!
}

/**********************************************************************
* Function title: first_square
***********************************************************************
* Pseudocode
* Begin
*	Set first pointer to first place where fixed grid is 0
*	Set (x,y) to first place where fixed grid is 0
* End
***********************************************************************/

void Sudoku::first_square()
{
	for (first = &fixed[0][0]; *first != 0; first++);	// Set first pointer to first place where fixed grid is 0 (for future use)

	for(y = 0; y < 9; y++)								// Set (x,y) to first place where fixed grid is 0
	{
		for (x = 0; x < 9; x++)
		{
			if (fixed[x][y] == 0)
			{
				//cout << "first found\n";
				return;
			}

		}
	}


	return;
}

/**********************************************************************
* Function title: prev_square
***********************************************************************
* Pseudocode
* Begin
*	Move back one
*	Loop until valid previous square is found
*		If fixed grid at (x,y) is empty
*			previous found!
*		If at first of row
*			Move up a row 
*		Else
*			Move back one
*		EndIf
*	EndLoop
* End
***********************************************************************/

bool Sudoku::prev_square()
{
	/*for (prev = &fixed[x][y]; *prev != 0; prev--)
	{
		if (prev == first)
		{
			cout << "Jumped off grid!\n";
			//exit(1);
		}
	}
	*/


	if (x == 0 && y > 0)							// Move back one
	{
		x = 8;	// move up a row
		y--;
	}
	else if (x > 0)
	{
		x--;
	}
	
	for(;y >= 0; y--)
	{
		for(;x >= 0;)
		{
			
			if (fixed[x][y] == 0 && &fixed[x][y] != first)
			{
				//cout << "prev found\n";
				return true;						// previous found!
			}
			if (x == 0)								// move up a row
			{
				x = 8;					
				break;
			}
			else
			{
				x--;
			}
			if (*first == 9 || &fixed[x][y] == first)	// Don't try to move off the grid
				return false;							// unsolvable
		}
		
								// move to end of the row
	}
	//cout << "jumped off grid!\n Unsolvable!";


	return false;
}

/**********************************************************************
* Function title: next_square
***********************************************************************
* Pseudocode
* Begin
*	move forward 1
*	Loop until next square is found
*		If fixed grid at (x,y) is empty
*			next found!
*		If at end of row
*			move down to next row
*		Else
*			move forward 1
*		EndIf
*	EndLoop
* End
*	
***********************************************************************/

bool Sudoku::next_square()
{
	
	for (next = &fixed[x][y]; *next != 0; next++)// Ignore this part
	{
		if (next == &fixed[8][8])
		{
			//cout << "Jumped off grid!\n";
			//exit(1);
		}
	}
	if (x == 8 && y < 8)							// Move forward 1
	{
		x = 0;
		y++;
	}
	else if (x < 8)
	{
		x++;
	}
	for (; y < 9; y++)								// Loop until next is found
	{
		for (; x < 9;)
		{
			if (fixed[x][y] == 0)
			{
				//cout << "next found\n";
				return true;						// next found
			}
			if (x == 8 && y < 8)
			{
				x = 0;							// move to beginning of next row
				y++;
			}
			else if (x < 8)
			{
				x++;							// move forward 1
			}
		}					
	}
	//cout << "jumped off grid!\n";
	//exit(1);

	return false;
}

void Sudoku::last_square()
{
	for (last = &fixed[8][8]; *last != 0; last--);			// Find last square
}
