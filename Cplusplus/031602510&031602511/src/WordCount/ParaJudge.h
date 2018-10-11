#pragma once
#include <string>

using namespace std;

class ParaJudge
{
public:
	ParaJudge();
	~ParaJudge();
	void paraJudge(int &argc, char *argv[]);
	string getInput();
	string getOutput();
	int getWeight();
	int getPhraseLength();
	int getSortNum();
private:
	string input;
	string output;
	int weight;
	int phraseLength;
	int sortNum;
	void judgePara_w(int weight);
	void judgePara_m(int phraseLength);
	void judgePara_n(int sortNum);
};

