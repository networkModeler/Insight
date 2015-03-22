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
#include <ctime>        // clock
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
        // Remember the starting CPU clock
        clock_t clockTicks = clock();

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
        string fileName = constants.getFullMedianFileName();
        ofstream outputFile(fileName);
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

        // Calculate the number of CPU seconds
        clockTicks = clock() - clockTicks;
        float seconds = (float)clockTicks / CLOCKS_PER_SEC;
        cout << endl;
        cout << left << setw(24) << "CPU seconds elapsed:" << fixed << setprecision(3) << seconds << endl;

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

}   // namespace wordCount