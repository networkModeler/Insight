////////////////////////////////////////////////////////////////////////////////
//
// Filename:    Test.cpp
//
// Purpose:     test functions
//
// Comments:    
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>     // cout, etc
#include <iomanip>      // setw
#include <cstdlib>      // rand, srand
#include <ctime>        // clock
#include <cmath>        // floor
#include "WordMap.h"
#include "Histogram.h"
#include "Test.h"

using namespace std;
using namespace wordMap;
using namespace histogram;

namespace test
{
    ////////////////////////////////////////////////////////////////////////////////

    // Run all tests

    void testAll()
    {
        // Initialize
        int numPassed = 0;
        int numFailed = 0;

        // Test each of the major components
        testFileList(numPassed, numFailed);
        testParser(numPassed, numFailed);
        testWordMap(numPassed, numFailed);
        testHistogram(numPassed, numFailed);

        // Final results
        cout << endl;
        cout << "numPassed:" << numPassed << endl;
        cout << "numFailed:" << numFailed << endl;
    }

    ////////////////////////////////////////////////////////////////////////////////

    void testFileList(int& numPassed, int& numFailed)
    {
        // just a stub for now
    }

    ////////////////////////////////////////////////////////////////////////////////

    void testParser(int& numPassed, int& numFailed)
    {
        // just a stub for now
    }

    ////////////////////////////////////////////////////////////////////////////////

    void testWordMap(int& numPassed, int& numFailed)
    {
        testWordMapCounts(numPassed, numFailed);
        testWordMapTimed(numPassed, numFailed);
    }

    ////////////////////////////////////////////////////////////////////////////////

    void testHistogram(int& numPassed, int& numFailed)
    {
        testHistogramOdd(numPassed, numFailed);
        testHistogramEven(numPassed, numFailed);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Keep adding words with increasing length and count until it fails

    void testWordMapCounts(int& numPassed, int& numFailed)
    {
        cout << endl;
        cout << "testWordMapCounts" << endl;

        // Initialize
        int maxCount = 250;
        bool failed = false;

        // Instantiate a WordMap
        WordMap myWordMap;

        // Insert words with increasing length and count
        for (int count = 1; count <= maxCount; ++count)
        {
            // Build a word of this length
            string word;
            for (int i = 1; i <= count; ++i)
            {
                word += 'a';
            }

            // Increment it this many times
            for (int i = 1; i <= count; ++i)
            {
                myWordMap.incrementOrInsert(word);
            }
        }

        // Verify the counts
        for (int count = 1; count <= maxCount; ++count)
        {
            // Build a word of this length
            string word;
            for (int i = 1; i <= count; ++i)
            {
                word += 'a';
            }

            // Check if the count is correct
            if (myWordMap.getCount(word) != count)
            {
                failed = true;
            }
        }

        // Statistics
        unsigned int numEntries = (maxCount * (maxCount + 1)) / 2;
        cout << left << setw(24) << "number of words:" << maxCount << endl;
        cout << left << setw(24) << "number of entries:" << numEntries << endl;

        // Pass or fail
        if (!failed)
        {
            ++numPassed;
            cout << "Test passed" << endl;
        }
        else
        {
            ++numFailed;
            cout << "Test failed" << endl;
        }

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Keep adding words with increasing length and count until it fails

    void testWordMapTimed(int& numPassed, int& numFailed)
    {
        cout << endl;
        cout << "testWordMapTimed" << endl;

        // Remember the starting CPU clock
        clock_t clockTicks = clock();

        // Initialize
        int maxCount = 250;
        int repititions = 10;
        bool failed = false;

        // Instantiate a WordMap
        WordMap myWordMap;

        // Perform a number of repititions for a larger sample
        for (int repeat = 1; repeat <= repititions; ++repeat)
        {
            // Insert words with increasing length and count
            for (int count = 1; count <= maxCount; ++count)
            {
                // Build a word of this length
                string word;
                for (int i = 1; i <= count; ++i)
                {
                    word += 'a';
                }

                // Increment it this many times
                for (int i = 1; i <= count; ++i)
                {
                    myWordMap.incrementOrInsert(word);
                }
            }

            // Verify the counts
            for (int count = 1; count <= maxCount; ++count)
            {
                // Build a word of this length
                string word;
                for (int i = 1; i <= count; ++i)
                {
                    word += 'a';
                }

                // Check if the count is correct
                if (myWordMap.getCount(word) != (repeat * count))
                {
                    failed = true;
                }
            }

            // Iterate through the entire map in sorted order
            myWordMap.testTraversal();
        }

        // Calculate the number of CPU seconds
        clockTicks = clock() - clockTicks;
        float seconds = (float)clockTicks / CLOCKS_PER_SEC;

        // Statistics
        unsigned int numEntries = repititions * ((maxCount * (maxCount + 1)) / 2);
        cout << left << setw(24) << "number of words:" << maxCount << endl;
        cout << left << setw(24) << "number of entries:" << numEntries << endl;
        cout << left << setw(24) << "Seconds elapsed:" << fixed << setprecision(3) << seconds << endl;

        // Pass or fail
        if (!failed)
        {
            ++numPassed;
            cout << "Test passed" << endl;
        }
        else
        {
            ++numFailed;
            cout << "Test failed" << endl;
        }

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Generate a random sequence with a known median, compare with calculated median
    // Odd number of entries

    void testHistogramOdd(int& numPassed, int& numFailed)
    {
        //////////////
        // Initialize
        //////////////

        int maxWordCount = 50;
        int numEntries = 1000001;
        int numTests = 10;

        /////////////////////////////////
        // Execute test a number of times
        /////////////////////////////////

        for (int i = 0; i < numTests; ++i)
        {
            cout << endl;
            cout << "testHistogramOdd test " << i << endl;

            // Instantiate a Histogram
            Histogram myHistogram(maxWordCount);

            // Initialize a random number generator
            srand(i);

            ///////////////////////////////////////////////
            // Generate a random sequence with known median
            ///////////////////////////////////////////////

            // Pick a random median
            // Must avoid the two values: 0 and (maxWordCount - 1)
            int median = rand() % (maxWordCount - 2) + 1;

            // Add an entry for this median
            int medianCount = 1;
            for (int i = 0; i < medianCount; ++i)
            {
                myHistogram.increment(median);
            }

            // Add half of the remaining entries at less than median
            int lowerHalfCount = (numEntries - medianCount) / 2;
            for (int i = 0; i < lowerHalfCount; ++i)
            {
                int wordCount = rand() % median;
                myHistogram.increment(wordCount);
            }

            // Add the remaining entries at greater than median
            int remainingCount = (numEntries - medianCount - lowerHalfCount);
            for (int i = 0; i < remainingCount; ++i)
            {
                int wordCount = (rand() % (maxWordCount - median - 1)) + (median + 1);
                myHistogram.increment(wordCount);
            }

            // Print the histogram (for debugging)
            myHistogram.print();

            //////////////////////////////////
            // Calculate and verify the median
            //////////////////////////////////

            // Calculate the median
            int calculatedMedian = (int)(floor(myHistogram.runningMedian()));
            cout << left << setw(24) << "median:" << median << endl;
            cout << left << setw(24) << "calculatedMedian:" << calculatedMedian << endl;

            // Check if it matches the actual median
            if (calculatedMedian == median)
            {
                ++numPassed;
                cout << "Test passed" << endl;
            }
            else
            {
                ++numFailed;
                cout << "Test failed" << endl;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Generate a random sequence with a known median, compare with calculated median
    // Even number of entries

    void testHistogramEven(int& numPassed, int& numFailed)
    {
        //////////////
        // Initialize
        //////////////

        int maxWordCount = 50;
        int numEntries = 1000000;
        int numTests = 10;

        /////////////////////////////////
        // Execute test a number of times
        /////////////////////////////////

        for (int i = 0; i < numTests; ++i)
        {
            cout << endl;
            cout << "testHistogramEven test " << i << endl;

            // Instantiate a Histogram
            Histogram myHistogram(maxWordCount);

            // Initialize a random number generator
            srand(i);

            ///////////////////////////////////////////////
            // Generate a random sequence with known median
            ///////////////////////////////////////////////

            // Pick two different random values to flank the median
            // Must avoid the two values: 0 and (maxWordCount - 1)
            int median1 = rand() % (maxWordCount - 2) + 1;
            int median2 = rand() % (maxWordCount - 2) + 1;
            while (median2 == median1)
            {
                median2 = rand() % (maxWordCount - 2) + 1;
            }
            int lower = min(median1, median2);
            int upper = max(median1, median2);
            float median = (lower + upper) / 2.0f;

            // Add entries for these values that flank the median
            int medianCount = 1;
            for (int i = 0; i < medianCount; ++i)
            {
                myHistogram.increment(lower);
                myHistogram.increment(upper);
            }

            // Add half of the remaining entries at less than lower flank
            int lowerHalfCount = (numEntries - 2 * medianCount) / 2;
            for (int i = 0; i < lowerHalfCount; ++i)
            {
                int wordCount = rand() % lower;
                myHistogram.increment(wordCount);
            }

            // Add the remaining entries at greater than upper flank
            int remainingCount = (numEntries - 2 * medianCount - lowerHalfCount);
            for (int i = 0; i < remainingCount; ++i)
            {
                int wordCount = (rand() % (maxWordCount - upper - 1)) + (upper + 1);
                myHistogram.increment(wordCount);
            }

            // Print the histogram (for debugging)
            myHistogram.print();

            //////////////////////////////////
            // Calculate and verify the median
            //////////////////////////////////

            // Calculate the median
            float calculatedMedian = myHistogram.runningMedian();
            cout << left << setw(24) << "median:" << fixed << setprecision(1) << median << endl;
            cout << left << setw(24) << "calculatedMedian:" << fixed << setprecision(1) << calculatedMedian << endl;

            // Check if it matches the actual median
            if (calculatedMedian == median)
            {
                ++numPassed;
                cout << "Test passed" << endl;
            }
            else
            {
                ++numFailed;
                cout << "Test failed" << endl;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////

}   // namespace test