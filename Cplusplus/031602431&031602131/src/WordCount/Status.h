#ifndef STATUS_H
#define STATUS_H

#include <map>
#include <string>

using namespace std;

struct StoreMap {
    map<string, int>* strMap;
};


class Status
{
public:
    Status();
    ~Status();

    int setIdentifyCode(int code);
    int setIOFile(string input, string output = "result.txt");
    int setPharse(int inPhraseLength);
    int setWeight(int inWeightTitle, int inWeightAbstract = 1);
    int setTopNum(int inTopNum = 10);

    int identifyCode;
    string inputFilePath, outputFilePath;
    int weightTitle, weightAbstract;
    int phraseLength;
    int topNum;
    StoreMap storeMap;

    int charNum;
    int wordTotalNum;
    int lineNum;

    static const int TITLE_CONTENT = 2;
    static const int ABSTRACT_CONTENT = 1;
    static const int FORMAT_CONTENT = 0;

};

#endif