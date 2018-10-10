#include "stdafx.h"
#include "Parameter.h"
using namespace std;

void Parameter::set()//设置初值
{
	i = -1;
	m = -1;
	n = -1;
	w = -1;
	o = -1;
}
void Parameter::get_Parameter(int argc, char *argv[])//提取参数
{
	for (int j = 0; j <= argc - 1; j++)//提取命令行参数
	{
		//cout << argv[j] << endl;
		if (strcmp(argv[j], "-i") == 0)
		{
			i = j + 1;
			//cout << argv[i] << endl;
		}
		if (strcmp(argv[j], "-o") == 0)
		{
			o = j + 1;
			//cout << argv[o] << endl;
		}
		if (strcmp(argv[j], "-w") == 0)
		{
			w = atoi(argv[j + 1]);
			//cout << "w=" << w << "   " << endl;
		}
		if (strcmp(argv[j], "-m") == 0)
		{
			m = atoi(argv[j + 1]);
			//cout << "m=" << m << "   " << endl;
		}
		if (strcmp(argv[j], "-n") == 0)
		{
			n = atoi(argv[j + 1]);
			//cout << "n=" << n << "   " << endl;
		}
	}
	if (o == -1 || i == -1 || w == -1)//检测输入的命令行参数是否正确
	{
		cout << "输入参数错误！" << endl;
		exit(1);
	}
}

