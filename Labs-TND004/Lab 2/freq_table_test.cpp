/*
  Name: freq_table
  Author: Daniel Holst
  Course: TND004, Lab 2
  Description: test program for class HashTable
*/

#include <iostream>
#include <string>

#include "hashTable.h"

using namespace std;

 /**
 * A hash routine for string objects.
 */
 unsigned int my_hash( string key, int tableSize )
 {
 unsigned int hashVal = 0;
 for( char ch : key )
    hashVal = 37 * hashVal + ch;

 return hashVal % tableSize;
 }


int main()
{
    string word;
    const int TABLE_SIZE = 7;
    HashTable freq_table(TABLE_SIZE, my_hash);

    while ( cin >> word )
    {
        freq_table[word];
    }

    cout << "Number of words in file: " << freq_table.get_number_OF_items() << endl << endl;

    cout << "Number of unique words in file: " << freq_table.get_number_of_unique_items() << endl << endl;

    //display freq_table
    freq_table.display(cout);
    return 0;
}
