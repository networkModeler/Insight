## INSIGHT CODING CHALLENGE BY DALE WONG ##

### Summary ###

My solution to the Insight coding challenge.  Development was in C++ (~1800 lines of code), in an object-oriented style, and makes use of the Standard Template Library.

There are two major design decisions:

- To store the unique words and their counts, I use a binary tree data structure.  This also satisfies the requirement to output the words in alphabetical order (as opposed to a hash table).
- To calculate a running median of words-per-line, I store a histogram of the number of occurrences for each possible value of words-per-line.  At any time, the median is calculated by a linear scan of this small histogram.  This approach is possible because there is a maximum words-per-line (i.e. 50).  This design has the advantage of not needing to store the words-per-line of every line parsed. 

Test functions were written to verify each major component.  A test suite of various text files was created to verify the program as a whole.

## Problem Statement ##

The original problem statement can be found at <https://github.com/InsightDataScience/cc-example> on GitHub.

Of particular note is that the number of files/lines can be very large.

### Assumptions ###

Particular to my solution:

- The maximum number of words per line is 50
- The maximum number of files fits in unsigned long (typically > 4B)
- The maximum number of lines fits in unsigned long (typically > 4B)
- The maximum number of words fits in unsigned long (typically > 4B)

Confirmed via correspondence:

- The delimiter characters are the same as isspace(): " \t\n\v\f\r"
- The punctuation characters are the same as ispunct(): "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
- Punctuation characters will not be treated as delimiters
- The g++ compiler will be available in the test environment

From the Insight FAQ:

- All words will be converted to lower case
- All punctuation will be removed from words
- All characters are simple ASCII
- All files in the input directory are text files



## Design ##

### Word Count:  Binary Tree vs. Hash Table ###

For the word count data structure, two alternatives immediately come to mind: binary trees and hash tables.

- Hash tables have fast O(1) insertion, but do not provide any ordered traversal.
- Binary trees have slower O(log n) insertion, but provide an easy ordered traversal.

If we used hash tables, an ordered traversal could be provided at the end of the run by copying its contents into an array, and then sorting the array (which would be O(n log n).

It is not obvious which of the two schemes would be faster, due to unknown constant factors in the implementations.  So I implemented both schemes (which is relatively easy with STL), and timed them.  I created a test that inserts words of length 1 to 250, and the count for each word is the same as its length (e.g. a word of length 250 is inserted 250 times).  This entire insertion loop is repeated 10 times, without reseting the data structure, so overall the test consists of 250 words and 313,750 insertions.

On my development platform, the binary tree test took an average of 0.392 cpu seconds, and the hash table took an average of 1.488 cpu seconds.  In other words, **the binary tree was a surprising 3.8 times faster than the hash table**.  Upon further investigation, most of the hash table time was spent on insertion, not on copying to an array and sorting.  This is especially surprising since hash tables are known for fast insertion performance.  This may just be due to a poor implementation on my development platform (Microsoft Visual Studio), but a Google search yielded links for other people complaining about the STL hash table insertion on Linux with g++.

Based on my timed test, I chose to use the binary tree data structure.

### Running Medians: Histogram vs Heaps ###

A well known solution to the problem of running-medians utilizes two heaps (i.e. priority queues).  The number of entries in each heap is kept in balance of each other (except the first heap may have one more entry than the second heap).  The first heap is a max-heap (where the root is the maximum entry in the heap), and the second heap is a min-heap (where the root is the minimum entry in the heap).  All entries in the first heap are <= to the root of the second heap, and all entries in the second heap are >= the root of the first heap.  The median is easily found: if the sizes of the heaps are equal, then the median is the average of the two roots of the heaps; else the median is the root of the first heap.

This heap-based solution initially sounds attractive because heap insertion is O(log n), and median calculation is O(1).  However, the major drawback of this solution is that the entire set of data must be stored in the heaps.  In the scenario described in the original problem statement, we should anticipate a very large number of lines, and the data can easily exceed the amount of RAM available.  This would then necessitate either some disk caching, or some distributed computing, either of which is complex and slow.

A much more suitable solution exists, if there is an upper limit on the words-per-line.  I confirmed with David Drummond that there is indeed such a limit, and it is a relatively low 50 words-per-line.  Since words-per-line is inherently integer, we can simply use a fixed array to store a histogram of the occurrences of each words-per-line.  In order to calculate the median at any time, we simply scan the histogram starting from 0, and stop when the subtotal has accumulated more than half the total number of entries (plus a little handling of the even/odd peculiarities).

With this histogram scheme, insertion is O(1) and median calculation is O(k), where k is upper limit on words-per-line (e.g. 50).  When n >> k, as in this problem statement, the median calculation is effectively O(1).  And most importantly, the principal benefit is that **the memory usage is bounded and small**, obviating the need for disk caching or distributed computing.

### Overview of Code Structure ###

The following are the major modules:

- main.cpp:			The standard top-level entry point for the program
- WordCount.cpp:	The top-level object to instantiate to run this coding challenge
- FileList.cpp:		A linked list of filenames, fetched from a given directory, and sorted alphabetically
- Parser.cpp:		Parses each file into lines, parses lines into words, normalizes words
- WordMap.cpp:		Keeps track of the word counts
- Histogram.cpp:	Keeps track of the words-per-line counts, calculates medians
- Constants.cpp:	Holds various constants for the program
- Test.cpp:			Test methods

The following is the call graph of the principal object::methods for this program:

	main()
		WordCount::run()
			Parser::parse()
				FileList::fetchFileNames()
				Parser::parseFile()
					Parser::parseLine()
						Parser::normalizeWord()
						WordMap::incrementOrInsert()
						Histogram::increment()
						Histogram::runningMedian()
			WordMap::print()
		testAll()

## Testing ##

Tests were developed for the two major components, WordMap and Histogram.  If 100% test coverage is desired, and more time is allotted, tests for all components could easily be completed.  However, the remaining components are deemed to be relatively low risk.

The WordMap (binary tree to store the word counts) is a thin wrapper around the STL map object.  As such, the underlying functionality is rock solid and I only needed to develop a simple insert/verify routine to test my wrapper .  Most of the testing is focused instead on characterizing the performance of the WordMap.  This was already described above in the section "Word Count:  Binary Tree vs. Hash Table".

The highest risk component is clearly the median calculation with the Histogram.  I developed tests that create a random sequence of words-per-line, with a known median.  The random sequence is fed into the histogram, then the median is calculated, and then it is verified against the sequence's known median.  The tests can be configured to generate and verify any number of such sequences.  There are actually two of these test routines, one for an odd number of entries, and the other for an even number of entries.

Following is an example of one of the tests, with an even number of entries (i.e. 1,000,000).  The known median is the average of 36 and 42.

	testHistogramEven test 1
	Histogram entries:      1000000
	0       14053
	1       13756
	2       13945
	3       14108
	4       14012
	5       14028
	6       13776
	7       14009
	8       13773
	9       13784
	10      13940
	11      13705
	12      13976
	13      13919
	14      13888
	15      13962
	16      13970
	17      14026
	18      13709
	19      13778
	20      13718
	21      13760
	22      13843
	23      13905
	24      13834
	25      14026
	26      13782
	27      13918
	28      13755
	29      13812
	30      14006
	31      13886
	32      13887
	33      13971
	34      14018
	35      13761
	36      1
	37      0
	38      0
	39      0
	40      0
	41      0
	42      1
	43      70818
	44      71848
	45      71711
	46      71610
	47      71187
	48      71509
	49      71316
	median:                 39.0
	calculatedMedian:       39.0
	Test passed

This sequence was constructed by:

1. Randomly selecting two numbers (e.g. 36 and 42)
1. Inserting 1 entry for each of these two numbers
1. Randomly inserting half the entries below these two numbers
1. Randomly inserting half the entries above these two numbers

## Author ##

Dale Wong






