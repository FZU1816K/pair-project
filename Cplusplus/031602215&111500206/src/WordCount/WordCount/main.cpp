#include<iostream>
#include<fstream>
#include<sstream>
#include"ArgumentParser.h"
#include"CountChar.h"
#include"CountLines.h"
#include"CountWords.h"
#include"WordFrequency.h"
#include"comm.h"

using namespace std;

extern std::string inputFileName;
extern std::string outputFileName;
extern int weightFrequencyOn;
extern int phraseFrequencyOn;
extern int phraseLength;
extern int topNWords;

void old()
{
	int numberOfChar = CountChar(inputFileName.c_str());
	int numberOfLines = CountLines(inputFileName.c_str());
	int numberOfWords = CountWords(inputFileName.c_str());

	printf("In this file:\n");
	printf("Number of characters: %d\n", numberOfChar);
	printf("Number of non-empty lines: %d\n", numberOfLines);
	printf("Number of words: %d\n", numberOfWords);

	printf("Top 10 words:\n");
	WordFrequency(inputFileName.c_str(), 2);

	auto topTenWordList = TopNWords();
	StandardOutput(topTenWordList);

	fstream file;
	file.open(outputFileName.c_str(), ios::out);
	file << "characters: " << numberOfChar << endl;
	file << "words: " << numberOfWords << endl;
	file << "lines: " << numberOfLines << endl;
	file.close();

	OutputToFile(topTenWordList);

	return;
}

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

			numChar += (line.size() + 1); // 字符数是此行长度加上末尾的换行符
			numLines++;	// 有效行数+1
			numWords += CountWords(line); // 统计单词数

			if (weightFrequencyOn == 1) // 根据命令行参数选择是否开启权重词频模式
				WordFrequency(line, TITLE);
			else if (weightFrequencyOn == 0)
				WordFrequency(line, NONWEIGHT);
		}
		else if (line.find("Abstract: ") != string::npos) { // 摘要行，统计时Abstract: 不计入统计字符数和单词数
			line = line.substr(10);

			numChar += (line.size() + 1);
			numLines++;
			numWords += CountWords(line);

			if (weightFrequencyOn == 1) // 根据命令行参数选择是否开启权重词频模式
				WordFrequency(line, ABSTRACT);
			else if (weightFrequencyOn == 0)
				WordFrequency(line, NONWEIGHT);
		}
	}

	auto wordsFrequencyList = TopNWords();

	OutputToFile(numChar, numWords, numLines);
	OutputToFile(wordsFrequencyList);

	return 0;
}