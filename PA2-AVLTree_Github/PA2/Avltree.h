 #ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <iostream>    // For NULL
#include <queue>  // For level order printout
#include <vector>
#include <algorithm> // For max() function
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// int size( )            --> Quantity of elements in tree
// int height( )          --> Height of the tree (null == -1)
// void insert( x )       --> Insert x
// void insert( vector<T> ) --> Insert whole vector of values
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted (in) order
// void printPreOrder( )  --> Print tree in pre order
// void printPostOrder( ) --> Print tree in post order
// void printInOrder( )   --> Print tree in *in* order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
public:
	AvlTree() : root(NULL)
	{ }

	AvlTree(const AvlTree & rhs) : root(NULL)
	{
		*this = rhs;
	}

	~AvlTree()
	{
		cout << " [!] Destructor called." << endl;
	}

	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMin() const
	{
		if (isEmpty())
			throw UnderflowException();
		return findMin(root)->element;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMax() const
	{
		if (isEmpty())
			throw UnderflowException();
		return findMax(root)->element;
	}

	/**
	 * Returns true if x is found in the tree.
	 */
	bool contains(const Comparable & x) const
	{
		return contains(x, root);
	}

	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 *  TODO: Implement
	 */
	bool isEmpty() const
	{
		return false;  // so not correct
	}

	/**
	 * Return number of elements in tree.
	 */
	int size()
	{
		int count = 0;
		return size(root, count);
	}

	/**
	 * Return height of tree.
	 *  Null nodes are height -1
	 */
	int height()
	{
		return heights(root);
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	void printTree() const
	{
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printInOrder(root);
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	void printInOrder() const
	{
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printInOrder(root);
	}

	/**
	 * Print the tree contents in pre order.
	 */
	void printPreOrder() const
	{
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printPreOrder(root);
	}

	/**
	 * Print the tree contents in post order.
	 */
	void printPostOrder() const
	{
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printPostOrder(root);
	}

	/**
	 * Make the tree logically empty.
	 */
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert(const Comparable & x)
	{
		insert(x, root);
	}

	/**
	 * Insert vector of x's into the tree; duplicates are ignored.
	 */
	void insert(vector<Comparable> vals)
	{
		for (auto x : vals) {
			insert(x, root);
		}
	}


	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 *  TODO: Implement
	 */
	void remove(const Comparable & x)
	{
		cout << "Sorry, not implemented" << endl;
		/*if (!root) {	//Empty tree, end here
			return;
		}
		else if (x < root->element) {	//recurisvely go through
			root = root->left;
			remove(root->left->element);
		}
		else if (x > root->element) {	
			root = root->right;
			remove(root->right->element);
		}
		else {
			cout << "Sorry, not implemented" << endl;
		}
 */
	}


	/**
	 * Deep copy. - or copy assignment operator
	 *  Will be in part II
	 */
	const AvlTree & operator=(const AvlTree & rhs)
	{
		cout << " [!] Copy *assignment* operator called." << endl;
		return *this;
	}


	/*****************************************************************************/
private:
	struct AvlNode
	{
		Comparable element;
		AvlNode   *left;
		AvlNode   *right;
		int       height;

		AvlNode(const Comparable & theElement, AvlNode *lt,
			AvlNode *rt, int h = 0) //int h = 0
			: element(theElement), left(lt), right(rt), height(h) { }
	};

	AvlNode *root;
	/**
	 * Internal method to count nodes in tree
	 *  TODO: Implement
	 */
	int size(AvlNode * & t, int & count)
	{ 
		if (!t) {
			return count;
		}
		else {
			count = count + 1;         //recursively going through tree and counting number of elements
			size(t->left, count);
				size(t->right, count);
		
		}
	}
  
	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 *  TODO: Implement
	 */
	 //ALWAYS PASSIN THE ROOT 
	void insert(const Comparable & x, AvlNode * & t)
	{
		int factor;  
		if (!t) {
			t = new AvlNode(x, NULL, NULL, 0); //if t is empty make t new node
		}

		else if (x < t->element) {  //if value is less than t go to left
			insert(x, t->left);

		}
		else if (x > t->element) { 
			insert(x, t->right);  //if value more than t insert right
		}
		t->height = 1 + max(heights(t->left), heights(t->right));

		if (!t)
		factor = 0;
		factor =  heights(t->left) - heights(t->right); //balance factor

		if (factor >=2 && x < t->left->element) { //if left subtree is heavy and less than t's left pointer element
			rotateWithRightChild(t);
		}

		if (factor  <=-2 && x > t->right->element) { //if right subtree is heavy and more than t's right pointer element
			rotateWithLeftChild(t);
		}

		if (factor >=2 && x > t->left->element) //balancing left subtree that is right heavy
		{
			 
			doubleWithRightChild(t);
		}

		if (factor <=-2 && x < t->right->element) //balancing right subtree that is left heavy
		{
			doubleWithLeftChild(t);
			 
		}
		 
	}

	// Definitely to do


		/**
		 * Internal method to find the smallest item in a subtree t.
		 * Return node containing the smallest item.
		 *  You'll need this for deletes
		 *  TODO: Implement
		 */
    AvlNode * findMin( AvlNode *t ) const
    {
		if (!t) {
			return t;
		}								//if t is null return it
		else {
			while (t->left!=NULL) {  //keep going through left subtree until you reach the end, then it's the smallest
				t = t->left;
			}
		}
      return t; // placeholder
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     *  TODO: Implement
     */
    AvlNode * findMax( AvlNode *t ) const
    {
		if (!t) {
			return;						//same as findMin except it's through right subtree and t->left
		}
		else {
			while (t->right != NULL) {
				t = t->right;
			}
		}
        return t;  // placeholder
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     *  TODO: Implement
     */
	bool contains(const Comparable & x, AvlNode *t) const
	{
		if (!t)
		{
			cout << "NOT FOUND!" << endl;   //if t is null then return false
			return false;
		}
		else
		{
		if (x < t->element)
	     {
			contains(x, t->left); //if t is less than root value, go through left subtree, then return true if found
			return true;
		}
		else
		{
		if (x > t->element)
		{
		 contains(x, t->right);	//if t is more than root value, go through right subtree then return true if found
		  return true;
		}
		else
		{
		cout << "FOUND~ " << endl;
		}
	}
		return false;    // Lolz
}
}

/******************************************************/

    /**
     * Internal method to make subtree empty.
     * 
     */
    void makeEmpty( AvlNode * & t )
    {
       // Will be in part II
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     *  TODO: Implement
     */
    void printInOrder( AvlNode *t ) const
    {
		if (!t)
			return;
	 
		printInOrder(t->left);
		cout << t->element << ",";  //print through left subtree, then root, then right subtree
		printInOrder(t->right);
    }

    /**
     * Internal method to print a subtree rooted at t in pre order.
     *  TODO: Implement
     */
	void printPreOrder(AvlNode *t) const
	{

     // cout << "  [!] Printing Pre order";
	  if (!t)
		  return;
	  
	  cout << t->element << ",";
	  printPreOrder(t->left);   //print root, then left subtree, then right subtree
	  printPreOrder(t->right);  
    }

    /**
     * Internal method to print a subtree rooted at t in post order.
     *  TODO: Implement
     */
    void printPostOrder( AvlNode *t ) const
    {
		if (!t)
			return;
 
		printPostOrder(t->left);    //print left subtree, then right subtree, then root
		printPostOrder(t->right);
		cout << t->element << ",";
      //cout << "   [!] Printing post order";
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }


    // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     *  TODO: Implement
     */
    int heights( AvlNode *t ) const
    {  
		if (!t)
			return -1;  //if null then return 1;
		else {
			t->height = t->height; //else return height of t
		}
		return t->height;
    }


    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    { 
		AvlNode *some= k2->right; 

		k2->right = some->left; //peform rotation
		some->left = k2;

	    k2->height = max(heights(k2->left), heights(k2->right)) + 1;  //updates heights
		some->height = max(heights(some->right), k2->height) + 1;

		k2 = some;	 //set new root
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {

		AvlNode *other = k1->left;

		k1->left = other->right; //peform rotation
		other->right = k1;

		k1->height = max(heights(k1->left), heights(k1->right)) + 1; //updates heights
		other->height = max(heights(other->left), k1->height) + 1;

		k1 = other; //set new root
    }

	 
    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {  
		rotateWithRightChild(k3->right); //double rotation
	    rotateWithLeftChild(k3);
		 
    }
	 
    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node kld.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     *  TODO: Implement
     */
	void doubleWithRightChild(AvlNode * & k1)
	{
		rotateWithLeftChild(k1->left); //double rotation
		rotateWithRightChild(k1);
	}
		 
};

#endif
