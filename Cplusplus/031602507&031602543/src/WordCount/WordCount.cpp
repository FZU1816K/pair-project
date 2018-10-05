/********************************************************************************
* @File name: wc.cpp
* @Author: ChenYuXin
* @Version: 5.2
* @Date: 2018-10-05
* @Description: fixed bugs
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
using namespace std;



int main(int argc, char *argv[]) 
{
	for (int j = 0; j < 1; j++)
	{
		int lineCount = 0;			//����
		int characterCount = 0;		//�ַ���
		int wordCount = 0;			//������
		const char* inputFileName = "";  //�����ļ���
		const char* outputFileName = ""; //����ļ���
		int weightValue = 0;		//Ȩ��
		int phraseLen = -1;         //���鳤��
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
		if(FileIO::readChar(argc, argv,inputFileName,charBuf,linesBuf))			
		{
			characterCount = count.countCharNum(charBuf);			//�����ַ���
			lineCount = count.countLineNum(linesBuf);				//��������
			wordCount = count.countWordNum(linesBuf,weightValue);	//���㵥����
			if (phraseLen == -1)									//�����ô����Ƶͳ�ƹ���
			{
				vector<map<string, int>::iterator> topXWord = count.countTopXWord(topX);	//ͳ�Ƴ���Ƶ����ߵ�10�����ʣ��п��ܵ�����û��10����
				FileIO::outputToFile(characterCount, wordCount, lineCount, outputFileName, topXWord);	//�����������ļ�
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