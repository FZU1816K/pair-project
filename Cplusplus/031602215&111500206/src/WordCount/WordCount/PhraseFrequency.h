#pragma once
#include"WordFrequency.h"
/*
* Function name: TransitionStorePhrase
* Description:
*	State transition process in DFA(Deterministic Finite Automaton)
*	extract the correct word into a string and try to construct a 
*   'phrase' containing several continuous words.
* Parameter:
*	@state: current state
*	@input: current input
*	@word: when a legal word is detected, it is stored here.
*   @TitleorAbstract: weight frequency mode, see "comm.h"
* Return:
*	@int: new state
*/
int TransitionStorePhrase(int state, char input, string & word, int TitleorAbstract);

/*
* Function name: ConstructPhrase
* Description:
*	 TransitionStorePhrase() will call ConstructPhrase() when get a valid word
*    to try to construct a phrase and return.
* Parameter:
*	@word: valid word
* Return:
*	@string: if a phrase can be formed then return the phrase. Otherwise return "".
*/
string ConstructPhrase(string & word);

/*
* Function name: PhraseFrequency
* Description:
*	Use valid words in a line to form a phrase. Store phrases into a hash table. 
*   This function is a wrapper of Transition, ConstructPhrase and InsertToHashTable.
* Parameter:
*	@line: A single line of a file that need to be counted
*   @TitleorAbstract: weight frequency mode, see "comm.h"
* Return:
*	void
*/
void PhraseFrequency(string line, int TitleorAbstract);
