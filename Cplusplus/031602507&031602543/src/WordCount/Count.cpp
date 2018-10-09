#include "Count.h"

//�����ַ���
int Count::countCharNum(string &charBuf)
{
	return int(charBuf.size());
}
//��������
int Count::countLineNum(vector<string> &linesBuf)
{
	int lineCount = 0;
	for (int i = 0; i != linesBuf.size(); i++) 
	{
		for (string::iterator it = linesBuf[i].begin(); it != linesBuf[i].end(); it++) 
		{
			if (*it > 32) 
			{
				lineCount++;
				break;
			}
		}
	}
	return lineCount;
}
//���㵥����/������
int Count::countWordNum(vector<string> &linesBuf,int weightValue, int phraseLen)
{
	int wordCount = 0;
	int linesBufSize = int(linesBuf.size());
	string wordBuf;
	vector<string> phraseBuf;
	int wordInPhrase = 0;	//���黺���еĵ�����
	int isTitle = 0;
	for (int i = 0; i != linesBufSize; i++)
	{
		int len = int(linesBuf[i].length());
		for (int j = 0; j < len; j++)
		{
			if (isLetter(linesBuf[i][j]) || isDigit(linesBuf[i][j]))
			{
				wordBuf += linesBuf[i][j];
			}
			else
			{
				if (wordBuf == "title" && linesBuf[i][j] == ':' && j == 5)
				{
					paperCount++;	//ÿ����һ�� title: ˵����һƪ����
					isTitle = 1;
					wordBuf = "";
					phraseBuf.clear();	//���ֶεĴ��鲻��
					wordInPhrase = 0;
					continue;
				}
				if (wordBuf == "abstract" && linesBuf[i][j] == ':' && j == 8)
				{
					isTitle = 0;
					wordBuf = "";
					phraseBuf.clear();
					wordInPhrase = 0;
					continue;
				}
				if (isWord(wordBuf))
				{
					phraseBuf.push_back(wordBuf);
					wordInPhrase++;
					if (wordInPhrase == phraseLen)
					{
						string phrase;
						int phraseBufSize = phraseBuf.size();
						for (int it = 0; it < phraseBufSize; it++)
						{
							phrase += phraseBuf[it];
						}
						phraseMap[phrase]++;
						phraseBuf.erase(phraseBuf.begin());
						wordInPhrase--;
						while (!phraseBuf.empty())
						{
							if (!isWord(phraseBuf[0]))
							{
								phraseBuf.erase(phraseBuf.begin());
							}
							else
							{
								break;
							}
						}
					}
					if (weightValue == 0)	//û��Ȩ�صĴ�Ƶͳ��
					{
						wordMap[wordBuf]++;
						wordCount++;
					}
					else
					{
						if (isTitle == 1)	//�����ֶεĵ���
						{
							wordMap[wordBuf] += 10;
							wordCount++;
						}
						else
						{
							wordMap[wordBuf]++;
							wordCount++;
						}
					}
				}
				else
				{
					if (!wordBuf.empty())
					{
						phraseBuf.clear();
						wordInPhrase = 0;
					}
				}
				if (wordInPhrase > 0)
				{
					phraseBuf.push_back(string(1,linesBuf[i][j]));	//����ָ��������Ǵ��鲻���Էָ�����ͷ
				}
				wordBuf = "";
			}
		}
		if (isWord(wordBuf))
		{
			phraseBuf.push_back(wordBuf);
			wordInPhrase++;
			if (wordInPhrase == phraseLen)
			{
				string phrase;
				int phraseBufSize = phraseBuf.size();
				for (int it = 0; it < phraseBufSize; it++)
				{
					phrase += phraseBuf[it];
				}
				phraseMap[phrase]++;
				phraseBuf.erase(phraseBuf.begin());
				wordInPhrase--;
				while (!phraseBuf.empty())
				{
					if (!isWord(phraseBuf[0]))
					{
						phraseBuf.erase(phraseBuf.begin());
					}
					else
					{
						break;
					}
				}
			}
			if (weightValue == 0)
			{
				wordMap[wordBuf]++;
				wordCount++;
			}
			else
			{
				if (isTitle == 1)	//�����ֶεĵ���
				{
					wordMap[wordBuf] += 10;
					wordCount++;
				}
				else
				{
					wordMap[wordBuf]++;
					wordCount++;
				}
			}
		}
		else
		{
			if (!wordBuf.empty())
			{
				phraseBuf.clear();
				wordInPhrase = 0;
			}
		}
		wordBuf = "";
	}
	return wordCount;
}
//ͳ�Ƴ���Ƶ����ߵ�X������
vector<map<string, int>::iterator> & Count::countTopXWord(int topX)
{
	int wordMapSize = int(wordMap.size());
	for (int i = 0; i < wordMapSize && i < topX; i++)
	{
		auto maxFreWord = wordMap.begin();
		for (map<string,int>::iterator it = wordMap.begin(); it != wordMap.end(); it++)
		{
			if (it->second > maxFreWord->second)
			{
				maxFreWord = it;
			}
		}
		topXWord.push_back(maxFreWord);
		maxFreWord->second = -maxFreWord->second;
	}
	return topXWord;
}
//ͳ�Ƴ���Ƶ����ߵ�X������
vector<map<string, int>::iterator> & Count::countTopXPhrase(int topX)
{
	int phraseMapSize = int(phraseMap.size());
	for (int i = 0; i < phraseMapSize && i < topX; i++)
	{
		auto maxFrxPhrase = phraseMap.begin();
		for (map<string, int>::iterator it = phraseMap.begin(); it != phraseMap.end(); it++)
		{
			if (it->second > maxFrxPhrase->second)
			{
				maxFrxPhrase = it;
			}
		}
		topXPhrase.push_back(maxFrxPhrase);
		maxFrxPhrase->second = -maxFrxPhrase->second;
	}
	return topXPhrase;
}
//��ȡ paperCount ��ֵ
int Count::getpaperCount()
{
	return paperCount;
}

//�ж��Ƿ�Ϊ��ĸ
inline bool Count::isLetter(string::iterator it) {
	return (*it >= 97 && *it <= 122) ;
}
//�ж��Ƿ�Ϊ��ĸ(����)
inline bool Count::isLetter(const char & ch) {
	return (ch >= 97 && ch <= 122);
}
//�ж��Ƿ�Ϊ����
inline bool Count::isDigit(string::iterator it) 
{
	return *it >= '0' && *it <= '9';
}
//�ж��Ƿ�Ϊ����(����)
inline bool Count::isDigit(const char  & ch)
{
	return ch >= '0' && ch <= '9';
}
//�ж��Ƿ�Ϊ����
inline bool Count::isWord(const string & str)
{
	return (str.length() >= 4 && isLetter(str[0]) && isLetter(str[1]) && isLetter(str[2]) && isLetter(str[3]));
}