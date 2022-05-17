/*  "BST.h" */
/*  created by Johan Jaeger on 3/27/22. */

#ifndef BST_H
#define BST_H

#include <string>
#include <cmath>
#include <iostream>

using namespace std;

/* declarations. */

template <class T>
struct TreeNode;

template <class T>
ostream& operator << (ostream& os, const TreeNode<T>& node);

template <class T>
class BST;

template <class T>
ostream& operator << (ostream& os, const BST<T>& tree);

/* implementations. */

template <class T>
class TreeNode {
public:
    friend ostream& operator << (ostream& os, const TreeNode<T>& node){
        os << node.data << "(";
        
		if (node.left != NULL)
            os << *(node.left);
        else os << "_";
        os << ", ";
        if (node.right != NULL)
            os << *(node.right);
        else os << "_";
        
		os << ")";
        
		return os;
    }

	/* node pointers. */
    TreeNode<T>* parent;
    TreeNode<T>* left;
    TreeNode<T>* right;

	/* node data. */
    T data;
};

/* helper functions for TreeNode objects. */

template <class T>
bool isLeaf(TreeNode<T>* node) { /* returns true if TreeNode object exists and is leaf node. */
    if (node == NULL) return false;
    return (node -> left == NULL && node -> right == NULL);
}

template <class T>
bool isRight(TreeNode<T>* node){ /* returns true if TreeNode object exists and is right child. */
    if (node == NULL || node -> parent == NULL) return false;
    return node == node -> parent -> right;
}

template <class T>
bool isLeft(TreeNode<T>* node) { /* returns true if TreeNode object exists and is left child. */
    if (node == NULL || node -> parent == NULL) return false;
    return node == node -> parent -> left;
}

template <class T>
bool isRoot(TreeNode<T>* node) { /* returns true if TreeNode object exists and is root node. */
    if (node == NULL) return false;
    return node -> parent == NULL;
}

template <class T>
int treeHeight(TreeNode<T>* node) { /* returns height of TreeNode object. if it has no children, returns 0. */
    if (node == NULL) return -1; /* if it doesn't exist, returns -1. */
    return 1 + max(treeHeight(node -> left), treeHeight(node -> right));
}

template <class T>
int treeSize(TreeNode<T>* node){ /* returns size of subtree, starting at TreeNode object. */
    if (node == NULL)
        return 0;
    return 1 + treeSize(node -> left) + treeSize(node -> right);
}

template <class T>
class BST { /* left-hand side: <, right-hand side: >=. */
public:
    friend ostream& operator << (ostream& os, const BST<T>& tree){
        os << *(tree.root);
        return os;
    }

    BST();

    TreeNode<T>* search(T& data) const;
    void insert(T& data);
    TreeNode<T>* successor(TreeNode<T>* node) const;
    bool remove(T& data);

    bool isEmpty() const;
    int height() const;
    int size() const;

    TreeNode<T>* getRoot() const;
	
private:
    TreeNode<T>* root;
	void insert(TreeNode<T>* comparison, TreeNode<T>* node);
	TreeNode<T>* search(TreeNode<T>* comparison, T& data) const;
    bool remove(TreeNode<T>* node);
};

/* implementations of BST class. */

template <class T>
BST<T>::BST(): root(NULL) {}

template <class T>
void BST<T>::insert(TreeNode<T>* comparison, TreeNode<T>* node) {
	/* precondition: node -> data != NULL and root exists (i.e. comparison != NULL). */

	/* determine whether node should be inserted to the left or right of comparison. */
	TreeNode<T>** place = (node -> data < comparison -> data) ? &(comparison -> left) : &(comparison -> right);
	/* place is a pointer for one of comparison's child pointers. */
	
	/* if corresponding spot is empty, insert node. */
	if (*place == NULL) {
		*place = node; /* set node as child of comparison. */
		node -> parent = comparison; /* set comparison as parent of node. */
	}
	/* otherwise, use recursion. */
	else
		insert(*place, node);
}

template <class T>
void BST<T>::insert(T& data) {
	/* if data == NULL, do not insert. */
	if (data == NULL)
		return;
	
	/* initialize node to-be-inserted. */
	TreeNode<T>* node = new TreeNode<T>;
	node -> data = data;

	/* if tree is empty, insert node as root. */
	if (root == NULL) {
		root = node;
		return;
	}
	/* otherwise, insert node farther down in the tree. */
	insert(root, node);
}

template <class T>
TreeNode<T>* BST<T>::search(TreeNode<T>* comparison, T& data) const {
	/* precondition: target != NULL and root exists (i.e. comparison != NULL). */
	
	/* if comparison matches data, return it. */
	if (data == comparison -> data)
		return comparison;

	/* else, determine whether node should be located at left or right of comparison. */
	TreeNode<T>** place = (data < comparison -> data) ? &(comparison -> left) : &(comparison -> right);
	/* place is a pointer for one of comparison's child pointers. */
	
	/* if corresponding spot is empty, return NULL. node being searched should've been here. */
	if (*place == NULL)
		return NULL;
	/* otherwise, use recursion. */
	return search(*place, data);
}

template <class T>
TreeNode<T>* BST<T>::search(T& data) const {
	/* if target == NULL or tree is empty, search won't be successful. */
	if (data == NULL || root == NULL)
		return NULL;

	/* employ a recursive search. */
	return search(root, data);
}

template <class T>
TreeNode<T>* BST<T>::successor(TreeNode<T>* node) const {
	/* if pointer holds no address, successor cannot be determined. */
	if (node == NULL)
		return NULL;
	
	/* if right child exists, its leftest descendant is node's successor. */
	if (node -> right != NULL) {
		TreeNode<T>* iteration = node -> right;

		while (iteration -> left != NULL)
			iteration = iteration -> left;
		
		return iteration;
	}
	/* if node has no parent, further checks are futile. */
	if (node -> parent == NULL)
		return NULL;
	
	/* if node is parent's left child, then parent is node's successor. */
	if (isLeft(node))
		return node -> parent;
	/* if node's parent is left child of another node, then said grandparent is node's successor. */
	if (isLeft(node -> parent))
		return (node -> parent) -> parent;
	
	/* if none of the previous checks have passed, node has no successor. */
	return NULL;
}

template <class T>
bool BST<T>::remove(TreeNode<T>* node) {
	/* precondition: root exists. */

	if (node == NULL)
		return false;
	
	bool isroot = (node == root);
	bool isleft = isLeft(node);
	
	/* case one: node has two children. */ 
	if (node -> left != NULL && node -> right != NULL) {		
		/* replace node with successor. */		
		TreeNode<T>* replacement = successor(node);
		
		if (isroot)
			root -> data = replacement -> data;
		else if (isleft)
			node -> parent -> left -> data = replacement -> data;
		else
			node -> parent -> right -> data = replacement -> data;	

		remove(replacement);
		
		return true;
	}
	
	/* case two: node is leaf. */ 
	if (node -> left == NULL && node -> right == NULL) {
		if (isroot) {
			root = NULL;
			return true;
		}
		
		if (isleft)
			node -> parent -> left = NULL;
		
		else
			node -> parent -> right = NULL;

		return true;
	}
	
	/* case three: node has only one child. */ 
	else {
		TreeNode<T>* child = (node -> left != NULL) ? node -> left : node -> right;

		if (isroot) {
			root = child;
			return true;
		}

		if (isleft)
			node -> parent -> left = child;
		else
			node -> parent -> right = child;

		return true;
	}
	
	/* should never run... but here for redundancy. */
	return false;
}

template <class T>
bool BST<T>::remove(T& data) {
	/* removing NULL is impossible, as no node in tree can have data attribute set to NULL. */
	/* if tree is empty, removal is also impossible. */
	if (data == NULL || root == NULL)
		return false;

	TreeNode<T>* node = search(data);
	return remove(node);
}

template <class T>
bool BST<T>::isEmpty() const {
	return root == NULL;	
}

template <class T>
int BST<T>::height() const {
	return treeHeight(root);
}

template <class T>
int BST<T>::size() const {
	return treeSize(root);
}

template <class T>
TreeNode<T>* BST<T>::getRoot() const {
	return root;
}

#endif