/**********************************************
* File: node.cpp                              *
* Author: Daniel Holst                       *
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
//    delete left;
//    delete right;
//    while(this->left)
//        remove(this->left->value.first, this, false);
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    Node* tempNode = this;
    if(v.first == tempNode->value.first)    // increase word conter if this == value
    {
        tempNode->value.second++;
        return false;
    }


    else if(v.first > tempNode->value.first)    // new value is larger then this value
    {
        if(tempNode->r_thread)
        {
            Node* newNode = new Node(v, tempNode, tempNode->right);
            tempNode->right = newNode;
            newNode->l_thread = newNode->r_thread = true;
            tempNode->r_thread = false;
        }

        else
            return tempNode->right->insert(v);

    }

    else if(v.first < tempNode->value.first) // new value is smaller than value of this
    {
        if(tempNode->l_thread)
        {
            Node* newNode = new Node(v, tempNode->left, tempNode);
            tempNode->left = newNode;
            newNode->l_thread = newNode->r_thread = true;
            tempNode->l_thread = false;
        }

        else
            return tempNode->left->insert(v);

    }

    return true;
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    Node* childNode = this;
    Node* parentNode = parent;

    while(childNode->value.first != key)    //finds the right key
    {
        parentNode = childNode;
        if(key < childNode->value.first)
            childNode = childNode->left;
        else
            childNode = childNode->right;
    }

    //if child has two childs
    if(!childNode->r_thread && !childNode->l_thread)
    {
        cout << "debug: entered case of two childs in remove .." << endl;
        Node* tempNode = childNode;
        parentNode = childNode;
        childNode = childNode->left;
        while (!childNode->r_thread)
        {
            parentNode = childNode;
            childNode = childNode->right;
        }
        tempNode->value = childNode->value;     //replace value

        if(childNode->value.first <= parentNode->value.first)
            removeMe(parentNode, false);
        else
            removeMe(parentNode, true);
    }

   else if(parentNode->value.first == "") //if parent is root
        removeMe(parentNode, false);

    else if(parentNode->value.first > childNode->value.first)
        removeMe(parentNode, false);
    else
        removeMe(parentNode, true);

    return true;

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
//3   a child with two children
void Node::removeMe(Node* parent, bool isRight)
{
    cout << "debug: entered removeMe" << endl;
    Node* childNode;
    Node* parentNode = parent;
    string tempValue;

    if(isRight)
        childNode = parentNode->right;
    else
        childNode = parentNode->left;

    //if childNode has no childs (case 1c and 2c)
    if(childNode->l_thread && childNode->r_thread)
    {
        cout << "debug: case no childs " << endl;
        //rethread
        if(isRight)
        {
            parentNode->right = childNode->right;
            parentNode->r_thread = childNode->r_thread;
        }
        else
        {
            parentNode->l_thread = childNode->l_thread;
            parentNode->left = childNode->left;
        }
    }

    //if left child with only a right child (case 1a)
    else if(!isRight && childNode->l_thread && !childNode->r_thread)
    {
        cout << "debug: case left child with right child " << endl;
        parentNode->left = childNode->right;
        childNode->right->findMin()->left = childNode->left;

    }

    //if right child with only a right child (case 1b)
    else if(isRight && childNode->l_thread && !childNode->r_thread)
    {
        cout << "debug: case right child with right child " << endl;
        parentNode->left = childNode->left;
        childNode->right->findMin()->left = childNode->left;
    }

    //if left child with only a left child (case 2a)
    else if(!isRight && childNode->r_thread && !childNode->l_thread)
    {
        cout << "debug: case left child with left child " << endl;
        parentNode->left = childNode->left;
        childNode->left->findMax()->right = childNode->right;

    }

    //if right child with only a left child (case 2b)
    else if(isRight && childNode->r_thread && !childNode->l_thread)
    {
        cout << "debug: case right child with left child " << endl;
        parentNode->right = childNode->left;
        childNode->left->findMax()->right = childNode->right;
    }

    else
        cout << "something went wrong in removeMe..." << endl;

    //delete childNode
    cout << "deleting node " << childNode->value.first << endl << endl;
    delete childNode;

}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    Node* tempNode = this;

    while (tempNode)
    {
        if(key > tempNode->value.first)
        {
            if(tempNode->r_thread)
                break;
            tempNode = tempNode->right;
        }

        else if( key < tempNode->value.first)
        {
            if(tempNode->l_thread)
                break;
            tempNode = tempNode->left;
        }

        else    // same value
            return tempNode;
    }

    return nullptr;
}


//Return a pointer to the node storing the smalest value
//of the tree whose root is this node
Node* Node::findMin()
{
    Node* tempNode = this;

    while(!(tempNode->l_thread))
        tempNode = tempNode->left;

    return tempNode;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    Node* tempNode = this;

    while(!(tempNode->r_thread))
        tempNode = tempNode->right;

    return tempNode;
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
