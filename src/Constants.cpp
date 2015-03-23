////////////////////////////////////////////////////////////////////////////////
//
// Filename:    Constants.cpp
//
// Purpose:     methods for Constants class
//
// Comments:    Miscellaneous constants used by the program
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>     // cout, etc
#include <iomanip>      // setw
#include "Constants.h"

using namespace std;

namespace constants
{
    ////////////////////////////////////////////////////////////////////////////////

    // Default constructor, initialize all private members
    // The delimiter characters are from isspace() and ispunct() in the "C" locale

    Constants::Constants() :
        inputDirectoryName("wc_input"),
        outputDirectoryName("wc_output"),
        wordFileName("wc_result.txt"),
        medianFileName("med_result.txt"),
        delimiters(" \t\n\v\f\r"),
        punctuation("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"),
        maxWordsPerLine(50)
    {
        // Derived constants
        this->fullWordFileName   = this->outputDirectoryName + '/' + this->wordFileName;
        this->fullMedianFileName = this->outputDirectoryName + '/' + this->medianFileName;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Constructor with user parameters, useful for testing

    Constants::Constants(string& inputDirectoryName, string& outputDirectoryName,
                         string& wordFileName, string& medianFileName,
                         string& delimiters, string& punctuation,
                         unsigned int maxWordsPerLine)
    {
        // Initialize
        this->inputDirectoryName    = inputDirectoryName;
        this->outputDirectoryName   = outputDirectoryName;
        this->wordFileName          = wordFileName;
        this->medianFileName        = medianFileName;
        this->delimiters            = delimiters;
        this->punctuation           = punctuation;
        this->maxWordsPerLine       = maxWordsPerLine;

        // Derived constants
        this->fullWordFileName   = this->outputDirectoryName + '/' + this->wordFileName;
        this->fullMedianFileName = this->outputDirectoryName + '/' + this->medianFileName;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Default destructor

    Constants::~Constants()
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the directory name that has the files to be processed

    string Constants::getInputDirectoryName()
    {
        return(this->inputDirectoryName);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the directory name for the output files

    string Constants::getOutputDirectoryName()
    {
        return(this->outputDirectoryName);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the file name for the word counts

    string Constants::getWordFileName()
    {
        return(this->wordFileName);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the file name for the running medians

    string Constants::getMedianFileName()
    {
        return(this->medianFileName);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the full path file name for the word counts

    string Constants::getFullWordFileName()
    {
        return(this->fullWordFileName);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the full path file name for the running medians

    string Constants::getFullMedianFileName()
    {
        return(this->fullMedianFileName);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the delimiter characters for separating words

    string Constants::getDelimiters()
    {
        return(this->delimiters);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the punctuation characters to be removed from words

    string Constants::getPunctuation()
    {
        return(this->punctuation);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Get the user specified maximum words per line in the input files

    unsigned int Constants::getMaxWordsPerLine()
    {
        return(this->maxWordsPerLine);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Print the values of the constants

    void Constants::print()
    {
        cout << endl;
        cout << "PARAMETERS" << endl;
        cout << left << setw(24) << "input directory name:"     << this->inputDirectoryName << endl;
        cout << left << setw(24) << "output directory name:"    << this->outputDirectoryName << endl;
        cout << left << setw(24) << "word count filename:"      << this->wordFileName << endl;
        cout << left << setw(24) << "median filename:"          << this->medianFileName << endl;
        //cout << left << setw(24) << "delimiters:"               << this->delimiters << endl;
        cout << left << setw(24) << "punctuation characters:"   << this->punctuation << endl;
        cout << left << setw(24) << "maximum words per line:"   << this->maxWordsPerLine << endl;
    }

    ////////////////////////////////////////////////////////////////////////////////

}   // namespace constants