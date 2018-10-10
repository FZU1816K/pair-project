#include "stdafx.h"
#include "WordFreq.h"
#include"AnalyzeArguments.h"

extern string inputFile;
extern string outputFile;
extern int wordNum;
extern int topN;
extern bool inTitle;
extern bool weightOnWord;
map<string, int> mapWord;
vector < pair<string, int>> vecWord;

bool cmp(pair<string, int> a, pair<string, int> b)
{
	if (a.second != b.second)
		return a.second > b.second;
	return a.first < b.first;
}

bool IsLetter(char ch)
{
	return ch >= 'a' && ch <= 'z';
}

bool IsWord(string word)
{
	if (word.size() >= 4 && IsLetter(word[0]) && IsLetter(word[1]) && IsLetter(word[2]) && IsLetter(word[3]))
		return 1;
	return 0;
}

//count the word frequency of a line
int WordFreq(string s)
{
	string word = "";
	int cnt = 0;
	int len = s.length();
	for (int i = 0; i < len; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] += 32; //change into lower case
		}
		if ((s[i] >= '0'&&s[i] <= '9') || (s[i] >= 'a'&&s[i] <= 'z')) {
			word += s[i];
			if (i == len - 1 && IsWord(word)) {
				if (weightOnWord && inTitle) {
					mapWord[word] += 10;
					cnt++;
				}
				else {
					mapWord[word]++;
					cnt++;
				}		
			}
		}
		else {
			if (IsWord(word)) {
				if (weightOnWord && inTitle) {
					mapWord[word] += 10;
					cnt++;
				}
				else {
					mapWord[word]++;
					cnt++;
				}
			}		
			word = "";
		}
	}

	return cnt;
}

//output the first n words
void TopNWords() 
{
	for (auto x : mapWord) {
		vecWord.push_back(x);
	}
	sort(vecWord.begin(), vecWord.end(), cmp);
	ofstream fout(outputFile, ios::app);
	for (auto x : vecWord) {
		if (!topN) break;
		fout << "<" << x.first << ">: " << x.second << endl;
		topN--;
	}
	fout.close();
}
