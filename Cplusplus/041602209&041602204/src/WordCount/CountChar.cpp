#include"CountChar.h"

int CountChar(string filename)
{
	int cnt = 0, n = 0;
	char c;
	string temp;
	ifstream fin(filename, ios::in);
	if (!fin)
	{
		return -1;
	}
	while (fin.get(c))
	{
		cnt++;
		if (c == '\n')n++;
	}
	fin.close();
	return cnt-(n/5)*21;
}