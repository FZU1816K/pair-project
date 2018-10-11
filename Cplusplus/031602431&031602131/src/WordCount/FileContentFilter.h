#define _CRT_SECURE_NO_WARNINGS 

#ifndef FILECONTENTFILTER_H
#define FILECONTENTFILTER_H

#include <string>

#include "LexemeParser.h"
#include "Status.h"

using namespace std;



// This class will open the file and convert every character to LexemeParser
class FileContentFilter {
public:
    FileContentFilter();
    FileContentFilter(Status* status, LexemeParser* lexemePareser);
    ~FileContentFilter();
    int scan();


public:

    int statusOfDFA[3];
    int dfaOfFirstTitle(char c);
    int dfaOfTitle(char c);
    int dfaOfAbstract(char c);

private:
    Status* status;
    FILE* file;
    LexemeParser* processer;
    int contStart;
    int contEnd;
    string fileContent;
};

#endif