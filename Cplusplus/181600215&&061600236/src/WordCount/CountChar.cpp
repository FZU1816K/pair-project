#include "stdafx.h"
#include "CountChar.h"

//count the number of characters in a line
int CountChar(string oneLine)
{
	int cnt = 0;
	int len = oneLine.size();
	for (int i = 0; i < len; i++) {
		if (isascii(oneLine[i])) {  
			cnt++;
		}
	}

	return cnt + 1; 
}