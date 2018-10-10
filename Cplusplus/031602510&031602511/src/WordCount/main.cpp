#include <iostream>
#include <sstream>
#include "InputFile.h"
#include "ParaJudge.h"

#include <cstdlib>

using namespace std;

void writeTxt(string *output, int &crtNum, int &lineNum, int &wordNum, int &sortNum, vector<pair<string, int>>::iterator outItor, vector<pair<string, int>>::iterator outItorEnd);

int main(int argc, char *argv[])
{
	//for (int i = 0; i < 10000; i++)
	//{
	ParaJudge paraJudge;
	paraJudge.paraJudge(argc, argv);

	/*命令行参数相关，分别为：
	 -i, -o, -w, -m, -n
	 */
	string input;
	string output;
	int weight;
	int phraseLength;
	int sortNum;
	/*
	input = "input.txt";
	weight = 0;
	phraseLength = 3;
	sortNum = 10;
	*/

	input = paraJudge.getInput();
	output = paraJudge.getOutput();
	weight = paraJudge.getWeight();
	phraseLength = paraJudge.getPhraseLength();
	sortNum = paraJudge.getSortNum();

	InputFile inputFile(input, phraseLength, weight, sortNum);

	int crtNum = inputFile.getCrtNum();
	int lineNum = inputFile.getLineNum();
	int wordNum = inputFile.getWordNum();
	vector<pair<string, int>> orderWord = inputFile.getOrderWord();
	vector<pair<string, int>>::iterator outItor;
	vector<pair<string, int>>::iterator outItorEnd;
	outItor = orderWord.begin();
	outItorEnd = orderWord.end();

	writeTxt(&output, crtNum, lineNum, wordNum, sortNum, outItor, outItorEnd);

	/*测试语句*/
	/*
	//cout << "phrase: " << inputFile.getPhraseNum() << endl;
	cout << "characters: " << inputFile.getCrtNum() << endl;
	cout << "words: " << inputFile.getWordNum() << endl;
	cout << "lines: " << inputFile.getLineNum() << endl;
	for (int i = 0; i < sortNum && outItor != outItorEnd; i++, outItor++)
	{
		cout << "<" << outItor->first << ">" << ": " << outItor->second << endl;
	}
	system("pause");
	*/
	//}
	return 0;
}

void writeTxt(string *output, int &crtNum, int &lineNum, int &wordNum, int &sortNum, vector<pair<string, int>>::iterator outItor, vector<pair<string, int>>::iterator outItorEnd)
{
	ofstream fileWrite(*output, ios::out | ios::trunc);
	if (!fileWrite) {										//异常处理
		cerr << output << "文件写入失败!" << endl;
		exit(1);											//在单元测试时为保证测试不中断需将其注释
	}
	fileWrite << "characters: " << crtNum << endl;
	fileWrite << "words: " << wordNum << endl;
	fileWrite << "lines: " << lineNum << endl;
	for (int i = 0; i < sortNum && outItor != outItorEnd; i++, outItor++) {
		fileWrite << "<" << outItor->first << ">" << ": " << outItor->second << endl;
	}
	fileWrite.close();
}