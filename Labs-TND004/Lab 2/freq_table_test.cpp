/*
  Name: freq_table
  Author: Daniel Holst
  Course: TND004, Lab 2
  Description: test program for class HashTable
*/

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <vector>

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

 bool test_special_char(char c)
{
    if(c == '\'' || c == ',' ||c == '"' || c =='.' || c =='?')
        return false;
    else
        return true;

}

string rem(string word)
{
    char chars[] = ".,-()\"?";
    for(unsigned int i = 0; i < strlen(chars); ++i)
    {
        word.erase(remove(word.begin(), word.end(), chars[i]), word.end());
    }

    return word;
}


int main()
{
    string word ="";
    const int TABLE_SIZE = 7;
    HashTable freq_table(TABLE_SIZE, my_hash);

    fstream myfile;
    myfile.open ("test_file2.txt");

		while (myfile >> word)
		{
		    word = rem(word);
            transform(word.begin(),word.end(), word.begin(), ::tolower);
            freq_table[word];
		}

    cout << "----------------------------------" << endl;
    cout << "Number of words in file: " << freq_table.get_number_OF_items() << endl << endl;

    cout << "Number of unique words in file: " << freq_table.get_number_of_unique_items() << endl << endl;
    cout << "----------------------------------" << endl;
    //display freq_table
    cout << freq_table << endl;
    return 0;
    }

