/*******************************************************************
* Function Title: main
* Summary: Adds or deletes data from an input file to a binary tree
			and writes the result with the accompanying log10 value
********************************************************************
* Pseudocode
* Begin
*	Check for command line syntax
*	Open input and output files
*	If files failed to open
*		Cry, then exit
*	EndIf
* Loop until end of file
*	Read an operator
*	Read a value
*	If a
*		add value to binary tree
*	Else If d
*		delete value in tree
*	Else
*		Invalid operator
*	EndIf
* EndLoop
* Print binary tree to file
* Delete binary tree
* End
********************************************************************/

#include"btree.h"
#include"node.h"
#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char* argv[])
{
	ofstream output;
	ifstream input;
	char oper;
	int val;
	double log;
	btree tree;
	
	if(argc != 3)												// Check for command line syntax
	{
		cout<< "You're not very good at this." << endl;
		exit(1);
	}
	
	input.open(argv[1], ifstream::in);							// Open input and output files
	output.open(argv[2], ofstream::out);
	if(!input.good() || !output.good())							// If files failed to open
	{
		cout << "Your files suck. Wow." << endl;				// 	Cry, then exit
		cin.ignore();
		exit(1);
	}
	
	while(!input.eof())											// Loop until end of file
	{
		input >> oper;											// Read an operator 
		input >> val;											// Read a value
		if (oper == 'a')										// If a
			tree.add_node(val);									//	add value to binary tree
		else if(oper == 'd')									// Else If d
			tree.delete_node(val);								//	delete value in tree
		else													// Else
			cout << oper << "is an invalid operator." << endl;	//	Invalid operator
	}
	

	tree.print_tree(tree.get_root(), output);					// Print binary tree to file
	tree.clean_up(tree.get_root());								// Delete binary tree
	return 0;
}
















