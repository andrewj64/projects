#include"sudoku.h"

using namespace std;

/**********************************************************************
* Function title: main
* Summary: Prompts the user for a number of cells to populate in a sudoku solver, then solves the puzzle if possible.
***********************************************************************
* Pseudocode
* Begin
*	Print prompt
*	Get integer from keyboard
*	Populate grid
*	Print grid
*	If unsolvable
*		Print Sorry, unsolvable
*	Else
*		Print grid
*	EndIf
* End
***********************************************************************/

int main()
{
	int n, d;
	cout << "Welcome to SudokuSolver!!" << endl;					// Print prompt
	cout << "Enter number of squares to prepopulate: ";
	cin >> n;														// Get integer from keyboard
	Sudoku s(n);													// Populate grid
	//cout << "populated\n";
	s.print_grid();													// Print grid
	//cout << "Press any key and enter to solve \n";
	//cin >> d;
	if (!(s.solve()))												
	{
		cout << "Sorry, unsolvable..." << endl;						// unsolvable :(
	}
	else 
	{
		cout << "Solved!" << endl;
		s.print_grid();												// Print grid! :)
	}

	cin >> n;
	return 0;
}