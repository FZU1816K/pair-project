#include "stdafx.h"
#include "CountChar.h"

int CountChar(string filename)
{
	int count = 0;
	ifstream file(filename);
	char ch;
	while ((ch = file.get()) != EOF) count++;
	file.close();

	return count;
}