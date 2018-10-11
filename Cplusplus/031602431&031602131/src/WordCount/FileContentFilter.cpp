#define _CRT_SECURE_NO_WARNINGS 

#include <cstdio>
#include <string>
#include <queue>

#include "FileContentFilter.h"
#include "LexemeParser.h"
#include "FileContentFilter.h"

using namespace std;

FileContentFilter::FileContentFilter()
    :status(NULL), file(NULL), processer(NULL),
    contStart(0), contEnd(0), fileContent(string()) {

    for (int i = 0; i < 2; i++) {
        statusOfDFA[i] = 0;
    }
}

FileContentFilter::FileContentFilter(Status* stat, LexemeParser* lexemePareser)
    :status(stat), processer(lexemePareser), contStart(0), contEnd(0), fileContent(string()) {
 
    statusOfDFA[0] = 1;
    statusOfDFA[1] = 13;
    statusOfDFA[2] = 1;


    file = fopen((status->inputFilePath).c_str(), "r");
    if (file == NULL) {
        perror("File error");
    }
    else {
        ;
    }

}

FileContentFilter::~FileContentFilter() {
    if (file != nullptr) {
        fclose(file);
    }
}

int FileContentFilter::scan() {
    char peekChar;
    while ((peekChar = fgetc(file)) != EOF) {

        if (statusOfDFA[0] == -1) {// cannot find the first "Title: "
            return -1;
        }
        else if (statusOfDFA[0] != 10) { // find the first "Title: "
            int ans = dfaOfFirstTitle(peekChar);
            if (ans == -1) {
                printf("The file format is error\n");
            }
        }
        else if (statusOfDFA[1] != 13) {//find "\n\n\n[0-9]+\nTitle"
            fileContent.append(1, peekChar);
            dfaOfTitle(peekChar);
            if (statusOfDFA[1] == 13) {
                int index = fileContent.length() - 12;
                for (; index >= 0; index--) {
                    if (fileContent[index] == '\n')
                        break;
                }

                fileContent = fileContent.substr(0, index + 1);
                processer->processStr(fileContent, Status::ABSTRACT_CONTENT);
                fileContent.clear();
            }
        }
        else {
            fileContent.append(1, peekChar);
            dfaOfAbstract(peekChar);
            if (statusOfDFA[2] == 12) {
                fileContent = fileContent.substr(0, (fileContent.length() - 10));
                processer->processStr(fileContent, Status::TITLE_CONTENT);
                fileContent.clear();

                statusOfDFA[1] = 1;
                statusOfDFA[2] = 1;
            }
        }
    }
    if (peekChar == EOF) {
        processer->processStr(fileContent, Status::ABSTRACT_CONTENT);
        fileContent.clear();
    }

    //processer->setWordNumByMap();
    return 0;
}

int FileContentFilter::dfaOfFirstTitle(char c) {
    if (statusOfDFA[0] == 1)
    {
        if (isdigit(c)) {
            statusOfDFA[0] = 2;
        }
        else {
            statusOfDFA[0] = -1;
            return -1;
        }
    }
    else if (statusOfDFA[0] == 2) {
        // try to find '\n'
        if (isdigit(c)) {
            ;
        }
        else {
            if (c == '\n') {
                statusOfDFA[0] = 3;
            }
            else {
                statusOfDFA[0] = -1;
                return -1;
            }
        }
    }
    else if ((statusOfDFA[0] >= 3) && (statusOfDFA[0] <= 8)) {
        // 3-9 try to match "Title: "
        if (c == "Title:"[statusOfDFA[0] - 3]) {
            statusOfDFA[0] ++;
        }
        else {
            statusOfDFA[0] = -1;
            return -1;
        }
    }
    else if (statusOfDFA[0] == 9) {
        if (c == ' ') {
            statusOfDFA[0] = 10;// Founded
            return 1;
        }
    }
    return 0;
}

int FileContentFilter::dfaOfTitle(char c) {
    if (statusOfDFA[1] == 1) {
        if (c == '\n') {
            statusOfDFA[1] = 2;
        }
    }
    else if (statusOfDFA[1] == 2) {
        if (c == '\n') {
            statusOfDFA[1] = 3;
        }
    }
    else if (statusOfDFA[1] == 3) {
        if (c == '\n') {
            statusOfDFA[1] = 4;
        }
    }
    else if (statusOfDFA[1] == 4)
    {
        // to find a digit
        if (isdigit(c)) {
            statusOfDFA[1] = 5;
        }
        else {
            if (c == '\n')
                statusOfDFA[1] = 4;
            else
                statusOfDFA[1] = 1;
        }
    }
    else if (statusOfDFA[1] == 5) {
        // find digits
        if (isdigit(c)) {
            ;
        }
        else {
            if (c == '\n') {
                statusOfDFA[1] = 6;
            }
            else {
                statusOfDFA[1] = 1;
            }
        }
    }
    else if ((statusOfDFA[1] >= 6) && (statusOfDFA[1] <= 11)) {
        // 6-11 try to match "Title: "
        if (c == "Title:"[statusOfDFA[1] - 6]) {
            statusOfDFA[1] ++;
        }
        else if (c == '\n') {
            statusOfDFA[1] = 2;
        }
        else
            statusOfDFA[1] = 1;
    }
    else if (statusOfDFA[1] == 12) {
        if (c == ' ') {
            statusOfDFA[1] = 13;// Founded
            return 1;
        }
        else if (c == '\n') {
            statusOfDFA[1] = 2;
        }
        else
            statusOfDFA[1] = 1;
    }
    return 0;
}

int FileContentFilter::dfaOfAbstract(char c) {
    if (statusOfDFA[2] == 1) {
        if (c == '\n') {
            statusOfDFA[2] = 2;
        }
    }
    else if ((statusOfDFA[2] >= 2) && (statusOfDFA[2] <= 10)) {
        // 6-11 try to match "Abstract:"
        if (c == "Abstract:"[statusOfDFA[2] - 2]) {
            statusOfDFA[2] ++;
        }
        else if (c == '\n') {
            statusOfDFA[2] = 2;
        }
        else
            statusOfDFA[2] = 1;
    }
    else if (statusOfDFA[2] == 11) {
        if (c == ' ') {
            statusOfDFA[2] = 12;// Founded
            return 1;
        }
    }
    return 0;
}
