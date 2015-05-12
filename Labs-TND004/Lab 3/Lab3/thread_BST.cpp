/********************************************************
* File: threaded_BST.cpp                                *
* Author: Aida Nordman                                  *
* Course: TND004, Lab 3                                 *
* Date: VT2, 2014                                       *
* Description: class BST_threaded representing          *
*              a threaded binary search tree            *
*********************************************************/

#include "threaded_BST.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

using namespace std;


//Default Constructor: create an empty tree
//Empty tree has a dummy node as root
//The real tree is stored as left child of the dummy root
BST_threaded::BST_threaded()
 : counter(0)
{
    ELEMENT tempElement;
    tempElement.first = "";
    tempElement.second = -1;
    root = new Node(tempElement, nullptr, nullptr);   // pointer *l = *r = nullptr

}
//destructor
BST_threaded::~BST_threaded()
{
  //ADD CODE
}

//Test if the tree is empty
bool BST_threaded::empty() const
{
    if(root->left == nullptr)
        return true;
    else
        return false;
}

//Return mumber of keys (elements) stored in the tree
int BST_threaded::size() const
{
   return counter;
}


//Insert v in the tree
void BST_threaded::insert(ELEMENT v)
{
    if (empty())
    {
        //Insert first node of the BST has a left child of the BST
        root->left = new Node(v, root, root);
        root->left->l_thread = root->left->r_thread = true;

        root->l_thread = false;
        counter = 1;
    }
    else
        counter += root->left->insert(v); //call NODE::insert()
}


//Remove node with key from the tree
void BST_threaded::remove(string key)
{
    //if key exists in tree, remove it. else do nothing
   if (find(key))
        counter -= root->left->remove(key);
}



//If key matches the key of an element in the container,
//then return a reference to the ELEMENT with the key
//If key does not match the key of any element in the container,
//then an ELEMENT (key,0) is inserted and a reference to it is returned
ELEMENT& BST_threaded::operator[](string key)
{
    Node* tempNode;

    if(root->left->find(key) != nullptr)
    {
        tempNode = root->left->find(key);
        return tempNode->value;
    }
    else
    {
        ELEMENT tempElement;
        tempElement.first = key;
        tempElement.second = 0;
        root->left->insert(tempElement);
        tempNode = root->left->find(key);
        return tempNode->value;
    }


}


//Find the node in the BST storing key
//Return a BiIterator referring to the node storing the key, if the key is found.
//Otherwise, return this->end().
BiIterator BST_threaded::find(string key) const
{
    //BiIterator tempIterator(root->left->findMin());
    Node* tempNode;

    if(empty())
        return this->end();
    else
    {
        tempNode = root->left->find(key);
        if(tempNode == nullptr)
            return this->end();
        else
        {
            BiIterator tempIterator(tempNode);
            return tempIterator;
        }

    }
}


//Return an iterator referring to the first node in the inorder traversal of the BST
BiIterator BST_threaded::begin() const
{
    if(empty())
        return BiIterator(root);
    else
    {
        Node* tempNode = root->left;
        while (!(tempNode->l_thread))   // goes to the smallest node , at the bottom left
        {
            tempNode = tempNode->left;
        }
        cout << tempNode->value.first << endl;
        return BiIterator(tempNode);
    }
}


 //Return a BiIterator referring to the past-the-end element in the BST
BiIterator BST_threaded::end() const
{
    BiIterator it(root);

    return it;
}


//Display all keys increasingly
//To be used for debugging -- ONLY
void BST_threaded::display() const
{
    if (!empty())
        root->left->display();
     else
        cout << "The container is empty!!" << endl;

}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
