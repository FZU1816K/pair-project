#include <ctype.h>
#include <string>

#include "PhraseProcesser.h"

using namespace std;

PhraseProcesser::PhraseProcesser()
    :LexemeProcesser(), wordOfPhraseCount(0),
    words(NULL), seperators(NULL), wordsHead(0), phraseLength(0) {
}

PhraseProcesser::PhraseProcesser(Status * stat)
    : LexemeProcesser(stat), wordOfPhraseCount(0), wordsHead(0) {

    if (status == NULL) {
        printf("Error: The status is NULL!\n");
        throw invalid_argument("The status is NULL");
    }

    phraseLength = status->phraseLength;

    words = new string[phraseLength];
    seperators = new string[phraseLength];
}


PhraseProcesser::~PhraseProcesser() {
    delete[] words;
    delete[] seperators;
}

int PhraseProcesser::processLexeme(string word, string seperator, int whichContext) {
    if (inWhichContext != whichContext) {
        this->clearBuffer();
        inWhichContext = whichContext;
    }

    if (checkWordValid(word)) {
        wordTotalNum++;

        words[wordsHead] = word;
        seperators[wordsHead] = seperator;
        wordOfPhraseCount++;
        wordsHead = (wordsHead + 1) % phraseLength;

        if (wordOfPhraseCount == phraseLength) {
            string phrase;

            phrase.append(words[wordsHead]);
            for (int i = 0; i < phraseLength - 1; i++) {
                phrase.append(seperators[(wordsHead + 1 + i) % phraseLength]);
                phrase.append(words[(wordsHead + 1 + i) % phraseLength]);
            }
            wordOfPhraseCount--;

            int addNum = 0;
            if (whichContext == Status::TITLE_CONTENT) {
                addNum = status->weightTitle;
            }
            else if (whichContext == Status::ABSTRACT_CONTENT) {
                addNum = status->weightAbstract;
            }


            (*((status->storeMap).strMap))[phrase] += addNum;

        }
    }
    else {
        clearBuffer();
    }

    return 0;
}

int PhraseProcesser::clearBuffer() {

    for (int i = 0; i < phraseLength; i++) {
        words[i].clear();
        seperators[i].clear();
    }

    wordOfPhraseCount = 0;
    wordsHead = 0;

    return 0;
}

int PhraseProcesser::checkWordValid(string str) {
    unsigned int preCharCounts = 0;
    while (preCharCounts < str.length() && isalpha(str[preCharCounts]))
        preCharCounts++;
    if (preCharCounts >= 4)
        return 1;//True
    else {
        return 0;//False
    }
}


int PhraseProcesser::sendToStatus() {
    status->wordTotalNum = wordTotalNum;
    return 0;
}