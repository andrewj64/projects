#include"btree.h"
#include"walrus.h"

using namespace std;

/****************************************************************
* Function title: print_tree
* Summary: prints the entire binary tree recursively
*****************************************************************/

void btree::print_tree(node *n, ostream& output)
{
	if(n == root)
	{
		output << "    Value   " << '|' << "   Log10   " << endl;
		output << " ___________" << '|' << "___________" << endl;
	}
	if (n)
	{
		print_tree(n->get_left(), output);								// Print left branch
		output << '|' <<'\t' << n->get_val() << "\t\t|\t" << log10(n->get_val()) << '\t' << '|' << endl;	// Print node and log10 value
		print_tree(n->get_right(), output);								// Print right branch
	}	
}

/****************************************************************
* Function title: delete_node
* Summary: deletes a node from a binary tree
*****************************************************************
* Pseudocode
* Begin
* Find position in tree
* If value is less than current value
*	If left branch exists
*		go left
*	Else
*		doesn't exist
*	EndIf
* Else If value is greater than current value
*	If right branch exists
*		go right
*	Else
*		doesn't exist
*	EndIf
* Else node exists. End him!!!
*	If no children
*		If root with no children
*			set root to null
*			delete root and return
*		EndIf
*		If last move was left
*			set previous left to null
*			delete current and return
*		Else
*			Set previous right to null
*			delete current and return
*		EndIf
*	EndIf
*	If only left child
*		If root with only left child
*			set root to left branch
*			delete root and return
*		EndIf
*		if last move was left
*			set previous left to current left
*			delete current and return
*		Else
*			set previous right to current left
*			delete current and return
*		EndIf
*	If only right child
*		If root with only right child
*			set root to right branch
*			delete current and return
*		EndIf
*		If last move was left
*			set previous left to current right
*			delete current and return
*		Else
*			set previous right to current right
*			delete current and return
*		EndIf
*	If dos chilluns
*		Move right then left as far as you can go
*		Swap values
*		If mvoed left affter moving right
*			set previous left to null
*		Else
*			set node right to current right
*			delete current and return
*		EndIf
*	EndIf
* EndIf
* End
*****************************************************************/

void btree::delete_node(int val)
{
	int left, loop;
	node *cur, *prev;
	cur = root;
	prev = NULL;

	if (!root)
	{
		cout << "empty list" << endl;
		return;
	}
	
	while(1)	// Loop forever
	{														// find position in tree
		if(val < cur->get_val())							// If value is less than current value
		{
			if(cur->get_left())								// 	If left branch exists
			{
				left = 1;									//		go left
				prev = cur;
				cur = cur->get_left();
			}
			else										
			{
				cout << val << " doesn't exist" << endl;	//	Else
				walrus();									// 		doesn't exist
				return;
			}
		}
		else if(val > cur->get_val())						// Else If value is greater than current value
		{
			if(cur->get_right())							//	If right branch exists
			{
				left = 0;									//		go right
				prev = cur;
				cur = cur->get_right();
			}
			else											//	Else
			{
				cout << val << " doesn't exist" << endl;	// 		doesn't exist
				walrus();
				return;
			}
		}
		else
		{
															// Else node exists. End him!!!!
			if(!cur->get_left() && !cur->get_right())		// 	If no children
			{
				if(!prev) 									//		If root with no children
				{
					root = NULL;							//			delete root and return
					delete cur;
					return;
				}
				if(left)									//		If last move was left
				{
					prev->set_left(NULL);					//			Set previous left to null
					delete cur;								//			delete current and return
					return;
				}
				else										//		Else
				{
					prev->set_right(NULL);					//			Set previous right to null
					delete cur;								//			delete current and return
					return;
				}
			}	
			if(cur->get_left() && !cur->get_right())		// If only left child
			{
				if(!prev)									//	If root with only left child
				{
					root =  cur->get_left();				//		Set root to left branch
					delete cur;								//		delete current and return
					return;
				}
				if(left)									//	If last move was left
				{
					prev->set_left(cur->get_left());		//		set previous left to current left
					delete cur;								//		delete current and return
					return;
				}
				else										//	Else
				{		
					prev->set_right(cur->get_left());		//		set previous right to current left
					delete cur;								//		delete current and return
					return;
				}
			}
			if(!cur->get_left() && cur->get_right())		// If only right child
			{
				if(!prev)									//	If root with only right child
				{
					root =  cur->get_right();				//		Set root to right branch
					delete cur;								//		delete current and return
					return;
				}
				if(left)									//	If last move was left
				{
					prev->set_left(cur->get_right());		//		set previous left to current right
					delete cur;								//		delete current and return
					return;
				}
				else										//	Else
				{
					prev->set_right(cur->get_right());		//		set previous right to current right
					delete cur;								//		delete current and return
					return;
				}
			}
			
			if(cur->get_left() && cur->get_right())			// If dos chilluns
			{
				node *p = cur;
				prev = cur;
				cur = cur->get_right();						// 	Move right then left as far as you can go

				loop = 0;									
				while(cur->get_left())
				{
					loop = 1;
					prev = cur;
					cur = cur->get_left();
				}
				
				p->set_val(cur->get_val());					//	Swap values
				if (loop)									//	If moved left after moving right
					prev->set_left(NULL);					//		set previous left to null
				else										//	Else
					p->set_right(cur->get_right());			// 		set node right to current right
				delete cur;									//		delete current and return
				return;
			}
			// Something didn't work if you got this far
			cout << "Ummm this is awkward" << endl;
			return;
		}
	}
}

/****************************************************************
* Function title: add_node
* Summary: adds a node to a binary tree
*****************************************************************
* Pseudocode
* Begin
* Birth new node
* If no memory
*	Cry and exit in quick succession
* If empty tree
*	set root to new node and return
* EndIf
* Loop forever
*	If value is less than current value
*		If left branch exists
*			go left
*		Else
*			set current left to new node and return
*		EndIf
*	Else If value is less than current value
*		If right branch exists
*			go right
*		Else
*			set current right to new node and return
*	Else value already exists
*		delete new node and return
* End
****************************************************************/

void btree::add_node(int val)
{
	node *cur;
	cur = root;
	node *new_node = new node;							// Birth new node
	if (new_node == NULL)								// If no memory
	{
		cout << "I'm going to cry now." << endl;		//	Cry and exit in quick succession
		exit(1);
	}
	new_node->set_val(val);
	new_node->set_left(NULL);
	new_node->set_right(NULL);
	if(root == NULL)									// If empty tree 
	{
		root = new_node;								// set root to new node and return
		return;
	}
	
	while(1)											// Loop forever
	{
		if(val < cur->get_val())						// 	If value is less than current value
		{
			if(cur->get_left())							//		If left branch exists
				cur = cur->get_left();					//			go left
			else										//		Else
			{
				cur->set_left(new_node);				//			set current left to new node and return
				return;
			}
		}
		else if(val > cur->get_val())					//	Else If value is less than current value
		{
			if(cur->get_right())						//		If right branch exists
				cur = cur->get_right();					//			go right
			else										//		Else
			{
				cur->set_right(new_node);				//			set current right to new node and return
				return;
			}
		}
		else											// Else value already exists in tree
		{
			cout << val << " is already in the tree, ya doofus" << endl;
			delete new_node;							//	delete new node and return
			return;
		}
	}

	
}

node* btree::get_root()
{
	return root;										// yup
}

btree::btree()
{
	root = NULL;
}

/****************************************************************
* Function title: clean_up
* Summary: deletes the entire binary tree recursively
*****************************************************************/

void btree::clean_up(node *n)
{
	if(n->get_left())									// delete left branch
		clean_up(n->get_left());
	if(n->get_right())									// delete right branch
		clean_up(n->get_right());
	delete n;											// delete node
}












