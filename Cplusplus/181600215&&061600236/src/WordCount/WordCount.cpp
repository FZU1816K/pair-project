#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include "AnalyzeArguments.h"
#include "CountChar.h"
#include "CountLines.h"
#include "WordFreq.h"
#include "PhraseFreq.h"
using namespace std;

extern string inputFile;
extern string outputFile;
extern int phraseLen;
extern int topN;
extern bool weightOnWord;
extern bool _m;
bool inTitle;

bool IsNum(char ch)
{
	return ch >= '0' && ch <= '9';

}

bool IsEmptyLine(string s) {
	int len = s.size();
	for (int i = 0; i < len; i++) {
		if (s[i] >= 32)
			return 0;
	}
	return 1;
}

int main(int argc, char **argv)
{
	int x = AnalyseParameter(argv);
	if (x == 0)
		return 0;
	ifstream fin(inputFile);
	int characters = CountChar(inputFile);
	int lines = CountLines(inputFile);
	int words = 0;
	string str;
	while (getline(fin, str)) {
		inTitle = 0;
		if (str.substr(0, 7) == "Title: ") {
			str = str.substr(7, str.length());
			inTitle = 1;
		}
		else if (str.substr(0, 10) == "Abstract: ") {
			str = str.substr(10, str.length());
		}
		else if (IsNum(str[0]) || IsEmptyLine(str)){
			continue;
		}
		if (_m) {
			PhraseFreq(str);
		}
		words += WordFreq(str);
				
	}
	fin.close();
	cout << "characters: " << characters << endl;
	cout << "words: " << words << endl;
	cout << "lines: " << lines << endl;
	if (_m) {
		TopNPhrases();
	}
	else {
		TopNWords(); 
	}
	

	return 0;
}
