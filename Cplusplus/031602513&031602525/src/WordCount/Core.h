#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <vector>
using namespace std;
class Core {
public:
	Core(string InputNameTemp, string OutputNameTemp, string WeightTemp, int mNumTemp, int nNumTemp);
	~Core();

	ifstream infile;
	string InputName, OutputName, Weight;
	int characters, words, lines, mNum, nNum;
	bool useWordGroup, useCustomOutput;
	int getCrt();
	int getWords();
	int getLines();
	vector <pair<string, int>> getVector();

private:
	bool hasRunKernel;
	unordered_map<string, int> strMap;
	unordered_map<string, int>::iterator it;
	vector <pair<string, int>> vtMap;

	void kernelFunction();
	void sort();
};