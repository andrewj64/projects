

deleting a node with no children

loop through tree until you find the right node
if it doesn't exist
	do nothing (return)

cur = node to be deleted
prev = prev node
prev.left = null


only left child
prev.right = cur.left


only right child
prev.left = cur.right

two children
node to be deleted = left then right as far as you can go

/*
Pseudocode
Begin
	find node's position in tree
	cur = p;
	prev = NULL;
	If cur is null
		cry
	Else
		If cur has no children
			if cur->val > prev->val
				prev->right = NULL;
			else
				prev->right = NULL;
			delete cur;
		Else
			If cur only has left child
				If cur->val > prev->val
					prev->right = cur->left
				Else
					prev->left = cur->left;
				EndIf
			Else if cur only has right child
			...
			Else 
				cur = cur->right;
				while(cur->left)
					cur = cur->left;
				num = cur->val;
				delete_node(cur);
				
			
			
*/

/*
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
*

*/




/*
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
*
*/





/*
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
	
*/



















