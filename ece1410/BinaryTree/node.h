#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

class node {
public:
	node* get_left();
	node* get_right();
	int get_val();
	void set_right(node *);
	void set_left(node *);
	void set_val(int);
private:
	node *left, *right;
	int val;
};

#endif