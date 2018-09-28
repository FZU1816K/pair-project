#include<iostream>
#include<queue>
#include<fstream>
#include<cctype>
#include<algorithm>
#include "Phrase.h"
using namespace std;


Psort::Psort()
{
	finname = "input.txt";
	foutname = "result.txt";
	len = 2;
	num = 10;
}

Psort::Psort(string filein, string fileout, int length, int number)
{
	finname = filein;
	foutname = fileout;
	len = length;
	num = number;
}


typedef pair<string, int> PAIR;

struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second > rhs.second;
	}
};

/*************************************************/
 //为了测试而额外写的函数，实际并不需要
bool Psort::get_empty()
{
	return phrase_v.empty();
}

int Psort::get()
{
	return phrase_v.at(0).second;
}
/*************************************************/

void Psort::PS()
{
	queue<string> phrase_t;                  //title的词组
	queue<string> phrase_a;                  //abstract的词组
	short int flag = -1;                       //标志是title的还是abstract的
	ifstream fin;
	fin.open(finname);
	if (!fin.is_open())
	{
		cerr << "Could not open " << finname << endl;
		fin.clear();
	}
	string word;
	char c;
	fin >> noskipws; //不放过一个字符
	while (fin.good())
	{
		fin >> c;
		if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)) //是字母数字
		{
			if (c >= 65 && c <= 90)
				c += 32;
			word.push_back(c);
		}
		else //判断能否组成单词,顺便加入词组队列中
		{
			if (word.length() >= 4)
			{
				/**********************是单词******************************/
				if ((word[0] >= 97 && word[0] <= 122) && (word[1] >= 97 && word[1] <= 122) && (word[2] >= 97 && word[2] <= 122) && (word[3] >= 97 && word[3] <= 122))
				{
					if (word == "title")
					{
						flag = 0;
						phrase_a.push("\0");
					}
					else if (word == "abstract")
					{
						flag = 1;
						phrase_t.push("\0");
					}
					else
					{
						if (flag == 0)
							phrase_t.push(word);
						else if (flag == 1)
							phrase_a.push(word);
					}
				}
				else
				{
					if (flag == 0)
						phrase_t.push("\0");
					else if (flag == 1)
						phrase_a.push("\0");
				}
			}
			else
			{
				if (flag == 0)
					phrase_t.push("\0");
				else if (flag == 1)
					phrase_a.push("\0");
			}
			word = "";
		}
	}
	if (fin.eof()) {}
	else if (fin.fail())
		printf("Input terminated by data mismatch.\n");
	else
		printf("Input terminated for unknown reason.\n");
	fin.close();


	//*****************处理词组************************//
	std::map<std::string, size_t> phrase_count;
	string P = "";      //暂存词组的

	///////////////////////////title////////////////////////////////
	short int start = 0;
	string::size_type p = NULL;

	while (!phrase_t.empty())
	{
		if (start == 1)
		{
			p = P.find(" ") + 1;
			P = P.substr(p);      //把首个单词加上" "去掉
			if (phrase_t.front() == "\0")
			{
				start = 0;
				phrase_t.pop();
				continue;
			}
			else
			{
				P.append(" " + phrase_t.front());
				phrase_t.pop();
				++phrase_count[P];
			}
		}
		else   //第一次构建或者长度不够重新构建
		{
			P = "";
			short int l = len;
			flag = 1;    //之前的flag复用，用来判断词组是否足够长
			while (l--)
			{
				if (phrase_t.front() == "\0")
				{
					flag = 0;
					phrase_t.pop();
					break;
				}
				else
				{
					P.append(phrase_t.front() + " ");
					phrase_t.pop();
				}
			}
			if (flag == 1)
			{
				P = P.substr(0, P.length() - 1);  //词组最后的" "要处理
				++phrase_count[P];
				start = 1;
			}
		}

	}

	/////////////////////////abstract/////////////////////////////////
	start = 0;
	p = NULL;
	P = "";
	while (!phrase_a.empty())
	{
		if (start == 1)
		{
			p = P.find(" ") + 1;
			P = P.substr(p);      //把首个单词加上" "去掉
			if (phrase_a.front() == "\0")
			{
				start = 0;
				phrase_a.pop();
				continue;
			}
			else
			{
				P.append(" " + phrase_a.front());
				phrase_a.pop();
				++phrase_count[P];
			}
		}
		else   //第一次构建或者长度不够重新构建
		{
			P = "";
			short int l = len;
			flag = 1;    //之前的flag复用，用来判断词组是否足够长
			while (l--)
			{
				if (phrase_a.front() == "\0")
				{
					flag = 0;
					phrase_a.pop();
					break;
				}
				else
				{
					P.append(phrase_a.front() + " ");
					phrase_a.pop();
				}
			}
			if (flag == 1)
			{
				P = P.substr(0, P.length() - 1);  //词组最后的" "要处理
				++phrase_count[P];
				start = 1;
			}
		}

	}

	//*********排序**********//
	vector<PAIR>phrase_v1(phrase_count.begin(), phrase_count.end());
	sort(phrase_v1.begin(), phrase_v1.end(), CmpByValue());
	phrase_v = phrase_v1;
}


void Psort::show()
{
	for (int i = 0; i < phrase_v.size() && i < num; i++)
		cout << "<" << phrase_v.at(i).first << ">: " << phrase_v.at(i).second << endl;
}

void Psort::fwrite()
{
	ofstream fout;
	fout.open(foutname, ios::out | ios::app); //追加
	if (!fout.is_open())
	{
		cerr << "Cant't open" << foutname << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < phrase_v.size() && i < num; i++)
		fout << "<" << phrase_v.at(i).first << ">: " << phrase_v.at(i).second << endl;
	fout.close();
}