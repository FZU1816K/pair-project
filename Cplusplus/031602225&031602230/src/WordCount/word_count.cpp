#include "pch.h"
#include<iostream>
#include<sstream>
#include<string>
#include<queue>
#include<stdio.h>
#include<fstream>
#include"word_count.h"
using namespace std;

struct wo {
	char word[500];
	int count;
};
priority_queue<wo> tmp;//优先队列
bool operator< (wo a, wo b)//自定义排序
{
	//个数相同的单词按字典排序
	if (a.count == b.count)
	{
		int i = -1;

		do {
			i++;
		} while (a.word[i] == b.word[i]);

		return a.word[i] > b.word[i];

	}
	//出现频率排序	
	else return a.count < b.count;
}

int MyCount::countLines(string u)
{
	int lines = 0;
	int flag = 0;
	int n = u.length();

	for (int i = 0; i < n; i++)
	{


		if (u[i] >= 33 && u[i] <= 126)//表示该行是有效行
		{
			flag = 1;
		}
		if (u[i] == 10 && flag == 1)//当该行是有效行，并且遍历到1个换行符时，行数加1
		{
			lines++;
			flag = 0;
		}
	}
	if (flag == 1)//最后一行如果没有换行符，也加1
		lines++;
	return lines;
}

int MyCount::countChars(string u)
{
	int a;
	a = u.length();
	return a;
}

int MyCount::countWords(string u)
{

	char temp[100];
	int k, flag;
	int words = 0;

	int n = u.length();
	for (int i = 0; i < n; i++)
	{

		//判断是否为单词
		if ((u[i] >= 'a'&&u[i] <= 'z') || (u[i] >= 'A'&&u[i] <= 'Z'))
		{
			k = 0;
			flag = 0;
			while ((u[i] >= 'a'&&u[i] <= 'z') || (u[i] >= 'A'&&u[i] <= 'Z') || (u[i] >= '0'&&u[i] <= '9'))
			{
				temp[k++] = u[i];
				i++;
			}
			temp[k++] = '\0';
			for (int j = 0; j < 4; j++)
			{
				if ((temp[j] >= '0'&&temp[j] <= '9') || temp[j] == '\0')
				{
					flag = 1;//判断是否符合单词规范
					break;
				}
			}
			if (flag == 0)
			{
				words++;
			}
		}
		else continue;
	}
	return words;
}

void MyCount::count(string u, string v, int m, int w)
{
	wo *cizu = new wo[1000000];//动态分配结构体数组
	wo temp_cizu;
	int t = 0;
	//扫描Title
	string *ci = new string[1000000];

	int k = 0;
	int le = u.length();
	for (int i = 0; i < le; i++)//存入所有的词和字符
	{

		if ((u[i] >= 'a'&&u[i] <= 'z') || (u[i] >= 'A'&&u[i] <= 'Z') || (u[i] >= '0'&&u[i] <= '9'))//第一个是字母或数字
		{

			while ((u[i] >= 'a'&&u[i] <= 'z') || (u[i] >= 'A'&&u[i] <= 'Z') || (u[i] >= '0'&&u[i] <= '9'))
			{
				if (u[i] >= 'A'&&u[i] <= 'Z')
					u[i] += 32;
				ci[k] += u[i];
				i++;
			}
			while (!(u[i] >= 'a'&&u[i] <= 'z') && !(u[i] >= 'A'&&u[i] <= 'Z') && !(u[i] >= '0'&&u[i] <= '9') && u[i] != '\n'&&i < le)
			{
				ci[k] += u[i];
				i++;
			}
			if (u[i] == '\n')ci[++k] = '\n';//换行符单独存

			i--;
			k++;
		}
		else continue;
	}

	for (int i = 0; i < k; i++)
	{
		int flag1 = 0;
		int flag2 = 0;

		for (int j = 0; j < 4; j++)
		{
			if (!(ci[i][j] >= 'a'&& ci[i][j] <= 'z'))
			{
				flag2 = 1;//判断第一个是否符合单词规范
				break;
			}
		}

		if (flag2 == 0)//第一个符合
		{
			strcpy_s(temp_cizu.word, 500,ci[i].c_str()); //
			temp_cizu.count = 1;
			if (w == 1)temp_cizu.count += 9;
			for (int j = 1; j < m; j++)
			{
				int flag3 = 0;
				for (int f = 0; f < 4; f++)
				{
					if (!(ci[i + j][f] >= 'a'&& ci[i + j][f] <= 'z'))
					{
						flag3 = 1;//判断后几个是否符合单词规范
						i = i + j;
						break;
					}
				}

				if (flag3 == 0)//后几个都合法
					strcat_s(temp_cizu.word, 500, ci[i + j].c_str());//
				else { flag1 = 1; break; }
			}


			if (flag1 == 0) //插入
			{
				int a = strlen(temp_cizu.word) - 1;//去掉结尾的符号

				while (!(temp_cizu.word[a] >= 'a'&&temp_cizu.word[a] <= 'z') && !(temp_cizu.word[a] >= '0'&&temp_cizu.word[a] <= '9'))
				{

					temp_cizu.word[a]='\0';//
					a--;
				}

				int h, j = t;
				for (h = 0; h < j; h++)//相同的词个数累加
				{
					if (strcmp(temp_cizu.word,cizu[h].word) == 0)//

					{
						cizu[h].count++;
						if (w == 1)cizu[h].count += 9;
						break;
					}
				}

				if (t == 0 || h == j)//新词生成新的空间
				{
					cizu[t] = temp_cizu;
					t++;
				}
			}
			else continue;
		}
		else continue;
	}

	//扫描Abstract
	string *ci2 = new string[1000000];

	int kk = 0;
	int le2 = v.length();
	for (int i = 0; i < le2; i++)//存入所有的词和字符
	{

		if ((v[i] >= 'a'&&v[i] <= 'z') || (v[i] >= 'A'&&v[i] <= 'Z') || (v[i] >= '0'&&v[i] <= '9'))//第一个是字母或数字
		{

			while ((v[i] >= 'a'&&v[i] <= 'z') || (v[i] >= 'A'&&v[i] <= 'Z') || (v[i] >= '0'&&v[i] <= '9'))
			{
				if (v[i] >= 'A'&&v[i] <= 'Z')
					v[i] += 32;

				ci2[kk] += v[i];
				i++;
			}
			while (!(v[i] >= 'a'&&v[i] <= 'z') && !(v[i] >= 'A'&&v[i] <= 'Z') && !(v[i] >= '0'&&v[i] <= '9') && v[i] != '\n'&&i < le2)
			{
				ci2[kk] += v[i];
				i++;
			}
			if (v[i] == '\n')ci2[++kk] = '\n';//换行符单独存

			i--;
			kk++;
		}
		else continue;
	}

	for (int i = 0; i < kk; i++)
	{
		int flag1 = 0;
		int flag2 = 0;

		for (int j = 0; j < 4; j++)
		{
			if (!(ci2[i][j] >= 'a'&& ci2[i][j] <= 'z'))
			{
				flag2 = 1;//判断第一个是否符合单词规范
				break;
			}
		}

		if (flag2 == 0)//第一个符合
		{
			strcpy_s(temp_cizu.word, 500, ci2[i].c_str());
			temp_cizu.count = 1;

			for (int j = 1; j < m; j++)
			{
				int flag3 = 0;
				for (int f = 0; f < 4; f++)
				{
					if (!(ci2[i + j][f] >= 'a'&& ci2[i + j][f] <= 'z'))
					{
						flag3 = 1;//判断后几个是否符合单词规范
						i = i + j;
						break;
					}
				}

				if (flag3 == 0)//后几个都合法
				     strcat_s(temp_cizu.word, 500, ci2[i + j].c_str());//
				else { flag1 = 1; break; }
			}

			if (flag1 == 0) //插入
			{
				int a = strlen(temp_cizu.word)  - 1;//去掉结尾的符号

				while (!(temp_cizu.word[a] >= 'a'&&temp_cizu.word[a] <= 'z') && !(temp_cizu.word[a] >= '0'&&temp_cizu.word[a] <= '9'))
				{

					temp_cizu.word[a] = '\0';//
					a--;
				}

				int h, j = t;
				for (h = 0; h < j; h++)//相同的词个数累加
				{
					if (strcmp(temp_cizu.word, cizu[h].word) == 0) 

					{
						cizu[h].count++;

						break;
					}


				}

				if (t == 0 || h == j)//新词生成新的空间

				{
					cizu[t] = temp_cizu;

					t++;
				}
			}
			else continue;
		}
		else continue;
	}


	//放入优先队列

	for (int i = 0; i < t; i++)
	{
		tmp.push(cizu[i]);
	}

}

void MyCount::TitleAndAbstract(string filename)
{
	char ch;
	ifstream fin;
	fin.open(filename);//打开文件

	if (!fin)
	{
		cout << "can not open file" << endl;
	}

	while (!fin.eof())
	{
		ch = fin.get();
		if (ch == '\n')
		{
			ch = fin.get();
			if (ch == 'T')
			{
				for (int i = 0; i <= 6; i++)
					ch = fin.get();

				while (ch != '\n')
				{
					title_str += ch;
					ch = fin.get();
				}
				title_str += ch;
			}
		
		}
		if (ch == '\n')
		{
			ch = fin.get();
			if (ch == 'A')
			{
				for (int i = 0; i < 10; i++)
					ch = fin.get();

				while (ch != '\n' && !fin.eof())
				{
					abstract_str += ch;
					ch = fin.get();
				}
				if (ch == '\n')
					abstract_str += ch;
			}

		}

	}
	fin.close();
}
string MyCount::get_abstract()
{
	return abstract_str;
}

string MyCount::get_title()
{
	return title_str;
}

void MyCount::print(string outfile, string str, int n)//输出到文件
{
	int x = 0;
	ofstream outf;
	outf.open(outfile);

	outf << "characters: " << countChars(str) << endl;
	outf << "words: " << countWords(str) << endl;
	outf << "lines: " << countLines(str) << endl;

	while (!tmp.empty() && x < n)//输出前n个单词
	{
		outf << "<" << tmp.top().word << ">: " << tmp.top().count << endl;
		tmp.pop();
		x++;
	}
	outf.close();
}