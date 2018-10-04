#pragma once
#include<iostream>
#include<queue>
#include<unordered_map>
#include<fstream>
#include<string>

using namespace std;

#define Separator(x) (isspace(x) || (!IsNum(x) && !isalpha(x))) 
#define IsNum(x) (x >= '0' && x <= '9')

#define OUTWORD 0 // 6 DFA states
#define P1 1
#define P2 2
#define P3 3
#define NotAWord 4 
#define VALIDWORD 5
#define ERRORSTATE 6


#define TITLE 1
#define ABSTRACT 2
#define NONWEIGHT 3

/* 
* Function name: MySort
* Description:
*	Sort method of Top 10 words vector.
*/
bool MySort(const pair<int, string>& word1, const pair<int, string>& word2);

/*
* Function name: TransitionStoreWord
* Description: 
*	State transition process in DFA(Deterministic Finite Automaton)
*	and extract the correct word into a string
* Parameter:
*	@state: current state
*	@input: current input
*	@word: when a legal word is detected, it is stored here.
*   @TitleorAbstract: weight frequency mode, see "comm.h"
* Return:
*	@int: new state
*/
int TransitionStoreWord(int state, char input, string & word, int TitleorAbstract);

/*
* Function name: InsertToHashTable
* Description: 
*	Insert legal words into the hash table. Be called in the
*	Transition() function
* Parameter:
*	@word: the legal word / or phrase
*   @TitleorAbstract: weight frequency mode, see "comm.h"
* Return:
*	void
*/
void InsertToHashTable(string & word, int TitleorAbstract);

/*
* Function name: WordFrequency
* Description: 
*	Count the number of occurrences of each word in a line, stored into
*	a hash table. This function is a wrapper of Transition and InsertToHashTable
* Parameter:
*	@line: A single line of a file that need to be counted
*   @TitleorAbstract: weight frequency mode, see "comm.h"
* Return:
*	void
*/
void WordFrequency(string line, int TitleorAbstract);

/*
* Function name: TopWords
* Description:
*	Construct top N words/phrases vector with the highest frequency. 
*   N is assigned by commandline argument.
* Parameter:
*	none
* Return:
*	vector<pair<int, string>> & : List of top N words/phrases with their counter.
*/
vector<pair<int, string>> TopWords();

/*
* Function name: OutputToFile
* Description:
*	Output the statistics or top words to file, to standard output in a regular format.
*   or display commandline arguments for debug.
* Parameter:
*	@TopWords: Top words list
*	@numChar, numWords, numLines: statistics
*   @argc, argv: commandline arguments
* Return:
*	int: 0 if output correctly, -1 otherwise.
*/
int OutputToFile(vector<pair<int, string>> & TopWords);
int OutputToFile(int numChar, int numWords, int numLines);
int OutputToFile(int argc, char **argv);