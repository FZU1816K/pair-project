#include "CountChar.h"

int CountChar(std::string line)
{
	int size = line.size();

	int count = 0;

	for (int i = 0; i < size; i++)  // ��Ҫ������ ASCII �ַ�
		if (isascii(line[i]))
			count++;

	return count + 1;
}
