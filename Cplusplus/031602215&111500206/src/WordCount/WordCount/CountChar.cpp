#include "CountChar.h"

int CountChar(std::string line)
{
	int size = line.size();

	int count = 0;

	for (int i = 0; i < size; i++)  // Don't consider non-ascii characters here.
		if (isascii(line[i]))
			count++;

	return count + 1;  // '\n' in the end of a line.
}
