#include "InputFile.h"
#include "PhraseCmp.h"
#include <algorithm>
#include <iostream>

/*bug1��ֻ�ᵥ��ֻ�����ͳ��һ��
	�޸���������char����wordArray�ж��һ�����ʣ��ڴﵽ(Ҫ��)������ʱ����phraseLength�����ʣ� ÿ�ζ�ȡ�����ָ�����һ����׺�ľ���
  bug2��Abstract��ĩβû�л��з�ʱ����ͳ��һ�ε���
	�޸�������1.ѯ�����������ļ���ʽ
  bug3���ڴ��鳤��Ϊ1ʱsubstrʱ������쳣
	�޸�����������phraseLength>1ʱ��������ж�
  bug4����ȡ�ڶ����ļ���Title��tempChar����������ȡ�ַ�
	�޸�������֮ǰ��������������c++��get()�������ȶ�������֪��ΪʲôĪ���������
 */

InputFile::InputFile(string inputPath, int _phraseLength, int _weight, int _sortNum)
{
	crtNum = 0;
	lineNum = 0;
	wordNum = 0;
	phraseNum = 0;

	sortNum = _sortNum;
	phraseLength = _phraseLength;
	weight = _weight;
	hasCount = false;
	hasSort = false;

	inputFile.open(inputPath, ios::in);

	if (!inputFile)
	{
		hasOpenFile = false;
		cerr << inputPath << "�ļ������ڣ�" << endl;
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

int InputFile::getPhraseNum()
{
	if (!hasCount) readFile();
	return phraseNum;
}

void InputFile::readFile()
{
	hasCount = true;
	if (!hasOpenFile) return;

	/*��ͷ��ȡ�ļ�*/
	inputFile.clear(ios::goodbit);
	inputFile.seekg(ios::beg);

	/*�ݴ��Ա����*/
	int _lineNum = 0;
	int _crtNum = 0;
	int _wordNum = 0;
	int _phraseNum = 0;

	/*�ж��ַ��Ƿ���Ч���õľֲ�����*/
	int crlfNum = 0;											//���з���Ŀ
	bool flag_switch = true;									//�Ƿ����switch���
	int skipNum = 0;											//Title��Abstract���������ַ���
	bool flag_count = false;									//�Ƿ���д�Ƶͳ��	

	bool flag_hasCrt = false;									//�ж��Ƿ�հ���
	int _weight = 1;

	/*�жϵ������õľֲ�����*/
	char tempChar;
	int alpLength = 0;											//������������ĸ����
	bool flag_numBefAlp = false;								//�ж���ĸǰ�Ƿ��������
	char wordArray[500];										//��Ŵ��������	
	int arrayLength = 0;										//���鳤��(����char����תstring)


	int wordLength[10];											//����ÿ�����ʼ��Ϸָ�����׺�ĳ���
	int tag = 0;												//���浱ǰ��׺���ȵ��±�(���к��0��ʼ)
	int tempTag = 0;
	int tempInt = 0;											//���浥����׺����
	string phrase;												//��ʱ����Ĵ���
	int _phraseLength = 0;										//phrase�ַ����е��ʵĸ���(�����Ŀǰ����)

	inputFile >> noskipws;										//�����Կո�

	while (inputFile.get(tempChar))
	{
		//inputFile >> tempChar;
		/*ͨ��crlfNum��ֵ�жϵ�ǰ������һ��*/
		switch (crlfNum)
		{
			/*Title�У������߸��ַ�����д�Ƶͳ��*/
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
		/*Abstract�У�����10���ַ�����д�Ƶͳ��*/
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
		/*�����У����Ե�ǰ�������ַ�*/
		default:
			if (tempChar == '\n') crlfNum = (crlfNum + 1) % 5;
			flag_count = false;
			break;
		}

		if (!flag_count) continue;

		/*��Ƶͳ��*/
		_crtNum++;

		/*
		��Ƶͳ��
		 1. �жϵ���
		 */
		 /*��ȡ�ַ�Ϊ�Ƿָ���*/
		if ((tempChar >= 'a' && tempChar <= 'z') || (tempChar >= 'A' && tempChar <= 'Z') || (tempChar >= '0' && tempChar <= '9'))
		{
			/*���ڷǷ�����ʱ�޷����ɴ���,��ջ���*/
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
				if (flag_numBefAlp && alpLength < 4) continue;
				if (tempChar >= 'A' && tempChar <= 'Z') tempChar = tempChar - 'A' + 'a';
				alpLength++;									//�����ʿ�ͷ��������ĸ��Ŀ+1
				/*�µĵ��ʶ��룬�ַ�����ǰһ��Ϊ��׺*/
				if (alpLength == 1 && _phraseLength > 0 && phraseLength > 1)
				{
					wordLength[tag] = tempInt;					//������һ����׺
					tempInt = 0;								//���õ�ǰ��׺����
					tag = (tag + 1) % 10;
				}
			}
			wordArray[arrayLength++] = tempChar;				//����Ҫ����ַ������������α����
			tempInt++;
		}
		/*��ȡ�ַ�Ϊ�ָ���*/
		else
		{
			if (flag_numBefAlp) flag_numBefAlp = false;
			/*�ָ���ǰ��һ�������ĵ���*/
			if (alpLength >= 4)
			{
				_phraseLength++;								//�����е��ʸ���+1
				_wordNum++;
				tempInt++;

				/*���ʸ�������������Ҫ��*/
																//����Ҫ��Ӧ����ǰ�������phrase��������������׺��������
				if (_phraseLength == phraseLength)
				{
					/*�������phrase*/
					wordArray[arrayLength] = 0;
					phrase = wordArray;

					/*���������������*/
					itor = phraseMap.find(phrase);
					if (itor != phraseMap.end()) itor->second += _weight;
					else
					{
						phraseMap.insert(make_pair(phrase, _weight));
						_phraseNum++;
					}
					/*����������׺��������*/
					if (phraseLength > 1)
					{
						tempTag = tag - phraseLength + 1;
						if (tempTag < 0) tempTag += 10;
						phrase = phrase.substr(wordLength[tempTag]);
						strcpy_s(wordArray, phrase.c_str());
						arrayLength -= (wordLength[tempTag]);	//�൱���ַ�����ָ�����һ����׺�ĳ���
					}

					_phraseLength--;							//�ַ������д�׺��Ŀ-1
				}
				if (phraseLength > 1) wordArray[arrayLength++] = tempChar;
				else arrayLength = 0;
				alpLength = 0;
			}
			/*�ָ�����������ָ�����ã��豣��*/
			else if (alpLength == 0 && _phraseLength > 0 && phraseLength > 1)
			{
				wordArray[arrayLength++] = tempChar;
				tempInt++;
			}
			/*�ָ���ǰ���ǷǷ����ʣ�������黺��*/
			else if (alpLength > 0 && alpLength < 4)
			{
				alpLength = 0;
				arrayLength = 0;
				_phraseLength = 0;
				tempInt = 0;
			}
		}

		/*
		��Ƶͳ��
		 2. �жϿհ���
		 */
		if (tempChar != ' ' && !flag_hasCrt && tempChar != '\t' && tempChar != '\n') flag_hasCrt = true;
		if (tempChar == '\n')
		{
			if (flag_hasCrt)
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

	/*�ļ����һ��ΪAbstractʱ������ж�(���һ������ĩβ����û�зָ���)*/
	if (flag_hasCrt)
	{
		_lineNum++;
		flag_hasCrt = false;
	}
	if (alpLength >= 4)
	{
		_phraseLength++;
		_wordNum++;
		tempInt++;

		/*���ʸ�������������Ҫ��*/
														//����Ҫ��Ӧ����ǰ�������phrase��������������׺��������
		if (_phraseLength == phraseLength)
		{
			/*�������phrase*/
			wordArray[arrayLength] = 0;
			phrase = wordArray;

			/*���������������*/
			itor = phraseMap.find(phrase);
			if (itor != phraseMap.end()) itor->second += _weight;
			else
			{
				phraseMap.insert(make_pair(phrase, _weight));
				_phraseNum++;
			}
			/*����������׺��������*/
			if (phraseLength > 1)
			{
				tempTag = tag - phraseLength + 1;
				if (tempTag < 0) tempTag += 10;
				phrase = phrase.substr(wordLength[tempTag]);
				strcpy_s(wordArray, phrase.c_str());
				//arrayLength -= (wordLength[tempTag]);		//�൱���ַ�����ָ�����һ����׺�ĳ���
			}
			_phraseLength--;							//�ַ������д�׺��Ŀ-1
		}

		alpLength = 0;
	}

	lineNum = _lineNum;
	crtNum = _crtNum;
	wordNum = _wordNum;
	phraseNum = _phraseNum;
}

/*�����ʰ�Ҫ������󱣴浽orderWord������*/
void InputFile::sortPair()
{
	hasSort = true;
	/*ͨ����������unordered_map�е�pair���ݸ��Ƶ�vector��*/
	for (itor = phraseMap.begin(); itor != phraseMap.end(); itor++) {
		orderWord.push_back(make_pair(itor->first, itor->second));
		//cout << "<" << itor->first << ", " << itor->second << ">" << endl;
	}
	int i = (int)phraseMap.size();
	if (i > sortNum) i = sortNum;
	/*ͨ��paritial_sort������vector�еĵ��ʰ���ĿҪ������*/
	partial_sort(orderWord.begin(), orderWord.begin() + i, orderWord.end(), PhraseCmp());
}

/*�����ú���*/
vector<pair<string, int>> InputFile::getOrderWord()
{
	if (!hasSort) sortPair();
	return orderWord;
}