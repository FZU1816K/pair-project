#ifndef WORD_PROCESSER_H
#define WORD_PROCESSER_H

#include <string>

#include "LexemeProcesser.h"

using namespace std;

class WordProcesser :
    public LexemeProcesser {
public:
    WordProcesser();
    WordProcesser(Status* stat);

    int processLexeme(string word, string seperator, int whichContext);
    int sendToStatus();

private:
    int checkWordValid(string str);
};

#endif