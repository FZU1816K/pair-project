#include "CountWords.h"
#include "pch.h"
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<string, int> wordFrequency;

bool inTitle = false;
bool inAbstract = false;
int titleWeight = 1;
int cnt = 0;

void WordClassify(string word)
{
	if (wordFrequency.count(word) == 0)
	{
		if (inTitle)
		{
			cnt += 1;
			wordFrequency[word] = titleWeight;
		}
		else
		{
			wordFrequency[word] = 1;
		}

	}
	else
	{
		if (inTitle)
		{
			wordFrequency[word] += titleWeight;
		}
		else
		{
			wordFrequency[word] += 1;
		}

	}

}

void stringCut(string inStr)
{
	int slen = inStr.length();
	bool is_head = true;//at the beginning of a word
	bool not_a_word = false;
	string word;
	for (int i = 0; i < slen; i++)  //todo:avoid digit-first-word
	{
		if (!(inStr[i] >= 1 && inStr[i] <= 255))
		{
			continue;
		}
		if ((inStr[i] <= '9') && (inStr[i]) >= '0') // deal with digit
		{
			if (is_head)
			{
				not_a_word = true;
				continue;
			}
			else
			{
				word += inStr[i];
			}
		}
		if ((inStr[i] >= 'a') && (inStr[i] <= 'z') || (inStr[i] >= 'A') && (inStr[i] <= 'Z'))
		{
			if (!not_a_word)
			{
				is_head = false;
				word += tolower(inStr[i]);
			}
		}
		if (inStr[i] == ' ')
		{
			not_a_word = false;
			if (word.length() >= 4)
			{
				//cnt++;
				cout << word << endl;
				WordClassify(word);
			}
			word = "";
			continue;
		}


		if (ispunct(inStr[i]))//deal with punctions (i.e ',')
		{
			not_a_word = false;
			if (word.length() >= 4)
			{
				//cnt++;
				cout << word << endl;
				WordClassify(word);
			}
			word = "";
			continue;
		}
		if (i == slen - 1)
		{
			cout << word << endl;
			if (word.length() >= 4)
			{
				//cnt++;
				WordClassify(word);
			}
		}

	}
}
int CountWord(string inputFilename, bool weightOn)
{
	fstream input;
	input.open(inputFilename);
	
	if (weightOn)
	{
		titleWeight = 10;
	}
	
	string oneLine;

	while (getline(input, oneLine))
	{
		if (oneLine[0] >= '0'&& oneLine[0] <= '9')
			continue;
		if (oneLine.substr(0, 7) == "Title: ")
		{
			
			oneLine = oneLine.substr(7, oneLine.length());
			stringCut(oneLine);
		}

		else if (oneLine.substr(0, 10) == "Abstract: ")
		{
			oneLine = oneLine.substr(10, oneLine.length());
			stringCut(oneLine);
		}
	}
	cout << wordFrequency["hello"] << endl;
	return 0;
}

