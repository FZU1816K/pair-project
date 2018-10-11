#include "Status.h"

Status::Status()
    :identifyCode(0x00), inputFilePath(string()), outputFilePath("result.txt"),
    weightTitle(1), weightAbstract(1),
    phraseLength(1), topNum(10),
    charNum(0), wordTotalNum(0), lineNum(0) {

    storeMap = struct StoreMap();
    storeMap.strMap = new map<string, int>();
}

Status::~Status() {
    delete storeMap.strMap;
}

// set the code by OR these constants
//none: 0x00, "-i": 0x01, "-o": 0x02, "-w": 0x04, "-m": 0x08, "-n": 0x10, "-g": 0x20
int Status::setIdentifyCode(int code)
{
    if ((code <= 0xff) && (code >= 0x00))
        identifyCode = code;
    return 0;
}


int Status::setIOFile(string input, string output)
{
    inputFilePath = input;
    outputFilePath = output;
    return 0;
}

int Status::setPharse(int inPhraseLength)
{
    phraseLength = inPhraseLength;
    return 0;
}

int Status::setWeight(int inWeightTitle, int inWeightAbstract)
{
    weightTitle = inWeightTitle;
    weightAbstract = inWeightAbstract;
    return 0;
}

int Status::setTopNum(int inTopNum)
{
    topNum = inTopNum;
    return 0;
}
