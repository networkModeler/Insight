////////////////////////////////////////////////////////////////////////////////
//
// Filename:    Parser.cpp
//
// Purpose:     methods for Parser class
//
// Comments:    This class fetches files and parses them
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>     // cout, etc
#include <iomanip>      // setprecision
#include <fstream>      // ifstream
#include <algorithm>    // transform() for lower casing
#include <climits>      // UINT_MAX
#include "Constants.h"
#include "FileList.h"
#include "Parser.h"

using namespace std;
using namespace constants;
using namespace fileList;

namespace parser
{
    ////////////////////////////////////////////////////////////////////////////////

    // Default constructor, initialize all private members

    Parser::Parser() : numFiles(0), numLines(0), numWords(0), numUnique(0),
                       minWords(UINT_MAX), maxWords(0), medianWords(0.0)
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Default destructor

    Parser::~Parser()
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Parse all files in the given directory

    void Parser::parse(Constants& constants, WordMap& wordMap, Histogram& histogram, ofstream& outputFile)
    {
        cout << endl;
        cout << "PROCESSING" << endl;

        // Fetch a linked list of file names in the given directory
        FileList myFileList;
        string directoryName = constants.getInputDirectoryName();
        cout << left << setw(24) << "Opening directory:" << directoryName << endl;
        if (!myFileList.fetchFileNames(directoryName))
        {
            cout << left << setw(24) << "Could not open directory:" << directoryName << endl;
            return;
        }
        myFileList.print();

        // For each file
        string delimiters = constants.getDelimiters();
        string punctuation = constants.getPunctuation();
        for (auto iterator = myFileList.begin(); iterator != myFileList.end(); ++iterator)
        {
            string fileName = *iterator;

            // Construct the full file name
            string fullName = directoryName + '/' + fileName;

            // Parse this file
            cout << left << setw(24) << "Parsing file:" << fileName << endl;
            this->parseFile(fullName, delimiters, punctuation, wordMap, histogram, outputFile);
            ++(this->numFiles);
        }

        // Update statistics
        this->numUnique = wordMap.getSize();
        this->medianWords = histogram.runningMedian();

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Parse a single file

    void Parser::parseFile(string& fileName, string& delimiters, string& punctuation,
                           WordMap& wordMap, Histogram& histogram, ofstream& outputFile)
    {
		// Open the input file
		ifstream inputFile(fileName);
		if (!inputFile.is_open())
		{
			cout << left << setw(24) << "Failed to open file:" << fileName << endl;
			return;
		}

        // Get each line from the file
        string line;
		while (getline(inputFile, line))
		{
            // Parse this line
            this->parseLine(line, delimiters, punctuation, wordMap, histogram, outputFile);
            ++(this->numLines);
        }

        // Close the file
        inputFile.close();

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Parse a single line

    void Parser::parseLine(string& line, string& delimiters, string& punctuation,
                           WordMap& wordMap, Histogram& histogram, ofstream& outputFile)
    {
        // Initialize
        unsigned int numWordsThisLine = 0;
        size_t start = 0;
        size_t finish = 0;

        // For each word in this line
        while (true)
        {
            // Look for the start and finish of a word
            start = line.find_first_not_of(delimiters, finish);
            finish = line.find_first_of(delimiters, start);

            // Check if a word was found
            if ((start == string::npos) && (finish == string::npos))
            {
                // End of line
                break;
            }

            // Found a word
            ++numWordsThisLine;
            string word = line.substr(start, (finish - start));
            this->normalizeWord(word, punctuation);

            // Update statistics for this word
            this->updateWordStats(word, wordMap);
        }

        // Update statistics for this line
        this->updateLineStats(numWordsThisLine, histogram, outputFile);

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Normalize word to a standard form

    void Parser::normalizeWord(string& word, string& punctuation)
    {
        // Convert to lower case
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Remove any punctuation
        int numChars = punctuation.size();
        for (int i = 0; i < numChars; ++i)
        {
            word.erase(std::remove(word.begin(), word.end(), punctuation[i]), word.end());
        }

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Update statistics for one word

    void Parser::updateWordStats(string& word, WordMap& wordMap)
    {
        // Update the count for this word in the WordMap
        wordMap.incrementOrInsert(word);

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Update statistics for one line

    void Parser::updateLineStats(unsigned int numWordsThisLine, Histogram& histogram, ofstream& outputFile)
    {
        // Update total number of words
        this->numWords += numWordsThisLine;

        // Update minimum number of words per line
        if (this->minWords > numWordsThisLine)
        {
            this->minWords = numWordsThisLine;
        }

        // Update maximum number of words per line
        if (this->maxWords < numWordsThisLine)
        {
            this->maxWords = numWordsThisLine;
        }

        // Update the histogram of words per line
        histogram.increment(numWordsThisLine);

        // Calculate the running median and output it to the open file
        float median = histogram.runningMedian();
        outputFile << fixed << setprecision(1) << median << endl;

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Output statistics of the run

    void Parser::stats()
    {
        cout << endl;
        cout << "STATISTICS" << endl;
        cout << left << setw(24) << "number of files parsed:" << this->numFiles << endl;
        cout << left << setw(24) << "number of lines parsed:" << this->numLines << endl;
        cout << left << setw(24) << "number of words parsed:" << this->numWords << endl;
        cout << left << setw(24) << "number of unique words:" << this->numUnique << endl;
        cout << left << setw(24) << "minimum words per line:" << this->minWords << endl;
        cout << left << setw(24) << "maximum words per line:" << this->maxWords << endl;
        cout << left << setw(24) << "median words per line:"  << setprecision(1) << this->medianWords << endl;

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////

}   // namespace parser