#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <cstdio>
#include <string>
#include <queue>

#include "LexemeParser.h"

using namespace std;

const int IN = 1;
const int OUT = 0;
const int NEW = 0;
const int OLD = 1;

LexemeParser::LexemeParser(Status * stat, LexemeProcesser * lexProcess)
    :charNum(0), lineNum(0), inWord(0), newLine(0),
    nowWord(string()), nowSeperator(string()) {

    status = stat;
    lexProcesser = lexProcess;
}

int LexemeParser::processStr(string str, int whichContext) {

    for (unsigned int i = 0; i < str.length(); i++) {
        char c = str[i];

        if (isascii(c))
            charNum++;
        else {
            c = TAB;
        }

        if (c == LINESYM) {
            if (newLine == OLD) {
                newLine = NEW;
                lineNum++;
            }
        }
        else {
            if (newLine == NEW) {
                if (!(c == SPACE || c == TAB))
                    newLine = OLD;
            }
        }

        if (!(isalnum(c))) {
            if (inWord == IN) {
                lexProcesser->processLexeme(nowWord, nowSeperator, whichContext);
                inWord = OUT;
                nowWord.clear();
                nowSeperator.clear();
            }
            else;
            if (c != '\n') {
                nowSeperator.append(1, c);
            }
            else {
                lexProcesser->clearBuffer();
                nowSeperator.clear();
            }
        }
        else if (isalnum(c)) {
            if (isalpha(c))
                c = tolower(c);
            if (inWord == IN);
            else {
                inWord = IN;
            }
            nowWord.append(1, c);
        }
        else;
    }

    // end of str
    if (newLine == OLD)
        lineNum++;
    if (inWord == IN) {
        lexProcesser->processLexeme(nowWord, nowSeperator, whichContext);
        inWord = OUT;
        nowWord.clear();
        nowSeperator.clear();
    }

    return 0;
}

int LexemeParser::sendToStatus()
{
    status->lineNum = lineNum;
    status->charNum = charNum;
    return 0;
}
