#ifndef LEXEME_PARSER_H
#define LEXEME_PARSER_H

#include <map>
#include <string>

#include "Status.h"
#include "LexemeProcesser.h"

using namespace std;

class LexemeProcesser;

// This class process every character using processStr(char c)
class LexemeParser{
public:
    LexemeParser(Status* stat, LexemeProcesser* lexProcesser);

    int processStr(string str, int whichContext);
    int sendToStatus();


private:
    int charNum;
    int lineNum;
    int inWord;// IN = 1, OUT = 0
    int newLine;// OLD = 1, NEW = 0;
    
    string nowWord;
    string nowSeperator;
    const int SPACE = ' ';
    const int LINESYM = '\n';
    const int TAB = '\t';
    const int LINKWORDSYM = '-';

    LexemeProcesser* lexProcesser;
    Status * status;
};


#endif