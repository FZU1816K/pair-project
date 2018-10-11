#ifndef LEXEME_PROCESSER_H
#define LEXEME_PROCESSER_H

#include "Status.h"

class LexemeProcesser{
public:
    LexemeProcesser();
    LexemeProcesser(Status* stat);
    virtual ~LexemeProcesser();

    virtual int processLexeme(string word, string seperator,int whichContext);
    virtual int clearBuffer();
    virtual int sendToStatus();

protected:
    Status* status;
    int wordTotalNum;
    int inWhichContext;

};

#endif // !LEXEME_PROCESSER_H