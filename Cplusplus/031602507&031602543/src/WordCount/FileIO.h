#pragma once
#include<iostream>
#include<stdio.h>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

class FileIO
{
public:
	static bool readFile(const char* inputFileName,string &charBuf,vector<string> &linesBuf);
	static bool outputToFile(int characterCount, int lineCount, int wordCount, const char* outputFileName, vector<map<string,int>::iterator> &topX);

private:
};