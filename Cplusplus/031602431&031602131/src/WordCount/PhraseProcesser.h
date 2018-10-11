#ifndef PHRASE_PROCESSER_H
#define PHRASE_PROCESSER_H

#include "LexemeProcesser.h"

class PhraseProcesser : public LexemeProcesser{
public:
    PhraseProcesser();
    PhraseProcesser(Status* stat);
    ~PhraseProcesser();

    int processLexeme(string word, string seperator, int whichContext);
    int clearBuffer();
    int sendToStatus();

private:
    int wordOfPhraseCount;
    string* words;
    string* seperators;
    int wordsHead;

    int checkWordValid(string str);

    int phraseLength;


};

#endif
