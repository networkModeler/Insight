////////////////////////////////////////////////////////////////////////////////
//
// Filename:    main.cpp
//
// Purpose:     Main function for Insight coding puzzle
//
// Author:      Dale Wong
//
////////////////////////////////////////////////////////////////////////////////

#include "WordCount.h"
#include "Test.h"

using namespace wordCount;
using namespace test;

////////////////////////////////////////////////////////////////////////////////

//#define TEST

int main(int argc, char* argv[])
{
    #ifndef TEST

        // Instantiate a Constants object, just use the default values
        Constants myConstants;

        // Run the coding challenge
        WordCount myWordCount;
        myWordCount.run(myConstants);

    #else

        testAll();

    #endif

    return(0);
}

////////////////////////////////////////////////////////////////////////////////
