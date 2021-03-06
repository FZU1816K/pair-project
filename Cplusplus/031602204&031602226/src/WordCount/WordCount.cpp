// WordCount.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

string vv, s;
char *txi = nullptr;
string txo;
int num = 10, m;
int bo = 0;

int main(int c, char **v)
{
	if (c < 2)
		return 0;

	int i = 1;

	while (i < c)
	{
		vv = v[i];
		if (vv == "-i")
		{
			//传v[i+1]，它是输入路径
			txi = v[i + 1];
			i += 2;
			continue;
		}
		if (vv == "-o")
		{
			//传v[i+1]，它是输出路径
			txo = v[i + 1];
			i += 2;
			continue;
		}
		if (vv == "-w")
		{
			s = v[i + 1];
			//传v[i+1],它是权重
			if (s == "1")
				bo = 1;
			i += 2;
			continue;
		}
		if (vv == "-m")
		{
			//传v[i+1]它是词数
			m = atoi(v[i + 1]);
			i += 2;
			continue;
		}
		if (vv == "-n")
		{
			//传v[i+1],它是输出个数
			num = atoi(v[i + 1]);
			i += 2;
			continue;
		}
	}
	charcount(txi, txo);
	wordcount(txi, txo, bo);
	linecount(txi, txo);
	wordmax(txi, txo, num, m);

	return 0;
}
