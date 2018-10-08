#include <iostream>
#include "InputFile.h"

using namespace std;

#define WRITING_FILE "result.txt"
#define ORDER_WORD vector<pair<string, int>>


int main() 
{
	string order_inputPath;
	int order_weight = 0;
	string order_outputPath;
	int order_phraseLength = 1;
	int order_sortNum = 10;

	order_inputPath = "input.txt";
	order_phraseLength = 3;
	order_weight = 0;

	InputFile inputFile(order_inputPath, order_phraseLength, order_weight, order_sortNum);



	/*测试语句*/
	/*
	ofstream fileWrite(WRITING_FILE, ios::out | ios::trunc);
	int crtNum = inputFile.getCrtNum();
	int lineNum = inputFile.getLineNum();
	int wordNum = inputFile.getWordNum();
	ORDER_WORD orderWord = inputFile.getOrderWord();
	ORDER_WORD::iterator outItor;
	if (!fileWrite) {										//异常处理
		cerr << WRITING_FILE << "文件写入失败!" << endl;
		exit(1);											//在单元测试时为保证测试不中断需将其注释
	}
	fileWrite << "characters: " << crtNum << endl;
	fileWrite << "words: " << wordNum << endl;
	fileWrite << "lines: " << lineNum << endl;
	outItor = orderWord.begin();
	for (int i = 0; i < 10 && outItor != orderWord.end(); i++, outItor++) {
		fileWrite << "<" << outItor->first << ">" << ": " << outItor->second << endl;
	}
	fileWrite.close();
	*/
	///*
	cout << "characters: " << inputFile.getCrtNum() << endl;
	cout << "words: " << inputFile.getWordNum() << endl;
	cout << "lines: " << inputFile.getLineNum() << endl;
	vector<pair<string, int>> orderWord = inputFile.getOrderWord();
	vector<pair<string, int>>::iterator outItor;
	outItor = orderWord.begin();
	for (int i = 0; i < 10 && outItor != orderWord.end(); i++, outItor++) 
	{
		cout << "<" << outItor->first << ">" << ": " << outItor->second << endl;
	}
	system("pause");
	//*/

	return 0;
}