////////////////////////////////////////////////////////////////////////////////
//
// Filename:    Parser.h
//
// Purpose:     header for Parser class
//
// Comments:    This class fetches files and parses them
//
////////////////////////////////////////////////////////////////////////////////

#ifndef	PARSER_H
#define	PARSER_H

#include <string>
#include <fstream>      // ofstream
#include "Constants.h"
#include "WordMap.h"
#include "Histogram.h"
#include "Parser.h"

using namespace std;
using namespace wordMap;
using namespace histogram;
using namespace constants;

////////////////////////////////////////////////////////////////////////////////

namespace	parser
{
	class Parser
	{
		public:

            // constructor
            Parser();

            // destructor
            ~Parser();

             // parses all files in given directory
            void parse(Constants& constants, WordMap& wordMap, Histogram& histogram, ofstream& outputFile);

            // output statistics of the run
            void stats();

        private:

            // parses a single file
            void parseFile(string& fileName, string& delimiters, string& punctuation,
                           WordMap& wordMap, Histogram& histogram, ofstream& outputFile);

            // parses a single line
            void parseLine(string& fileName, string& delimiters, string& punctuation,
                           WordMap& wordMap, Histogram& histogram, ofstream& outputFile);

            // normalize a word to a standard form
            void normalizeWord(string& word, string& punctuation);

            // whatever updating required per word
            void updateWordStats(string& word, WordMap& wordMap);

            // whatever updating required per line
            void updateLineStats(unsigned int numWordsThisLine, Histogram& histogram, ofstream& outputFile);

            // statistics
            unsigned long   numFiles;       // number of files read in
            unsigned long   numLines;       // number of lines read in
            unsigned long   numWords;       // number of words read in
            unsigned long   numUnique;      // number of unique words read in
            unsigned int    minWords;       // minimum words per line read in
            unsigned int    maxWords;       // maximum words per line read in
            float           medianWords;    // median words per line overall
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif	PARSER_H
////////////////////////////////////////////////////////////////////////////////