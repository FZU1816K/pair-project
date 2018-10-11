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
extern bool countPhrase;
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
	int characters = 0;
	int lines = 0;
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
		else if (IsNum(str[0]) || str==""){ //ignore paper number and empty lines
			continue;
		}
		if (countPhrase) {
			PhraseFreq(str);
		}
		characters += CountChar(str);
		words += WordFreq(str);
		lines += CountLines(str);
	}
	fin.close();
	ofstream fout(outputFile);
	fout << "characters: " << characters - 1 << endl;
	fout << "words: " << words << endl;
	fout << "lines: " << lines << endl;
	fout.close();
	if (countPhrase) { //phrase statistics
		TopNPhrases();
	}
	else { //word statistics
		TopNWords(); 
	}
	

	return 0;
}
