#include"CountLine.h"

int CountLine(string filename)
{
	ifstream File;
	int n = 0;
	string temp;
	File.open(filename, ios::in);//ios::in 表示以只读的方式读取文件
	if (File.fail())//文件打开失败:返回0
	{
		return -1;
	}
	else//文件存在
	{
		while (getline(File, temp))
		{   //   if(temp[0]!='\n')
		//  实验站	cout << temp[0] << endl;
			n++;
		}
		return n - ((n+2) / 5) * 3;
	}
	File.close();

}