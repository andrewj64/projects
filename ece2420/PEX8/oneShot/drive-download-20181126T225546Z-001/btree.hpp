#ifndef BTREE_HPP
#define BTREE_HPP

#include"node.h"

using namespace std;

class btree {
private:
	node *root;
public:
	btree();
	void add_node(int);
	void delete_node(int);
	void print_tree(node *n, ostream& output);
	node* get_root();
	void clean_up(node *);
};

#endif