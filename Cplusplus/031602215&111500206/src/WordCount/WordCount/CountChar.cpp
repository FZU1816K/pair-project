#include "CountChar.h"

int CountChar(std::string line)
{
	int size = line.size();

	int count = 0;

	for (int i = 0; i < size; i++)  // 需要跳过非 ASCII 字符
		if (isascii(line[i]))
			count++;

	return count + 1;
}
