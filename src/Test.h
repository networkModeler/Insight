////////////////////////////////////////////////////////////////////////////////
//
// Filename:    Test.h
//
// Purpose:     header for Test functions
//
// Comments:    
//
////////////////////////////////////////////////////////////////////////////////

#ifndef	TEST_H
#define	TEST_H

////////////////////////////////////////////////////////////////////////////////

namespace	test
{
    void testAll();

    void testFileList(int& numPassed, int& numFailed);

    void testParser(int& numPassed, int& numFailed);

    void testWordMap(int& numPassed, int& numFailed);
    void testWordMapCounts(int& numPassed, int& numFailed);
    void testWordMapTimed(int& numPassed, int& numFailed);

    void testHistogram(int& numPassed, int& numFailed);
    void testHistogramOdd(int& numPassed, int& numFailed);
    void testHistogramEven(int& numPassed, int& numFailed);
}

////////////////////////////////////////////////////////////////////////////////
#endif	TEST_H
////////////////////////////////////////////////////////////////////////////////
