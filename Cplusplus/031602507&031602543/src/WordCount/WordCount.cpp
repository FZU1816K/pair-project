/********************************************************************************
* @File name: WordCount.cpp
* @Author: ChenYuXin
* @Version: 5.8
* @Date: 2018-10-06
* @Description: code optimization 
********************************************************************************/


#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<regex>
#include<map>
#include<algorithm>
#include"Count.h"	//��װ���е�ͳ����صĹ���
#include"FileIO.h"	//��װ�����ļ���д��صĹ���
#include"Additional.h"
using namespace std;



int main(int argc, char *argv[]) 
{
	for (int j = 0; j < 1; j++)
	{
		int lineCount = 0;			//����
		int characterCount = 0;		//�ַ���
		int wordCount = 0;			//������
		int paperCount = 0;			//������
		int invaildChar = 0;		//��Ч�ַ���
		const char* inputFileName = "input(2).txt";  //�����ļ���
		const char* outputFileName = "output.txt"; //����ļ���
		int weightValue = 0;		//Ȩ��
		int phraseLen = -1;         //���ʸ���
		int topX = 10;				//Ƶ����ߵĵ���(����),Ĭ��Ϊ10
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-i") == 0)
			{
				inputFileName = argv[i + 1];
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				outputFileName = argv[i + 1];
			}
			else if (strcmp(argv[i], "-w") == 0)
			{
				weightValue = atoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-m") == 0)
			{
				phraseLen = atoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-n") == 0)
			{
				topX = atoi(argv[i + 1]);
			}
		}
		Count count;
		string charBuf;
		vector<string> linesBuf;
		Additional additional;
		additional.readF(inputFileName, linesBuf);
		additional.countAuthor(linesBuf);
		cout << 1;
		if(FileIO::readFile(inputFileName,charBuf,linesBuf))			
		{	
			characterCount = count.countCharNum(charBuf);			//�����ַ���
			lineCount = count.countLineNum(linesBuf);				//��������
			if (phraseLen == -1)
			{
				wordCount = count.countWordNum(linesBuf, weightValue);	//���㵥����
				paperCount = count.getpaperCount();						//��ȡ������
				invaildChar = (paperCount * 17);						//������Ч�ַ���
				vector<map<string, int>::iterator> topXWord = count.countTopXWord(topX);	//ͳ�Ƴ���Ƶ����ߵ�10�����ʣ��п��ܵ�����û��10����
				if (!FileIO::outputToFile(characterCount - invaildChar, wordCount, lineCount, outputFileName, topXWord))	//�����������ļ�
				{
					cout << "output to file fail";
				}
			}
			else
			{
				wordCount = count.countPhraseNum(linesBuf, weightValue,phraseLen);	//���������
				paperCount = count.getpaperCount();									//��ȡ������
				invaildChar = (paperCount * 17);									//������Ч�ַ���
				vector<map<string, int>::iterator> topXPhrase = count.countTopXPhrase(topX);	//ͳ�Ƴ���Ƶ����ߵ�10�����飨�п��ܵ�����û��10����
				if (!FileIO::outputToFile(characterCount - invaildChar, wordCount, lineCount, outputFileName, topXPhrase))	//�����������ļ�
				{
					cout << "output to file fail";
				}
			}
		}
		else
		{
			cout << "read file fail";
		}
	}

	system("pause");
	return 0;
}