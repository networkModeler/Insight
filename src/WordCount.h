////////////////////////////////////////////////////////////////////////////////
//
// Filename:    WordCount.h
//
// Purpose:     header for WordCount class
//
// Comments:    This is the top-level class for the coding challenge
//
////////////////////////////////////////////////////////////////////////////////

#ifndef	WORDCOUNT_H
#define	WORDCOUNT_H

#include "Constants.h"
using namespace constants;

////////////////////////////////////////////////////////////////////////////////

namespace	wordCount
{
	class WordCount
	{
		public:

            WordCount();    // default constructor
            ~WordCount();   // default destructor

            void run(Constants& constants); // run the coding challenge

        private:

	};
}

////////////////////////////////////////////////////////////////////////////////
#endif	// WORDCOUNT_H
////////////////////////////////////////////////////////////////////////////////