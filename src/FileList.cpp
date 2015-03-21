////////////////////////////////////////////////////////////////////////////////
//
// Filename:    FileList.cpp
//
// Purpose:     methods for FileList class
//
// Comments:    Manages an STL linked list of filenames in the given directory
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>     // cout, etc
#include <iomanip>      // setw
#include <vector>       // STL dynamic array
#include <algorithm>    // STL sort
#include "dirent.h"
#include "FileList.h"

using namespace std;

namespace fileList
{
    ////////////////////////////////////////////////////////////////////////////////

    // Default constructor

    FileList::FileList()
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Default destructor

    FileList::~FileList()
    {
        // NA
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Fetch file names from given directory, store in a sorted dynamic array

    bool FileList::fetchFileNames(string directoryName)
    {
        dirent* dirEntry = NULL;
        DIR*    dirPointer = NULL;

        // Open the given directory
        dirPointer = opendir(directoryName.c_str());
        if (dirPointer == NULL)
        {
            return(false);
        }

        // For each file
        while (dirEntry = readdir(dirPointer))
        {
            if (dirEntry == NULL)
            {
                return(false);
            }

            // Filter out the current directory and parent directory
            if (dirEntry->d_name[0] == '.')
            {
                continue;
            }

            // Add this file's name to the list
            string fileName = dirEntry->d_name;
            this->fileNames.push_back(fileName);
        }

        // Close the directory
        closedir(dirPointer);

        // Sort the list of file names
        std::sort(this->fileNames.begin(), this->fileNames.end());

        return(true);
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Begin iterator

    vector<string>::iterator FileList::begin()
    {
        return(this->fileNames.begin());
    }

    ////////////////////////////////////////////////////////////////////////////////

    // End iterator

    vector<string>::iterator FileList::end()
    {
        return(this->fileNames.end());
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Print the file name list

    void FileList::print()
    {
        // Output the total number of files
        unsigned int size = this->fileNames.size();
        cout << left << setw(24) << "Number of files found:" << size << endl;

        /*
        // Output the name of each file
        for (auto iterator = this->fileNames.begin(); iterator != this->fileNames.end(); ++iterator)
        {
            string fileName = *iterator;
            cout << fileName << endl;
        }
        */
    }

    ////////////////////////////////////////////////////////////////////////////////

}   // namespace fileList