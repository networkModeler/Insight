////////////////////////////////////////////////////////////////////////////////
//
// Filename:    Constants.h
//
// Purpose:     header for constants class
//
// Comments:    Miscellaneous constants used by the program
//
////////////////////////////////////////////////////////////////////////////////

#ifndef	CONSTANTS_H
#define	CONSTANTS_H

#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

namespace	constants
{
    class Constants
    {
        public:

            // default constructor
            Constants();

            // default destructor
            ~Constants();

            // constructor with user parameters, useful for testing
            Constants(string& inputDirectoryName, string& outputDirectoryName,
                      string& wordFileName, string& medianFileName,
                      string& delimiters, string& punctuation,
                      unsigned int maxWordsPerLine);

            // read-only access to constants
            string          getInputDirectoryName();
            string          getOutputDirectoryName();
            string          getWordFileName();
            string          getMedianFileName();
            string          getFullWordFileName();
            string          getFullMedianFileName();
            string          getDelimiters();
            string          getPunctuation();
            unsigned int    getMaxWordsPerLine();

            void            print();

        private:
            string          inputDirectoryName;     // name of directory with input files
            string          outputDirectoryName;    // name of directory with output files
            string          wordFileName;           // name of output file for word counts
            string          medianFileName;         // name of output file for running medians
            string          delimiters;             // word delimiter characters
            string          punctuation;            // punctuation characters to be removed
	        unsigned int    maxWordsPerLine;        // maximum words from command line

            // derived constants
            string          fullWordFileName;       // directory + filename
            string          fullMedianFileName;     // directory + filename
    };
}

////////////////////////////////////////////////////////////////////////////////
#endif  // CONSTANTS_H
////////////////////////////////////////////////////////////////////////////////
