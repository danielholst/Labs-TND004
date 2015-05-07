/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS


Node::Node(ELEMENT v, Node *l, Node *r)
 : value(v), left(l), right(r)
{
    l_thread = r_thread = false;
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node()
{
    //ADD CODE
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{

    if(v.first == this->value.first)    // increase word conter if this == value
    {
        this->value.second++;
        return false;
    }


    else if(v.first > this->value.first)    // new value is larger then this value
    {
        if(this->r_thread)
        {
            this->right = new Node(v, nullptr, nullptr);
            this->right->l_thread = this->right->r_thread = true;
            this->r_thread = false;
            return true;
        }

        else if(this->right->value.first == v.first)     // v already exists in the tree
        {
            this->right->value.second++;
            return false;
        }
        else
        {
            this->right->insert(v);
        }

    }

    else if(v.first < this->value.first) // new value is smaller than value of this
    {
        if(this->l_thread)
        {
            this->left = new Node(v, nullptr, nullptr);
            this->left->l_thread = this->left->r_thread = true;
            this->l_thread = false;
            return true;
        }

        else if(this->left->value.first == v.first)     // v already exists in the tree
        {
            this->left->value.second++;
            return false;
        }
        else
        {
            this->left->insert(v);
        }


    }

}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    //ADD CODE
    return false;
}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight)
{
   //ADD CODE
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    Node* tempNode = this;
    if(tempNode->value.first == key);
        return tempNode;
        else if(key < tempNode->value.first) // new value is smaller than value of this
    {
        if(tempNode->l_thread)
        {
            return nullptr;
        }

        else if(tempNode->left->value.first == key)     // v already exists in the tree
        {
            return tempNode->left;
        }
        else
        {
            this->left->find(key);
        }


    }
    return nullptr;
}


//Return a pointer to the node storing the smalest value
//of the tree whose root is this node
Node* Node::findMin()
{
    //ADD CODE
    return nullptr;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    //ADD CODE
    return nullptr;
}



//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const
{
    if ( !l_thread ) //display left sub-tree
        left->display();

    cout << value.first << " "; //display key stored in the node

    if ( !r_thread ) //display right sub-tree
        right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
