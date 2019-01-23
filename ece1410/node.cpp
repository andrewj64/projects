#include"btree.h"

using namespace std;

/**********************************************************************
* Summary: So ummm all of these functions are pretty self-explanatory.
*			These functions are used to access the prviate variables
*			of the node class
***********************************************************************/

node* node::get_left()
{
	return left;
}
node* node::get_right()
{
	return right;
}

int node::get_val()
{
	return val;
}

void node::set_right(node *n)
{
	right = n;
}

void node::set_left(node *n)
{
	left = n;
}

void node::set_val(int v)
{
	val = v;
}


