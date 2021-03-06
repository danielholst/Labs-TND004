#include <assert.h>
#include <iomanip>
#include <iostream>

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
    : size(nextPrime(table_size)), h(f), nItems(0), nUniqueItems(0)
{
    //create array (hTable) with pointers to items
    hTable = new Item*[size];
    for(int i = 0; i < size; i++)
    {
        hTable[i] = nullptr;
    }

}


//destructor
// IMPLEMENT
HashTable::~HashTable()
{
    for (int i = 0; i < size; i++)
    {
        if (hTable[i] != nullptr)
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
    if(hTable[hashVal] == nullptr)
        return NOT_FOUND;
    else
    {
        while (hTable[hashVal] != nullptr)   //loop until empty slot in table
        {
            if(hTable[hashVal]->key == key)
                return hTable[hashVal]->value;
            hashVal++;

            if( hashVal == size )  // if in the last slot of array start from the top
            {
                hashVal = 0;
            }
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

    if(hTable[hashVal] == nullptr)     // if empty -> insert
    {
        hTable[hashVal] = newItem;
        nItems++;
        nUniqueItems++;
    }
    else
    {
        while (hTable[hashVal] != nullptr) //loop until empty slot in table
        {
            if(hTable[hashVal]->value == -1 && (find(key) == NOT_FOUND))
            {
                hTable[hashVal] = newItem;
                nItems++;
                nUniqueItems++;
                break;
            }
            if(hTable[hashVal]->key == key)     // if key already exist in table remove old one and insert new to get new value
            {
                hTable[hashVal]->value++;
                nItems++;
                nUniqueItems--;
                break;
            }
            hashVal++;

            if( hashVal == size )  // if in the last slot of array start from the top
            {
                hashVal = 0;
            }
        }
        hTable[hashVal] = newItem;
        nItems++;
        nUniqueItems++;
    }

    if (loadFactor() > MAX_LOAD_FACTOR)
        reHash();

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
        while (hTable[hashVal] != nullptr )   // loop to find key
        {
            if(hTable[hashVal]->key == key)
            {
                if(hTable[hashVal]->value == 1)
                    nUniqueItems--;
                hTable[hashVal] = Deleted_Item::get_Item();
                nItems--;
                return true;
            }
            hashVal++;
            if( hashVal == (size))  // if in the last slot of array start from the top
            {
                hashVal = 0;
            }

        }
        return false;
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
    for(int i = 0; i < T.size; i++)
    {
        if(T.hTable[i] != nullptr)
            os << "key = " << left << setw(20) << T.hTable[i]->key
               << "value = " << T.hTable[i]->value << endl;
    }

    return os;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{
    nItems = 0;
    nUniqueItems = 0;
    int NEXT_TABLE_SIZE = nextPrime(2*size);    // new size of array

    string keys[size];        //to store old keys and values
    int values[size];

    for(int i = 0; i < size; i++)       //loop through old array and store all values in new arrays
    {
        if(hTable[i] != nullptr)
        {
            keys[i] = hTable[i]->key;
            values[i] = hTable[i]->value;
        }
        else
        {
            keys[i] = "";
            values[i] = 0;
        }
    }

    int prevSize = size;
    size = NEXT_TABLE_SIZE;

    hTable = new Item*[size];   // make hTable to the new size
    for(int i = 0; i < size; i++)
    {
        hTable[i] = nullptr;
    }

    for( int i = 0; i < prevSize; i++)  // insert values to hTable again
    {
        if(values[i] != 0)
        {
            insert(keys[i], values[i]);
        }
    }

    cout << "Rehashing ..." << endl;
    cout << " new size = " << NEXT_TABLE_SIZE << endl;
}

// subscript operator
int& HashTable::operator[](const string s)
{
    if((find(s)) == NOT_FOUND)
        insert(s,1);
    else
         insert(s, (find(s)+1));

    int hashVal = h(s, size);

    //hTable[hashVal]->value++;
    return hTable[hashVal]->value;
}
