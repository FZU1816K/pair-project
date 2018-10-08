#pragma once
#include "pch.h"
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Paper.h"
#include <unordered_map>
using namespace std;

class FileIO
{
public:
	static void readFile(vector<Paper> &fileContent, const char *inFilePath, bool showInConsole = false);
	static void writeResult(int charNum, int wordNum, int lineNum, vector<unordered_map<string, int>::iterator> &topPhrase, const char *outFilePath, bool showInConsole = false);
};

