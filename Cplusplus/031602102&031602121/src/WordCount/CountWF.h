#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<cassert>
#include <algorithm>
#include <list>
using namespace std;
int K;
map<string, int> essay;
list<string> b('\0');
list<string>::iterator it1;
bool cmp(int a, int b)
{
	return a>b;
}
void Count(string tempLine, int MaxNum, int head,int weight_Pid)
{
	for (int i = head; i < tempLine.length(); i++)
	{

		int count = 0;
		int char_Count = 0;
		int num_Pid = 0;//数字标识符，判断单词前中是否有数字
		for (int k = i;; k++)//判断是否符合需求中单词的样子
		{

			if (tempLine[k] >= 'a'&&tempLine[k] <= 'z'&&num_Pid == 0)
			{
				char_Count++;
				count++;
			}
			else if (tempLine[k] >= 'A'&&tempLine[k] <= 'Z'&&num_Pid == 0)
			{
				char_Count++;
				count++;
			}
			else if (tempLine[k] >= '0'&&tempLine[k] <= '9')
			{
				count++;
				num_Pid = 1;
			}
			else if (tempLine[k] == ':')
			{
				count++;
				char_Count = 0;
			}
			else break;
		}
		if (char_Count >= 4) //若符合要求，则记录
		{
			char words[100] = { "\0" };            //单词存储
			for (int k = i; k < i + count; k++)
			{
				words[k - i] = tempLine[k];

			}
			string s = words;
			b.push_back(s);   //推入队列尾
			s = "\0";
			if (b.size() == MaxNum)//队列满
			{
				int nowNum = MaxNum;
				for (it1 = b.begin(); it1 != b.end(); it1++)
				{
					s.append(*it1);
					
					nowNum--;
					if (nowNum != 0)s.append(" ");
				}
				if(head==7&&weight_Pid==1)essay[s]+=10;//记录词组/单词
				else essay[s]++;
				b.pop_front();
				s = "\0";


			}

			i += count - 1;
		}
		else if (count > 0 && count < 4)
		{
			b.clear();
			i += count - 1;
		}
		else continue;

	}
	if (head == 7)b.clear();
}
void adjustDown(vector<map<string, int>::iterator> &top, int i)					//调整堆
{
	int min = i;
	int child = 2 * min + 1;
	while (i < K / 2)
	{
		if ((child + 1 < K) && (top[child]->second > top[child + 1]->second))
			child++;
		if ((child<K) && (top[min]->second>top[child]->second))
		{
			swap(top[min], top[child]);
			min = child;
			child = 2 * min + 1;
		}
		else
			break;
	}
}
void topK(map<string, int> &essay, vector<map<string, int>::iterator> &top, ofstream &fout,char *filename)
{
	auto it = essay.begin();
	//  初始化完全二叉树
	for (int i = 0; i < K; i++)
	{
		top[i] = it;
		it++;
	}
	//  建立小根堆
	for (int i = K / 2 - 1; i >= 0; i--)
	{
		adjustDown(top, i);
	}
	//  取topK
	while (it != essay.end())
	{
		if (it->second > top[0]->second)
		{
			top[0] = it;                     //  大于堆顶元素，则入堆；
			adjustDown(top, 0);              //  重新调整为小根堆；

		}
		it++;
	}
	int a[1000];
	string b[1000];

	for (int i = K - 1; i >= 0; i--)
	{
		a[i] = essay[top[0]->first];
		b[i] = top[0]->first;
		top[0]->second = 1000000;
		adjustDown(top, 0);              //  重新调整为小根堆；
	}
	sort(a, a + K, cmp);
	fout.open(filename, ios::app);
	for (int i = 0; i < K; i++)
	{
		fout << "<" << b[i] << ">: " << a[i] << endl;
	}
	fout.close();
}
void CountWF(char *filename, ofstream &fout,char* outfile,int topNum,int MaxNum,int weigth_Pid)
{
	int num = 0;
	K = topNum;
	ifstream in(filename);          //  打开文件
	if (!in)
	{
		cerr << "无法打开输入文件" << endl;
		exit(0);
	}
	char readLine[100000];
	string tempLine;

	list<string> listString;
	while (in.getline(readLine, 100000))
	{

		tempLine = readLine;//存储当前行的字符串
		if (tempLine.length()<6)
		{
			b.clear();
			continue;
		}
		else if (readLine[0] == 'T'&&readLine[1] == 'i'&&readLine[2] == 't'&&readLine[3] == 'l'&&readLine[4] == 'e')
		{
			Count(tempLine, MaxNum, 7,weigth_Pid);
		}
		else if (readLine[0] == 'A'&&readLine[1] == 'b'&&readLine[2] == 's'&&readLine[3] == 't'&&readLine[4] == 'r'&&readLine[5] == 'a'&&readLine[6] == 'c'&&readLine[7] == 't')
		{
			Count(tempLine, MaxNum, 10, weigth_Pid);
		}
		else if(readLine)
		{
			Count(tempLine, MaxNum, 0,weigth_Pid);
		}
	}
	if (essay.size() < K)K = essay.size();
	vector < map<string, int> ::iterator> top(K, essay.begin());
	topK(essay, top, fout,outfile);

}