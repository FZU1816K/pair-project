#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cassert>
#include <algorithm>
#include "Dll1.h"
#pragma comment(lib, "Dll1.lib")
#include "CountChars.h"
#include "CountLines.h"
#include "CountWF.h"
#include "CountWords.h"
#include <stdlib.h>
using namespace std;

int main(int argc, char **argv)
{
	int in_Pid = 0, out_Pid = 0;														//输入输出文件标识
	int weight_Pid=0;																		//权重标识符
	int itemLenth = 1;
	int i = 1;
	int topNum = 10;
	string a = "-i", b = "-o", c = "-w",d = "-m",e = "-n";
	while (argv[i])
	{
		if (argv[i] == a) in_Pid = i + 1;												//传入输入文件参数
		if (argv[i] == b) out_Pid = i + 1;												//传入输出文件参数
		if (argv[i] == c)                                                                               
		{ 
			string a = argv[i + 1]; 
			weight_Pid = a[0] - '0'; 
		}
		if(argv[i] == d)itemLenth = atoi(argv[i + 1]);									//传入词项长度参数
		if (argv[i] == e)topNum = atoi(argv[i + 1]);
		i++;
	}
	ifstream in(argv[in_Pid]);	//  打开文件
	if (!in)
	{
		cerr << "无法打开输入文件" << endl;
		return -1;
	}
	ofstream fout(argv[out_Pid]);

	
	int LineNum = CountLines(argv[in_Pid]);
	int CharNum = CountChars(argv[in_Pid]);
	int WordNum = CountWords(argv[in_Pid]);
	fout << "characters: " << CharNum << endl << "words: " << WordNum << endl << "lines: " << LineNum << endl;
	fout.close();
	
	CountWF(argv[in_Pid],fout,argv[out_Pid],topNum,itemLenth,weight_Pid);
	return 0;
}