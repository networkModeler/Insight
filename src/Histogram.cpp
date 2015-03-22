////////////////////////////////////////////////////////////////////////////////
//
// Filename:    Histogram.cpp
//
// Purpose:     methods for Histogram class
//
// Comments:    Manages an STL array as a histogram of words-per-line
//              Designed for memory-efficient fast-calculation of running median
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>     // cout, etc
#include <iomanip>      // setw
#include <vector>       // STL dynamic array
#include "Histogram.h"

using namespace std;

namespace histogram
{
    ////////////////////////////////////////////////////////////////////////////////

    // Default constructor

    Histogram::Histogram() : numEntries(0)
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Allocate vector space when the max words-per-line is known

    Histogram::Histogram(unsigned int size) : numEntries(0)
    {
        // Allocate the space and initialize to 0
        this->histogram.resize(size, 0);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Default destructor

    Histogram::~Histogram()
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Increment the count for the given words-per-line

    void Histogram::increment(unsigned int wordsPerLine)
    {
        // Increment the count for the given wordsPerLine
        ++(this->histogram[wordsPerLine]);

        // Increment the total number of entries in the histogram
        ++(this->numEntries);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Calculate the running median
    //
    // Essentially walks through the histogram, starting at 0, until it
    // accumulates enough entries to constitute half of the total entries.
    //
    // If k is the max-words-per-line (e.g. 50), this algorithm is O(k) complexity.
    // Most likely O(.5 k), but would be even less if words-per-line skews low.
    // When n is the number of lines, and n >> k, this algorithm is essentially
    // constant complexity.
    //
    // It's conceivable that this could be optimized to O(1) by maintaining a
    // "median pointer" that is updated each time a new line entry is added.
    // But it's probably not worth the code complexity as I believe the runtime
    // is dominated not by this algorithm but by the file I/O and text parsing.

    float Histogram::runningMedian()
    {
        // Initialize
        float median = 0;
        unsigned long subTotal = 0;
        unsigned long previousSubTotal = 0;
        unsigned long previousWordsPerLine = 0;
        unsigned int size = this->histogram.size();
        unsigned int half = this->numEntries / 2;

        // For each entry in the histogram, starting at 0
        for (unsigned int wordsPerLine = 0; wordsPerLine < size; ++wordsPerLine)
        {
            // Check if there were any entries for this wordsPerLine
            unsigned long count = this->histogram[wordsPerLine];
            if (count > 0)
            {
                // Accumulate the number of entries so far
                subTotal += count;

                // Check if we have more than half the entries
                if (subTotal > half)
                {
                    // Check if the number of entries is odd
                    if (this->numEntries & 0x1)
                    {
                        // Odd: the median is simply this wordsPerLine
                        median = (float)wordsPerLine;
                    }
                    else
                    {
                        // Even: check if we are just past the cusp
                        if (previousSubTotal == half)
                        {
                            // The median is the average of this and the previous wordsPerLine
                            median = (previousWordsPerLine + wordsPerLine) / 2.0f;
                        }
                        else
                        {
                            // The median is simply this wordsPerLine
                            median = (float)wordsPerLine;
                        }
                    }

                    // We're done
                    break;
                }

                // Remember for the next iteration
                previousWordsPerLine = wordsPerLine;
                previousSubTotal = subTotal;
            }
        }

        return(median);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Print the histogram

    void Histogram::print()
    {
        cout << left << setw(24) << "Histogram entries:" << this->numEntries << endl;

        int index = 0;
        for (auto iterator = this->histogram.begin(); iterator != this->histogram.end(); ++iterator)
        {
            cout << index++ << "\t" << *iterator << endl;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////

}   // namespace histogram