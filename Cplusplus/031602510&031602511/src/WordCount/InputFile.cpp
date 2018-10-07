#include "InputFile.h"
#include "PhraseCmp.h"
#include <algorithm>
#include <iostream>

/*bug1：只会单词只会进入统计一次
 修复方法：在char数组wordArray中多存一个单词，在达到(要求)个单词时存入phraseLength个单词， 每次读取词组后指针后移一个词缀的距离
  bug2：Abstract行末尾没有换行符时会少统计一次单词
 修复方法：1.询问助教爬虫文件格式
 */

/*测试用函数*/
vector<pair<string, int>> InputFile::getOrderWord()
{
	if (orderWord.empty()) sortPair();
	return orderWord;
}

InputFile::InputFile(string inputPath, int _phraseLength, int _weight, int _sortNum)
{
	crtNum = 0;
	lineNum = 0;
	wordNum = 0;

	sortNum = _sortNum;
	phraseLength = _phraseLength;
	weight = _weight;
	hasCount = false;	

	inputFile.open(inputPath, ios::in);

	if (!inputFile)
	{
		hasOpenFile = false;
		cerr << inputPath << "文件不存在！" << endl;
		exit(1);
	}
					
	hasOpenFile = true;
}

InputFile::~InputFile()
{
	inputFile.close();
}

int InputFile::getCrtNum()
{
	if (!hasCount) readFile();
	return crtNum;
}

int InputFile::getLineNum()
{
	if (!hasCount) readFile();
	return lineNum;
}

int InputFile::getWordNum()
{
	if (!hasCount) readFile();
	return wordNum;
}

void InputFile::readFile()
{
	hasCount = true;
	if (!hasOpenFile) return;

	/*从头读取文件*/
	inputFile.clear(ios::goodbit);
	inputFile.seekg(ios::beg);
	
	/*暂存成员变量*/
	int _lineNum = 0;
	int _crtNum = 0;
	int _wordNum = 0;

	/*判断字符是否有效所用的局部变量*/
	int crlfNum = 0;											//换行符数目
	bool flag_switch = true;									//是否进入switch语句
	int skipNum = 0;											//Title和Abstract行跳过的字符数
	bool flag_count = false;									//是否进行词频统计	

	bool flag_hasCrt = false;									//判断是否空白行
	int _weight = 1;

	/*判断单词所用的局部变量*/
	char tempChar;											
	int alpLength = 0;											//单个单词中字母长度
	bool flag_numBefAlp = false;								//判断字母前是否存在数字
	char wordArray[100];										//存放词组的数组	
	int arrayLength = 0;										//数组长度(用于char数组转string)


	int wordLength[10];											//保存每个单词加上分隔符后缀的长度
	int tag = 0;												//保存当前词缀长度的下标(换行后从0开始)
	int tempTag = 0;
	int tempInt = 0;											//保存单个词缀长度
	string phrase;												//暂时保存的词组
	int _phraseLength = 0;										//phrase字符串中单词的个数(词组的目前长度)

	inputFile >> noskipws;										//不忽略空格
	
	while (inputFile.get(tempChar))
	{
		/*通过crlfNum的值判断当前处于哪一行*/
		switch (crlfNum)
		{
		/*Title行：跳过七个字符后进行词频统计*/
		case 1:
		{
			if (skipNum == 7)
			{
				flag_count = true;
				skipNum = 0;
				if (weight == 1) _weight = 10;
			}
			if (flag_count) break;
			skipNum++;
			break;
		}
		/*Abstract行：跳过10个字符后进行词频统计*/
		case 2:
		{
			if (skipNum == 10)
			{
				flag_count = true;
				skipNum = 0;
				_weight = 1;
			}
			if (flag_count) break;
			skipNum++;
			break;
		}
		/*其余行：忽略当前行所有字符*/
		default:
			if (tempChar == '\n') crlfNum = (crlfNum + 1) % 5;
			flag_count = false;
			break;
		}

		if (!flag_count) continue;

		/*词频统计*/
		_crtNum++;
		
		/*
		词频统计
		 1. 判断单词
		 */
																/*读取字符为非分隔符*/
		if ((tempChar >= 'a' && tempChar <= 'z') || (tempChar >= 'A' && tempChar <= 'Z') || (tempChar >= '0' && tempChar <= '9')) 
		{	
			/*存在非法单词时无法构成词组,清空缓存*/
			if ((tempChar >= '0' && tempChar <= '9') && (alpLength < 4)) 
			{
				alpLength = 0;												
				arrayLength = 0;	
				_phraseLength = 0;
				flag_numBefAlp = true;			
				tempInt = 0;							
				continue;
			}
			else if (!(tempChar >= '0' && tempChar <= '9')) 
			{							
				if (flag_numBefAlp && alpLength < 4) continue;	//如果前一个字符是数字且str数组开头连续字母数目<4,则一定不是单词，直接进行下一次读字符

				if (tempChar >= 'A' && tempChar <= 'Z') tempChar = tempChar - 'A' + 'a';	
				alpLength++;									//本单词开头的连续字母数目+1
				if (alpLength == 1 && _phraseLength > 0)		/*新的单词读入，字符数组前一串为词缀*/
				{
					wordLength[tag] = tempInt;
					tempInt = 0;
					tag = (tag + 1) % 10;
				}
			}
			wordArray[arrayLength++] = tempChar;				//符合要求的字符存入数组且游标后移
			tempInt++;
		}
																/*读取字符为分隔符*/
		else
		{
			/*分隔符前是一个完整的单词*/
			if (alpLength >= 4)
			{
				_phraseLength++;	
				_wordNum++;
				tempInt++;

				cout << wordArray << endl;

				/*单词个数满足词组个数要求*/
																//满足要求应将当前词组存入phrase，并将后两个词缀留在数组
				if (_phraseLength == phraseLength)
				{
					/*词组存至phrase*/
					wordArray[arrayLength] = 0;
					phrase = wordArray;						

					/*词组存入无序容器*/
					itor = phraseMap.find(phrase);
					if (itor != phraseMap.end()) itor->second += _weight;
					else phraseMap[phrase] = _weight;
				
					/*将后两个词缀留在数组*/
					tempTag = tag - phraseLength + 1;
					if (tempTag < 0) tempTag += 10;
					phrase = phrase.substr(wordLength[tempTag]);
					strcpy_s(wordArray, phrase.c_str());
					arrayLength -= (wordLength[tempTag]);		//相当于字符数组指针后移一个词缀的长度

					_phraseLength--;							//字符数组中词缀数目-1
				}
				wordArray[arrayLength++] = tempChar;
				alpLength = 0;
			}
			/*分隔符在起词组间分割单词作用，需保存*/
			else if (alpLength == 0 && _phraseLength > 0)
			{
				wordArray[arrayLength++] = tempChar;
				tempInt++;
			}
			/*分隔符前面是非法单词，清空数组缓存*/
			else if (alpLength > 0 && alpLength < 4)
			{
				alpLength = 0;
				arrayLength = 0;
				_phraseLength = 0;
				tempInt = 0;
			}
		}

		/*
		词频统计
		 2. 判断空白行
		 */
		if (tempChar != ' ' && !flag_hasCrt && tempChar != '\t' && tempChar != '\n') flag_hasCrt = true;
		if (tempChar == '\n')
		{
			if (flag_hasCrt = true)
			{
				_lineNum++;
				flag_hasCrt = false;

				alpLength = 0;
				arrayLength = 0;
				_phraseLength = 0;

				tempInt = 0;
				tag = 0;
			}
			crlfNum = (crlfNum + 1) % 5;
			flag_count = false;
			continue;
		}
	}
	
	lineNum = _lineNum;
	crtNum = _crtNum;
	wordNum = _wordNum;
}

/*将单词按要求排序后保存到orderWord容器中*/
void InputFile::sortPair() {
	/*通过迭代器将unordered_map中的pair数据复制到vector中*/
	for (itor = phraseMap.begin(); itor != phraseMap.end(); itor++) {
		orderWord.push_back(make_pair(itor->first, itor->second));
	}
	size_t i = phraseMap.size();	
	if (i > sortNum) i = sortNum;
	/*通过paritial_sort函数对vector中的单词按题目要求排序*/
	partial_sort(orderWord.begin(), orderWord.begin() + i, orderWord.end(), PhraseCmp());
}