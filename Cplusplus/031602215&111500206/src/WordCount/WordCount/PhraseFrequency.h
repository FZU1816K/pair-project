#pragma once
#include"WordFrequency.h"

int TransitionStorePhrase(int state, char input, string & word, int TitleorAbstract);
string ConstructPhrase(string & word);
void PhraseFrequency(string line, int TitleorAbstract);