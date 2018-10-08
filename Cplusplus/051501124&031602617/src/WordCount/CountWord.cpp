// stringCut with length:Done in 10/1 afternoon
// TODO: add shift-window for phrase
#include "CountWords.h"
#include "pch.h"
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;



unordered_map<string, int> wordFrequency;
vector<pair<string, int>> wordRank;

extern int phraseLen;
extern int topN;

bool inTitle = false;
bool inAbstract = false;
int titleWeight = 1;
int cnt = 0;

void showResult()
{
	int cnt = 0;
	for (auto iter = wordFrequency.begin(); iter != wordFrequency.end(); iter++)
	{
		cnt++;
		cout << iter->first << " : " << iter->second << endl;
	}
	//cout << cnt << endl;
}

bool mysort(const pair<string, int> &left, const pair<string, int> &right)
{
	if (left.second != right.second)
	{
		return left.second > right.second;
	}
	else
	{
		return left.first < right.first;
	}
}

void topNword(int n)
{
	for (auto iter = wordFrequency.begin(); iter != wordFrequency.end(); iter++) // iterate all words in WordFrequency
	{
		pair<string, int> word = make_pair(iter->first, iter->second);
		wordRank.push_back(word);
		
	}
	sort(wordRank.begin(),wordRank.end(),mysort);
	auto iter = wordRank.begin();
	//avoid topN > wordRankSize
	if (n > wordRank.size())
	{
		n = wordRank.size();
	}

	//
	for (int i = 0; i < n; iter++,i++)
	{
		cout << iter->first << ":" << iter->second << endl;
	}
}

void WordClassify(string word)
{
	int len = word.length();
	for (int i = 0; i < len; i++)
	{
		if (word[i]<='Z'&&word[i]>='A')
		{
			word[i] += 32;
		}
	}

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
			// 9/30
			is_head = true;
			if (word.length() >= 4)
			{
				//cnt++;
				//cout << word << endl;
				WordClassify(word);
			}
			word = "";
			continue;
		}


		if (ispunct(inStr[i]))//deal with punctions (i.e ',')
		{
			not_a_word = false;
			// 9/30
			is_head = true;
			if (word.length() >= 4)
			{
				//cnt++;
				//cout << word << endl;
				WordClassify(word);
			}
			word = "";
			continue;
		}
		if (i == slen - 1)
		{
			//cout << word << endl;
			// 9/30
			is_head = true;
			if (word.length() >= 4)
			{
				//cnt++;
				WordClassify(word);
			}
		}

	}

}

// 9/30
void stringCutWithLen(string inStr,int phraseLen)
{
	int phraseHead = 0;
	int secondWordHead = 0;
	int phraseLenCnt = 0;
	string phrase = "";
	
	
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

		else if ((inStr[i] <= '9') && (inStr[i]) >= '0') // deal with digit
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

		else if ((inStr[i] >= 'a') && (inStr[i] <= 'z') || (inStr[i] >= 'A') && (inStr[i] <= 'Z'))
		{
			if (!not_a_word)
			{
				if (is_head)
				{
					phraseLenCnt++;  
					if (phraseLenCnt == 1) //词组首词
					{
						phraseHead = i;
					}
					if (phraseLenCnt == 2)
					{
						secondWordHead = i;
					}
				}
				is_head = false;
				word += tolower(inStr[i]);
			}
		}

		else if (inStr[i] == ' ')
		{
			not_a_word = false;
			// 9/30
			is_head = true;
			if (word.length() >= 4)
			{
				if (phraseLenCnt == phraseLen)
				{
					phrase = inStr.substr(phraseHead, i - phraseHead );
					//cout << phrase << endl;
					WordClassify(phrase);
					/*phraseHead = i;
					phraseLenCnt = 0;     10/1 noon right        */
					phraseHead = secondWordHead;
					phraseLenCnt -= 1;
				}
				else
				{

				}
			}
			else
			{
				phraseHead = i;  //清空待传词组
				phraseLenCnt = 0;
			}
			word = "";
			continue;
		}


		else if (ispunct(inStr[i]))//deal with punctions (i.e ',')
		{
			not_a_word = false;
			// 9/30
			is_head = true;
			if (word.length() >= 4)
			{
				//cout << word << endl;
				if (phraseLenCnt == phraseLen)
				{
					phrase = inStr.substr(phraseHead, i - phraseHead );
					//cout << phrase << endl;
					WordClassify(phrase);
					/*phraseHead = i;
					phraseLenCnt = 0;   10/1 noon right*/
					phraseHead = secondWordHead;
					phraseLenCnt -= 1;

				}
				else
				{
					;
				}
				
			}
			else
			{
				phraseHead = i+1; // 10/1 fix
				phraseLenCnt = 0;
			}
			word = "";
			continue;
		}


		if (i == slen - 1)
		{
			//cout << word << endl;
			// 9/30
			is_head = true;
			if (word.length() >= 4)
			{
				
				if (phraseLenCnt == phraseLen)
				{
					phrase = inStr.substr(phraseHead, i - phraseHead );
					//cout << phrase << endl;
					WordClassify(phrase);
					phraseHead = i;
				}
				else
				{
					
				}
			}
			phraseHead = i;
			phraseLenCnt -= 1;
			
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
			inTitle = true;
			oneLine = oneLine.substr(7, oneLine.length());
			//stringCut(oneLine);
			stringCutWithLen(oneLine,phraseLen);
			inTitle = false;
		}

		else if (oneLine.substr(0, 10) == "Abstract: ")
		{
			oneLine = oneLine.substr(10, oneLine.length());
			//stringCut(oneLine);
			stringCutWithLen(oneLine,phraseLen);
		}
	}
	//showResult();
	topNword(topN);
	//cout << wordFrequency["hello"] << endl;
	return 0;
}


