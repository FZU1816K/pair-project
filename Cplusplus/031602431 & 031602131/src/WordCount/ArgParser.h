#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <iostream>
#include <string>

#include "Tools.h"
#include "Status.h"

using namespace std;

class ArgParser{
public:
    ArgParser(int argc, char* argv[], Status* status);
	~ArgParser() {};
private:
    string filename;
	int inPhraseLength, inTopNum, titleWeight, titleAbstract;
	string inputName, outputName;
};

#endif