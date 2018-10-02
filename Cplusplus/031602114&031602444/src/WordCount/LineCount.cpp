#include"pch.h"
#include"LineCount.h"
using namespace std;

int LineCount(char *filename)
{
	int line_cnt = 0;
	int flag = 0;
	string str;
	char ch_tmp;
	fstream f_tmp;
	f_tmp.open(filename);
	if (!f_tmp)
	{
		cout << "Can't open file :" << filename << "\nUsage:countch filename" << endl;
		exit(0);
	}
	while (!f_tmp.eof())
	{
		getline(f_tmp, str);
		int str_len = str.length();
		if ((str[0] >= '0' && str[0] <= '9') && (str[str_len - 1] >= '0' && str[str_len - 1] <= '9'))			//将编号行排除在行数统计中
		{
			continue;
		}
		if (str_len == 0)
		{
			continue;
		}
		else
		{
			line_cnt++;
		}
	}
	f_tmp.close();
	return line_cnt;
}