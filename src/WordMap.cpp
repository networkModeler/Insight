////////////////////////////////////////////////////////////////////////////////
//
// Filename:    WordMap.cpp
//
// Purpose:     methods for WordMap class
//
// Comments:    Manages an STL binary tree of unique words and associated counts
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>         // cout, etc
#include <iomanip>          // setw
#include <fstream>          // ofstream
#include <vector>           // STL dynamic array
#include <unordered_map>    // STL hash table
#include <map>              // STL associative binary tree
#include <algorithm>        // STL sort
#include "Constants.h"
#include "WordMap.h"

using namespace std;
using namespace constants;

namespace wordMap
{
    ////////////////////////////////////////////////////////////////////////////////

    // Default constructor

    WordMap::WordMap()
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Default destructor

    WordMap::~WordMap()
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Increment an existing count, or insert a new key with a count of 1
    // WordMap may exceed available memory, depending on the number of unique words

    bool WordMap::incrementOrInsert(string word)
    {
        try
        {
            // STL automatically does the check for an existing or new key
            ++(this->map[word]);
        }
        catch(std::bad_alloc)
        {
            cout << "Out of memory in WordMap" << endl;
            return(false);
        }
        catch(...)
        {
            cout << "Exception in WordMap" << endl;
            return(false);
        }

        return(true);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the count for a given word

    unsigned int WordMap::getCount(string word)
    {
        return(this->map.at(word));
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the number of unique entries in the map

    unsigned int WordMap::getSize()
    {
        return(this->map.size());
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Print out the words and their associated counts, in alphabetical order

    void WordMap::print(Constants& constants)
    {
        // Open the output file
        // The output directory must already exist (preferrable to non-portable code for mkdir)
        ofstream outputFile(constants.getFullWordFileName());
		if (!outputFile.is_open())
		{
			cout << "failed to open word count file" << endl;
            return;
		}

        
        #ifdef HASH_TABLE   // Compile-time switch: word counts stored in a hash table

            // Create an array for sorting
            vector< pair<string, unsigned long> > pairArray;

            // Copy from the hash table into the array
            for (auto iterator = this->map.begin(); iterator != this->map.end(); ++iterator)
            {
                pairArray.push_back(*iterator);
            }

            // Sort the array
            sort(pairArray.begin(), pairArray.end());

            // Traverse the entire array in sorted order
            for (auto iterator = pairArray.begin(); iterator != pairArray.end(); ++iterator)
            {
                string word = iterator->first;
                unsigned long count = iterator->second;

                outputFile << word << "\t" << count << endl;
            }

        
        #else   // Compile-time switch: word counts stored in a binary tree

            // Output each word and its count
            for (auto iterator = this->map.begin(); iterator != this->map.end(); ++iterator)
            {
                string word = iterator->first;
                unsigned long count = iterator->second;

                outputFile << word << "\t" << count << endl;
            }

        #endif

        // Close the file
        outputFile.close();

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Just for testing purposes, to time the traversal

    void WordMap::testTraversal()
    {
        #ifdef HASH_TABLE   // Compile-time switch: word counts stored in a hash table

            // Create an array for sorting
            vector< pair<string, unsigned long> > pairArray;

            // Copy from the hash table into the array
            for (auto iterator = this->map.begin(); iterator != this->map.end(); ++iterator)
            {
                pairArray.push_back(*iterator);
            }

            // Sort the array
            sort(pairArray.begin(), pairArray.end());


            // Traverse the entire array in sorted order
            for (auto iterator = pairArray.begin(); iterator != pairArray.end(); ++iterator)
            {
                string word = iterator->first;
                unsigned long count = iterator->second;

                // Do nothing else
            }

        #else   // Compile-time switch: word counts stored in a binary tree

            // Traverse the entire map in sorted order
            for (auto iterator = this->map.begin(); iterator != this->map.end(); ++iterator)
            {
                string word = iterator->first;
                unsigned long count = iterator->second;

                // Do nothing else
            }

        #endif

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

}   // namespace wordMap