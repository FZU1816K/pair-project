#include "stdafx.h"
#include<iostream>
#include<fstream>
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

int main()
{
	ifstream fin(inputFile);
	int characters = CountChar(inputFile);
	int lines = CountLines(inputFile);
	int words = 0;
	string str;
	while (getline(fin, str)) {
		if (str.substr(0, 7) == "Title: ") {
			str = str.substr(7, str.length());
		}
		if (str.substr(0, 10) == "Abstract: ") {
			str = str.substr(10, str.length());
		}
		words += WordFreq(str);
		PhraseFreq(str);
	}
	fin.close();
	cout << "characters: " << characters << endl;
	cout << "words: " << words << endl;
	cout << "lines: " << lines << endl;
	TopNWords();
	TopNPhrases();

	return 0;
}
