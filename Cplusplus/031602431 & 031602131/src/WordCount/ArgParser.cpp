#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <cstdio>
#include <iostream>

#include "argParser.h"
#include "Tools.h"

using namespace std;


ArgParser::ArgParser(int argc, char * argv[], Status* status)
    :inPhraseLength(1), inTopNum(10), abstractWeight(1),titleWeight(1),
     inputName(string()), outputName(string()){

    int code = 0x00;
	int i = 1;
	while (i < argc) {
		if (i % 2 == 1) {
			if (strcmp(argv[i], "-i") == 0) {
				inputName = argv[i + 1];
                code = code | 0x01;
			}

			else if (strcmp(argv[i], "-o") == 0) {
				outputName = argv[i + 1];
                code = code | 0x02;
			}
			else if (strcmp(argv[i], "-w") == 0) {
				if (strcmp(argv[i+1], "0") == 0) {
					titleWeight = 1;
				}
				else if (strcmp(argv[i + 1], "1") == 0) {
					titleWeight = 10;
                    code = code | 0x04;
				}
			}
			else if (strcmp(argv[i], "-m") == 0) {
				inPhraseLength = atoi(argv[i + 1]);
                code = code | 0x08;
			}
			else if (strcmp(argv[i], "-n") == 0) {
				inTopNum = atoi(argv[i + 1]);
                code = code | 0x10;
			}
            else if (strcmp(argv[i], "-g") == 0) {
                code = code | 0x20;
            }
		}
		i= i+ 2;
	}

    status->setIdentifyCode(code);
    if (outputName.empty())
        status->setIOFile(inputName);
    else
        status->setIOFile(inputName, outputName);

    status->setPharse(inPhraseLength);
    status->setTopNum(inTopNum);
    status->setWeight(titleWeight, abstractWeight);
}
