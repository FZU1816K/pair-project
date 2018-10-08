#include "CountChar.h"
#include "CountChar.h"
#include <iostream>
#include "pch.h"
#include <fstream>
using namespace std;
using namespace std;
extern int charAmount;
void CountChar(string filename)
{
	fstream file(filename);
	int cnt = 0;
	char temp;
	while (file.get(temp))
	{

		cnt++;

	}
	charAmount = cnt;
}