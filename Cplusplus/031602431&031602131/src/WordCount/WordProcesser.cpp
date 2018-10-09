#include "WordProcesser.h"

WordProcesser::WordProcesser()
    :LexemeProcesser() {

}

WordProcesser::WordProcesser(Status* stat)
    : LexemeProcesser(stat) {

    if (status == NULL) {
        printf("Error: The status is NULL!\n");
        throw invalid_argument("The status is NULL");
    }
}

int WordProcesser::processLexeme(string word, string seperator, int whichContext) {
    if (inWhichContext != whichContext) {
        this->clearBuffer();
        inWhichContext = whichContext;
    }

    if (!(word.empty()))
        if (checkWordValid(word)) {
            int addNum = 0;
            if (whichContext == Status::TITLE_CONTENT) {
                addNum = status->weightTitle;
            }
            else if (whichContext == Status::ABSTRACT_CONTENT) {
                addNum = status->weightAbstract;
            }
            (*((status->storeMap).strMap))[word] += addNum;
            wordTotalNum++;
        }
        else;
    else;

    return 0;
}

int WordProcesser::sendToStatus() {
    status->wordTotalNum = wordTotalNum;
    return 0;
}

int WordProcesser::checkWordValid(string str) {
    unsigned int preCharCounts = 0;
    while (preCharCounts < str.length() && isalpha(str[preCharCounts]))
        preCharCounts++;
    if (preCharCounts >= 4)
        return 1;//True
    else {
        return 0;//False
    }
}
