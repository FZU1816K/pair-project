#include<iostream>
#include<fstream>
#include<sstream>
#include"ArgumentParser.h"
#include"CountChar.h"
#include"CountLines.h"
#include"CountWords.h"
#include"WordFrequency.h"
#include"comm.h"
#include"PhraseFrequency.h"

using namespace std;

extern std::string inputFileName;
extern std::string outputFileName;
extern int weightFrequencyOn;
extern int phraseFrequencyOn;
extern int phraseLength;
extern int topNWords;

int main(int argc, char **argv)
{
	int ret = Parse_Args(argc, argv);
	if (ret == -1) {
		return -1;
	}

	fstream file;
	file.open(inputFileName.c_str(), ios::in || ios::binary);
	string line;
	
	int numChar = 0;
	int numWords = 0;
	int numLines = 0;

	while (getline(file, line))
	{
		if (line == "") // skip empty line
		{
			//cout << "empty line!" << endl;
			continue;
		}
		else if (stringIsNum(line)) // skip the line indicates the sequence number.
		{
			//cout << "number line!" << line << endl;
			continue;
		}
		else if (line.find("Title: ") != string::npos) { // Title line
			line = line.substr(7); // "Title: " shoule not included when counting.

			numChar += CountChar(line);
			numLines++;	
			numWords += CountWords(line); 

			if (phraseFrequencyOn == 0) { // count words frequency
				if (weightFrequencyOn == 1) // weight frequency mode or not
					WordFrequency(line, TITLE);
				else if (weightFrequencyOn == 0)
					WordFrequency(line, NONWEIGHT);
			}
			else { // if (phraseFrequencyOn == 1)  // count phrase frequency
				if (weightFrequencyOn == 1) // weight frequency mode or not
					PhraseFrequency(line, TITLE);
				else if (weightFrequencyOn == 0)
					PhraseFrequency(line, NONWEIGHT);
			}
		}
		else if (line.find("Abstract: ") != string::npos) { // Abstract line
			line = line.substr(10);// "Abstract: " shoule not included when counting.

			numChar += CountChar(line);
			numLines++;
			numWords += CountWords(line);

			if (phraseFrequencyOn == 0) {
				if (weightFrequencyOn == 1) 
					WordFrequency(line, ABSTRACT);
				else if (weightFrequencyOn == 0)
					WordFrequency(line, NONWEIGHT);
			}
			else {
				if (weightFrequencyOn == 1) 
					PhraseFrequency(line, ABSTRACT);
				else if (weightFrequencyOn == 0)
					PhraseFrequency(line, NONWEIGHT);
			}
		}
	}
	auto wordsFrequencyList = TopWords();
	
	OutputToFile(numChar, numWords, numLines);
	OutputToFile(wordsFrequencyList);
	OutputToFile(argc, argv);
	return 0;
}