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
		if (line == "") // 跳过空行
		{
			cout << "empty line!" << endl;
			continue;
		}
		else if (stringIsNum(line)) // 跳过标号行
		{
			cout << "number line!" << line << endl;
			continue;
		}
		else if (line.find("Title: ") != string::npos) { // 标题行，统计时 Title: 不计入统计字符数和单词数
			line = line.substr(7);

			numChar += CountChar(line); // 字符数是此行长度加上末尾的换行符 
			numLines++;	// 有效行数+1
			numWords += CountWords(line); // 统计单词数

			if (phraseFrequencyOn == 0) { // 统计词频
				if (weightFrequencyOn == 1) // 根据命令行参数选择是否开启权重词频模式
					WordFrequency(line, TITLE);
				else if (weightFrequencyOn == 0)
					WordFrequency(line, NONWEIGHT);
			}
			else { // if (phraseFrequencyOn == 1)  // 统计词组频
				if (weightFrequencyOn == 1) // 根据命令行参数选择是否开启权重词频模式
					PhraseFrequency(line, TITLE);
				else if (weightFrequencyOn == 0)
					PhraseFrequency(line, NONWEIGHT);
			}
		}
		else if (line.find("Abstract: ") != string::npos) { // 摘要行，统计时Abstract: 不计入统计字符数和单词数
			line = line.substr(10);

			numChar += CountChar(line);
			numLines++;
			numWords += CountWords(line);

			if (phraseFrequencyOn == 0) {
				if (weightFrequencyOn == 1) // 根据命令行参数选择是否开启权重词频模式
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