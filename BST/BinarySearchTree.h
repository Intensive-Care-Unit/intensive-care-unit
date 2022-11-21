#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void markAsDeleted( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template<typename Comparable, typename Object>
class BinarySearchTree
{
public:
    BinarySearchTree() : root{nullptr}
    {}

    BinarySearchTree(const BinarySearchTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    BinarySearchTree(BinarySearchTree &&rhs) : root{rhs.root}
    {
        rhs.root = nullptr;
    }

    ~BinarySearchTree()
    {
        makeEmpty();
    }

    /**
     * Deep copy.
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs)
    {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     * Move.
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs)
    {
        std::swap(root, rhs.root);

        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMax(root)->element;
    }


    /**
* Access data with a specific key
*/
    Object &at(const Comparable &x) const
    {
        return at(root, x);
    }

    /**
    * Access data with a specific key
    */
    Object &at(Comparable &&x) const
    {
        return at(root, std::move(x));
    }

    /**
    * Convert data into vector
    */
    std::vector<Object> toVector() const
    {
        std::vector<Object> vData;
        toVector(root, vData);
        return vData;
    }


    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
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
    void insert(const Comparable &x, const Object &o)
    {
        insert(x, root, o);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(Comparable &&x, Object &&o)
    {
        insert(std::move(x), root, o);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x)
    {
        remove(x, root);
    }

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int height;
        Object value;

        BinaryNode(const Comparable &ele, BinaryNode *lt, BinaryNode *rt, const Object &o, int h = 0)
                :
                element{ele}
                , left{lt}
                , right{rt}
                , height{h}
                , value{o}
        {}

        BinaryNode(Comparable &&ele, BinaryNode *lt, BinaryNode *rt, const Object &o, int h = 0)
                :
                element{std::move(ele)}
                , left{lt}
                , right{rt}
                , height{h}
                , value{std::move(o)}
        {}
    };

    BinaryNode *root;


    /**
  * Access data with a specific key
  */
    Object &at(BinaryNode *t, const Comparable &x) const
    {
        if (t == nullptr)
            throw IllegalArgumentException{};
        else if (x < t->element)
            return at(t->left, x);
        else if (t->element < x)
            return at(t->right, x);
        else
            return t->value;
    }

    /**
    * Access data with a specific key
    */
    Object &at(BinaryNode *t, Comparable &&x) const
    {
        if (t == nullptr)
            throw IllegalArgumentException{};
        else if (std::move(x) < t->element)
            return at(t->left, std::move(x));
        else if (t->element < std::move(x))
            return at(t->right, std::move(x));
        else
            return t->value;
    }

    /**
    * Convert tree data into vector
    */
    void toVector(BinaryNode *t, std::vector<Object> &vData) const
    {
        if (t != nullptr)
        {
            vData.push_back(t->value);
            toVector(t->left, vData);
            toVector(t->right, vData);
        }
    }


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, BinaryNode *&t, const Object &o)
    {
        if (t == nullptr)
            t = new BinaryNode{x, nullptr, nullptr, o};
        else if (x < t->element)
            insert(x, t->left, o);
        else if (t->element < x)
            insert(x, t->right, o);

    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable &&x, BinaryNode *&t, Object &&o)
    {
        if (t == nullptr)
            t = new BinaryNode{std::move(x), nullptr, nullptr, std::move(o)};
        else if (x < t->element)
            insert(std::move(x), t->left, o);
        else if (t->element < x)
            insert(std::move(x), t->right, o);

    }

    /**
     * Internal method to markAsDeleted from a subtree.
     * x is the item to markAsDeleted.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
            return;   // Item not found; do nothing

        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        } else
        {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

    }


    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const Comparable &x, BinaryNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(BinaryNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree(BinaryNode *t) const
    {
        if (t != nullptr)
        {
            printTree(t->left);
            cout << t->element << endl;
            printTree(t->right);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right), t->value, t->height};
    }


};

#endif