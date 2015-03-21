////////////////////////////////////////////////////////////////////////////////
//
// Filename:    FileList.h
//
// Purpose:     header for FileList class
//
// Comments:    Manages an STL linked list of filenames in the given directory
//
////////////////////////////////////////////////////////////////////////////////

#ifndef	FILELIST_H
#define	FILELIST_H

#include <string>
#include <vector>   // STL dynamic array

using namespace std;

////////////////////////////////////////////////////////////////////////////////

namespace	fileList
{
    class FileList
    {
        public:

            // default constructor
            FileList();

            // default destructor
            ~FileList();

            // fetches names of files in given directory
            bool fetchFileNames(string directoryName);

            // begin iterator
            vector<string>::iterator begin();

            // end iterator
            vector<string>::iterator end();

            // print the file name list
            void print();

        private:

            // dynamic array of file names
            vector<string> fileNames;
    };
}

////////////////////////////////////////////////////////////////////////////////
#endif	// FILELIST_H
////////////////////////////////////////////////////////////////////////////////
