////////////////////////////////////////////////////////////////////////////////
//
// Filename:    Histogram.h
//
// Purpose:     header for Histogram class
//
// Comments:    Manages an STL array as a histogram of words-per-line
//              Designed for memory-efficient fast-calculation of running median
//
////////////////////////////////////////////////////////////////////////////////

#ifndef	HISTOGRAM_H
#define	HISTOGRAM_H

#include <vector>       // STL dynamic array

using namespace std;

////////////////////////////////////////////////////////////////////////////////

namespace	histogram
{
    class Histogram
    {
        public:

            // default constructor
            Histogram();

            // constructor with specified size (maximum words-per-line)
            Histogram(unsigned int size);

            // default destructor
            ~Histogram();

            // Increment the count for the given words-per-line
            void increment(unsigned int wordsPerLine);

            // calculate the running median
            float runningMedian();

            // print the histogram
            void print();

        private:

            // histogram of counts from 0 to max-words-per-line 
            vector<unsigned long>   histogram;

            // total number of entries that have been added to the histogram
            unsigned long           numEntries;
    };
}

////////////////////////////////////////////////////////////////////////////////
#endif	// HISTOGRAM_H
////////////////////////////////////////////////////////////////////////////////
