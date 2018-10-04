#include "ArgumentParser.h"

extern std::string inputFileName;
extern std::string outputFileName;
extern int weightFrequencyOn;
extern int phraseFrequencyOn;
extern int phraseLength;
extern int topNWords;

bool stringIsNum(string str)
{
	stringstream sin(str);
	int d;
	if ((sin >> d))
		return true;
	else return false;
}

int stringIsPositiveInteger(string str)
{
	stringstream sin(str);
	int d;

	if (!(sin >> d)) // not a integer
		return -1;

	std::string::size_type sz;
	int res = std::stoi(str, &sz);
	if (res > 0)
		return res;

	return -1; // zero or a negetive integer
}

int Parse_Args(int argc, char ** argv)
{
	int i = 1; // skip WordCount.exe

	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			if (argv[i + 1] == NULL) {
				printf("error: no input file name!\n");
				return -1;
			}
			inputFileName = argv[i + 1];
			i += 2;
		}
		else if (strcmp(argv[i], "-o") == 0)
		{
			if (argv[i + 1] == NULL) {
				printf("error: no output file name!\n");
				return -1;
			}
			outputFileName = argv[i + 1];
			i += 2;
		}

		else if (strcmp(argv[i], "-w") == 0)
		{
			if (argv[i + 1] == NULL) {
				printf("error: -w must follow 0 or 1!\n");
				return -1;
			}
			bool isOneOrZero = (strcmp(argv[i + 1], "1") || strcmp(argv[i + 1], "0"));
			if (!isOneOrZero) {
				printf("error: -w must follow 0 or 1!\n");
				return -1;
			}
			int num = atoi(argv[i + 1]);
			weightFrequencyOn = num;
			i += 2;
		}

		else if (strcmp(argv[i], "-m") == 0)
		{
			if (argv[i + 1] == NULL) {
				printf("error: -m must follow a positive Integer!\n");
				return -1;
			}
			int res = stringIsPositiveInteger(argv[i + 1]);
			if (res == -1) {
				printf("error: -m must follow a positive Integer!\n");
				return -1;
			}
			phraseFrequencyOn = 1;
			phraseLength = res;
			i += 2;
		}
		else if (strcmp(argv[i], "-n") == 0)
		{
			if (argv[i + 1] == NULL) {
				printf("error: -n must follow a positive Integer!\n");
				return -1;
			}
			int res = stringIsPositiveInteger(argv[i + 1]);
			if (res == -1) {
				printf("error: -n must follow a positive Integer!\n");
				return -1;
			}
			topNWords = res;
			i += 2;
		}
	}
	return 0;
}
