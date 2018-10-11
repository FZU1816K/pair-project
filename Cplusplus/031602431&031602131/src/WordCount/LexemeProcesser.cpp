#include "LexemeProcesser.h"

LexemeProcesser::LexemeProcesser() :status(NULL), wordTotalNum(0),
                 inWhichContext(Status::FORMAT_CONTENT) {

}

LexemeProcesser::LexemeProcesser(Status * stat)
    : status(stat), wordTotalNum(0), inWhichContext(Status::FORMAT_CONTENT) {

}


LexemeProcesser::~LexemeProcesser()
{
}

int LexemeProcesser::processLexeme(string word, string seperator, int whichContext)
{
    return 0;
}

int LexemeProcesser::clearBuffer()
{
    return 0;
}

int LexemeProcesser::sendToStatus()
{
    return 0;
}

