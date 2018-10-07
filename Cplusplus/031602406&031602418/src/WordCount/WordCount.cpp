#include<iostream>
#include"WordCountFunction.h"
#include<fstream>
#include<string>
using namespace std;

vector<pair<string, int>> VM;
void topTen1()
{

	for (auto it = My.begin(); it != My.end(); it++)
	{
		VM.push_back(make_pair(it->first, it->second));
	}
	sort(VM.begin(), VM.end(), [](const pair<string, int> &x, const pair<string, int>&y)->int {return x.second > y.second; });
	int c = 0;
}
void topTen2()
{
	for (auto it = My3.begin(); it != My3.end(); it++)
	{
		VM.push_back(make_pair(it->first, it->second));
	}
	sort(VM.begin(), VM.end(), [](const pair<string, int> &x, const pair<string, int>&y)->int {return x.second > y.second; });
	int c = 0;
}

int main(int argc, char* argv[])
{
	if (argc == 0)
	{
		cout << "Error:argc=0!" << endl;
		exit(1);
	}
	else if (argc == 1)
	{
		cout << "Error:argc=1!" << endl;
		exit(1);
	}

	ifstream in;
	ofstream out;
	int weight = 0;
	int nt = argc;
	int i = 0;
	int topn = 10;
	int cpw = 0;//词组长度
	for (i = 0; i < nt; i++)
	{
		if ((**(argv + i)) == '-')
		{
			switch (*(*(argv + i) + 1))
			{
			case 'i':
				in.open(argv[i + 1]);
				break;
			case 'o':
				out.open(argv[i + 1]);
				break;
			case 'w': //权重
				if (argv[i + 1] == "1")
					weight = 1;
				else
					weight = 0;
				break;
			case 'n':  //前n多频率
				sscanf(argv[i + 1], "%d", &topn);//字符串数字转int

				/*if (strlen(argv[i + 1]) == 1)
				 {
					 topn = atoi(argv[i + 1]);
				 }
					 else if (strlen(argv[i + 1]) == 2)
					 {
						 topn = atoi(*(*argv + i)) * 10 + atoi(*(*argv + i) + 1);
					 }
					 topn = atoi(argv[i + 1]);*/
				break;
			case 'm':  //词组长度
				sscanf(argv[i + 1], "%d", &cpw);
				/*if (strlen(argv[i + 1]) == 1)
				{
				cpw = atoi(argv[i + 1]);
				}
				else if (strlen(argv[i + 1]) == 2)
				{
				cpw = 10;
				}*/
				break;
			}
		}
	}

	//in.open(argv[1]);
	if (in.fail())
	{
		cout << "open input file failed!" << endl;
		exit(1);
	}
	if (!out.is_open())
	{
		cout << "open output file error!";
		exit(1);
	}
	if (in.is_open())
	{
		WordCount f;
		//out.open("result.txt");
		f.count1(in);

		if (cpw == 0)//不是词组统计
		{
			f.count2(in, weight); topTen1();
		}
		else//词组统计
		{
			f.count3(in, cpw); topTen2();
		}
		out << "characters: " << f.numChar << endl;
		out << "words: " << f.numWords << endl;
		out << "lines:" << f.numLines << endl;

		int c = 0;
		for (auto it = VM.begin(); c < topn; it++, c++)
		{
			cout << "<" << it->first << ">" << ": " << it->second << endl;
			out << "<" << it->first << ">" << ": " << it->second << endl;
		}
	}

	in.close();
	out.close();
	return 0;
}