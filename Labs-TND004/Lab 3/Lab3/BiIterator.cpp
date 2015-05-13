/**********************************************
* File: BiIterator.cpp                        *
* Author: Daniel Holst                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/


#include "BiIterator.h"


#ifndef DOXYGEN_SHOULD_SKIP_THIS


// Constructor
BiIterator::BiIterator(Node *ptr)
 : current(ptr)
 {

 }


//Dereferencing operator
ELEMENT& BiIterator::operator*() const
{
    return current->value;
}


//Member access operator
ELEMENT* BiIterator::operator->() const
{
    return &current->value;
}


//Equality comparison operator
bool BiIterator::operator==(const BiIterator &it) const
{
    if((current->value.first == it.current->value.first))
        return true;
    else
        return false;
}


//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const
{
    if((current->value.first != it.current->value.first))
        return true;
    else
        return false;
}


//Pre increment operator
BiIterator& BiIterator::operator++()
{
    // If no right subtree, proceed to next node
    if(this->current->r_thread)
        this->current = this->current->right;

    // Find minimum value in the right subtree
    else
        this->current = this->current->right->findMin();

    return *this;
}



//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int)
{
    BiIterator biIt(*this);
    ++(*this);

    return biIt;
}

//Pre decrement operator
BiIterator& BiIterator::operator--()
{
    // If no left subtree, proceed to next node
    if(this->current->l_thread)
        this->current = this->current->left;

    // Find minimum value in the right subtree
    else
        this->current = this->current->left->findMax();

    return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int)
{
    BiIterator biIt(*this);
    --(*this);

    return biIt;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
