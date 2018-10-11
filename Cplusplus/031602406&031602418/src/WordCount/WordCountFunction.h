#pragma once
#include<sstream>
#include<fstream>
#include<iterator>
#include<cctype>
#include<unordered_map>
#include<vector>
#include<algorithm>
#include<string>
#include<string.h>
#include<stdlib.h>
using namespace std;
unordered_map<string, int>My;
unordered_map<string, int>My3;
/*bool letter(char ch)
{
if (ch >= 'a'&&ch <= 'z')
return true;
else if (ch >= 'A'&&ch <= 'Z')
return true;
else
return false;
}*/
bool digit(char ch)
{
if (ch >= '0'&&ch <= '9')
return true;
else
return false;
}

class WordCount
{
public:
	int numChar = 0;
	int numWords = 0;
	int numLines = 0;
	void count1(ifstream& in)  //统计字符数和行数
	{
		char ch;
		bool fg = true;
		bool isdig = false;
		while ((ch = in.get()) != EOF)
		{
			numChar++;
			if(digit(ch))
			{
				isdig=true;
			}
			if ((!isdig)&&ch != '\n'&&ch != '\t'&&ch != ' '&&fg == true)
			{
				numLines++;
				fg = false;
			}
			if (ch == '\n')
			{
				if (!fg)
				{
					numLines++;
					fg = true;
				}
			}
			isdig = false;
		}
		in.clear();//清空并回移指针
		in.seekg(0);
	}

	void count2(ifstream& in, int weight)  //带权值词频统计
	{
		string ss;
		string str;
		string stemp, temp;
		while (getline(in, str))
		{
			str.append(temp);
			temp.clear();
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == '\n')
					str[i] = ' ';
				if (ispunct(str[i]))
					str[i] = ' ';
			}
			stringstream ss(str);

			int sg;
			while (ss >> stemp)
			{
				if (stemp == "Title")
				{
					sg = 1;
				}
				if (stemp == "Abstract")
				{
					sg = 2;
				}
				for (int i = 0; i < stemp.length(); i++)
				{
					if ('A' < stemp[i] && stemp[i] < 'Z')
						stemp[i] += 32;
				}
				if (stemp == "title" || stemp == "abstract")
					continue;
				if (stemp.length() < 4)
				{
					continue;
				}
				if ((stemp[0]>'z' || stemp[0]<'a' || stemp[1]>'z' || stemp[1]<'a' || stemp[2]>'z' || stemp[2]<'a' || stemp[3]>'z' || stemp[3]<'a'))
				{
					continue;
				}
				numWords++;


				unordered_map<string, int>::iterator it = My.find(stemp);
					if (weight == 1) //有权值
					{
						if (it == My.end())
						{
							if (sg == 1)
							{
								My.insert(unordered_map<string, int>::value_type(stemp, 10));
							}
							if (sg == 2)
							{
								My.insert(unordered_map<string, int>::value_type(stemp, 1));
							}

						}
						else
						{
							if (sg == 1)
							{
								My[stemp] += 10;
							}
							if (sg == 2)
							{
								My[stemp]++;
							}
						}
					}
				if (weight == 0)//无权值
				{
					if (it == My.end())
					{
						My.insert(unordered_map<string, int>::value_type(stemp, 1));
					}
					else
					{
						My[stemp]++;
					}
				}
			}
		}

	}

	void count3(ifstream& in, int cpw)
	{
		string ss;
		string str;
		string stemp, temp;
		string cpwtp;//词组
		string strarr[10000];
		int strnum;
		//char ct[10000][100];
		while (getline(in, str))//读取一行
		{
			str.append(temp);
			temp.clear();
			strnum = 0;
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == '\n')
					str[i] = ' ';
				if (ispunct(str[i]))
					str[i] = ' ';
			}
			stringstream ss(str);
			while (ss >> stemp) //逐个读取单词
			{
				for (int i = 0; i < stemp.length(); i++)
				{
					if ('A' < stemp[i] && stemp[i] < 'Z')
						stemp[i] += 32;
				}
				if (stemp == "title" || stemp == "abstract")
					continue;
				if (stemp.length() < 4)
				{
					continue;
				}
				if ((stemp[0]>'z' || stemp[0]<'a' || stemp[1]>'z' || stemp[1]<'a' || stemp[2]>'z' || stemp[2]<'a' || stemp[3]>'z' || stemp[3]<'a'))
				{
					continue;
				}
				numWords++;
				strarr[strnum] = stemp;//将每一行的单词逐个存入字符串数组中
				//ct[strnum][100] = stemp;
				strnum++;
			}
			int pn = 0;
			for (int i = 0; i < strnum - cpw + 1; i++) //遍历strarr,每cpw个单词合并
			{
				cpwtp = "";
				for (int j = 0; j < cpw; j++)
				{
					//string tstrtp= ct[i + j + 1][100] ;
					//cpwtp+=tstrtp(ct[i+j+1][]);
					//cpwtp += tstrtp;
					cpwtp += strarr[i + j];
					if (j != cpw - 1)
						cpwtp += ' ';
				}
				unordered_map<string, int>::iterator it = My3.find(cpwtp);
				if (it == My3.end())
				{
					My3.insert(unordered_map<string, int>::value_type(cpwtp, 1));
				}
				else
				{
					My3[cpwtp]++;
				}
				for (int z = 0; z < 10000; z++)
					strarr[z].clear();
			}
		}
	}
};