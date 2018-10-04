#pragma once
#include <string>

// command line arguments settings:
std::string inputFileName = "result.txt";
std::string outputFileName = "output.txt";
int weightFrequencyOn = 0;
int phraseFrequencyOn = 0; 
int phraseLength = 0;
int topNWords = 10;


/*
external variables usage      |    corresponding command line arguments  
------------------------------|-------------------------------------------
extern string inputFileName;  | -i <input.txt> : define input file name.
extern string outputFileName; | -o <result.txt>: define output file name.
extern int weightFrequencyOn; | -w [0|1] : 1 to turn on weight frequency mode. See macros below.
extern int phraseFrequencyOn; | -m <number> : count frequency of phrases(instead of words) with the length of <number> words.
extern int phraseLength;      | if -m is used, <number> stored in here.
extern int topNWords;		  | -n <number> : count top <number> words/phrase. 

*/

/* when the weight frequency mode is on, words/phrases in title line count 10 when counting 
their frequency and only count 1 if they are in abstract line.

See InsertToHashTable()*/
#define TITLE 1		 
#define ABSTRACT 2

// if the weight frequency mode is off, do as usual.
#define NONWEIGHT 3