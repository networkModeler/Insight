////////////////////////////////////////////////////////////////////////////////
//
// Filename:    WordMap.h
//
// Purpose:     header for WordMap class
//
// Comments:    Manages an STL binary tree of unique words and associated counts
//
////////////////////////////////////////////////////////////////////////////////

#ifndef	WORDMAP_H
#define	WORDMAP_H

#include <string>
#include <unordered_map>    // STL hash table
#include <map>              // STL associative binary tree
#include "Constants.h"

using namespace std;
using namespace constants;

////////////////////////////////////////////////////////////////////////////////

// Use either a hash table or a binary tree to store the words and their counts
//#undef HASH_TABLE
#define HASH_TABLE

namespace	wordMap
{
    class WordMap
    {
        public:

            // default constructor
            WordMap();

            // default destructor
            ~WordMap();

            // Increment an existing count, or insert a new key with a count of 1
            bool incrementOrInsert(string word);

            // get the count for a given word
            unsigned int getCount(string word);

            // get the number of unique words in the map
            unsigned int getSize();

            // print out the words and their associated counts, in alphabetical order
            void print(Constants& constants);

            // just for testing purposes, to time the traversal
            void testTraversal();

        private:

#ifdef HASH_TABLE   // Compile-time switch: word counts stored in a hash table

            // map of words and associated counts
            unordered_map<string, unsigned long> map;

#else   // Compile-time switch: word counts stored in a binary tree

            // map of words and associated counts
            map<string, unsigned long> map;

#endif

    };
}

////////////////////////////////////////////////////////////////////////////////
#endif	WORDMAP_H
////////////////////////////////////////////////////////////////////////////////
