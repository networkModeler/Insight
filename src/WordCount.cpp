////////////////////////////////////////////////////////////////////////////////
//
// Filename:    WordCount.cpp
//
// Purpose:     methods for WordCount class
//
// Comments:    This is the top-level class for the coding challenge
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>     // cout, etc
#include <iomanip>      // setw
#include <climits>      // UINT_MAX
#include "Constants.h"
#include "WordMap.h"
#include "Histogram.h"
#include "Parser.h"
#include "WordCount.h"

using namespace std;
using namespace constants;
using namespace wordMap;
using namespace histogram;
using namespace parser;

namespace wordCount
{
    ////////////////////////////////////////////////////////////////////////////////

    // Default constructor

    WordCount::WordCount()
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Default destructor

    WordCount::~WordCount()
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Run the coding challenge

    void WordCount::run(Constants& constants)
    {
        cout << endl;
        cout << "RUNNING INSIGHT CODING CHALLENGE" << endl;

        // Print the given constants
        constants.print();

        // Instantiate a WordMap object to store the count for each word
        WordMap myWordMap;

        // Instantiate a Histogram object to store the count for each words-per-line
        Histogram myHistogram(constants.getMaxWordsPerLine());

        // Open a file for the running medians
        // Keep an open file so we can output the running medians as we parse each line,
        // rather than store a huge number of medians for output later
        ofstream outputFile(constants.getFullMedianFileName());
		if (!outputFile.is_open())
		{
			cout << "failed to open running median file" << endl;
            return;
		}

        // Parse the files
        Parser myParser;
        myParser.parse(constants, myWordMap, myHistogram, outputFile);
        myParser.stats();

        // Output the files
        outputFile.close();         // close the running median file
        myWordMap.print(constants); // output the word count file
        cout << endl;
        cout << "OUTPUT FILES" << endl;
        cout << left << setw(24) << "running median file:" << constants.getFullMedianFileName() << endl;
        cout << left << setw(24) << "word count file:" << constants.getFullWordFileName() << endl;

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

}   // namespace wordCount