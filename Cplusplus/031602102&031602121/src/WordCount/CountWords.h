#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cassert>
#include <algorithm>

using namespace std;
int CountWords(char *filename)
{
	ifstream in(filename);          //  ���ļ�
	if (!in)
	{
		cerr << "�޷��������ļ�" << endl;
		return -1;
	}
	char word[100000];
	string ss;
	int WordNum=0;
	while (in.getline(word, 100000))         //   istream &in �����հ��ַ����ո�����Ʊ���ͻ��з�����ֹͣ���롣
	{
		
		ss = word;//��һ�������ַ���ss
		//cout << "::"<< ss.length() << endl;
		for (int i = 0; i < ss.length(); i++)//��ÿ�еĲ���
		{
			int count = 0;
			int char_Count = 0;
			int num_Pid = 0;//���ֱ�ʶ�����жϵ���ǰ���Ƿ�������
			for (int k = i;; k++)//�ж��Ƿ���������е��ʵ�����
			{

				
				if (ss[k] >= 'a'&&ss[k] <= 'z'&&num_Pid == 0)
				{
					char_Count++;
					count++;
				}
				else if (ss[k] >= 'A'&&ss[k] <= 'Z'&&num_Pid == 0)
				{
					char_Count++;
					count++;
				}
				else if (ss[k] >= '0'&&ss[k] <= '9')
				{
					count++; 
					num_Pid = 1;
					char_Count++;
				}
				else if (ss[k] == ':')
				{
					count++;
					char_Count=0;
				}
				else break;
			}
			if (char_Count >= 4) //������Ҫ�����¼
			{
				char words[100] = { '\0' };
				for (int k = i; k < i + count; k++)
				{
					words[k - i] = ss[k];
				}
			
				WordNum++;//ͳ���ܵ�����
				i += count - 1;
			}
			else if (count>0 && count<4)i += count - 1;
			else continue;
		}

	}

	return WordNum;
}