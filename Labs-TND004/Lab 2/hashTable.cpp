#include <assert.h>
#include <iomanip>

#include "hashTable.h"

const double MAX_LOAD_FACTOR = 0.5;

//Test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


//Return a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}


// Constructor
// IMPLEMENT
HashTable::HashTable(int table_size, HASH f)
    : size(nextPrime(table_size)), h(f), nItems(0)
{
    //create array (hTable) with pointers to items
    hTable = new Item*[size];
    for(int i = 0; i < size; i++)
    {
        hTable[i] = NULL;
    }

}


//destructor
// IMPLEMENT
HashTable::~HashTable()
{
    for (int i = 0; i < size; i++)
    {
        if (hTable[i] != NULL)
            delete hTable[i];
    }
    delete[] hTable;
}


//Return the load factor of the table
double HashTable::loadFactor() const
{
    return (double) nItems / size;
}


//Return the value associated with key
//If key does not exist in the table then NOT_FOUND is returned
// IMPLEMENT
int HashTable::find(string key) const
{
    int hashVal = h(key, size);
    if(hTable[hashVal] == NULL)
        return NOT_FOUND;
    else
    {
        while (hTable[hashVal] != NULL)   //loop until empty slot in table
        {
            if(hTable[hashVal]->key == key)
                return hTable[hashVal]->value;
            hashVal++;
        }
        return NOT_FOUND;
    }

}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
//Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v)
{
    int hashVal = h(key, size);
    Item* newItem = new Item(key, v);

    if(hTable[hashVal] == NULL)     // if empty -> insert
    {
        hTable[hashVal] = newItem;
    }
    else
    {
        while (hTable[hashVal] != NULL) //loop until empty slot in table
        {
            if(hTable[hashVal]->key == key)     // if key already exist in table remove old one
            {
                remove(key);
                hTable[hashVal] = newItem;
                break;
            }
            hashVal++;
        }
        hTable[hashVal] = newItem;
    }

    if (loadFactor() > 0.5) reHash();

}


//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key)
{
    if (find(key) == NOT_FOUND)
        return false;
    else
    {
        int hashVal = h(key, size);
        hTable[hashVal] = NULL;
        return true;
    }

}


void HashTable::display(ostream& os)
{
    if (!hTable) return;

    os << "-------------------------------\n";

    for (int i = 0; i < size; ++i)
    {
        os << setw(6) << i << ": ";

        if (!hTable[i])
        {
            os << "null" << endl;
        }
        else
        {
            string key = hTable[i]->key;

            os << "key = " << "\"" << key << "\""
               << setw(12) << "value = " << hTable[i]->value
               << "  (" << h(key,size) << ")" << endl;
        }
    }

    os << endl;
}


//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T)
{
    return os;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{

}
