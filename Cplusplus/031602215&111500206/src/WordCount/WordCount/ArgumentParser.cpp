#include "ArgumentParser.h"

extern std::string inputFileName;
extern std::string outputFileName;
extern int weightFrequencyOn;
extern int phraseFrequencyOn;
extern int phraseLength;
extern int topNWords;

bool stringIsNum(string str);
bool stringIsNum(string str)
{
	stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d))
		return false;
	if (sin >> c)
		return false;
	return true;
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
				return -2;
			}
			outputFileName = argv[i + 1];
			i += 2;
		}

		else if (strcmp(argv[i], "-w") == 0)
		{
			if (argv[i + 1] == NULL) {
				printf("error: -w must follow 0 or 1!\n");
				return -3;
			}
			int num = (argv[i + 1][0] - '0'); // strcmp
			if (num != 0 && num != 1) {
				printf("error: -w must follow 0 or 1!\n");
				return -4;
			}
			weightFrequencyOn = num;
			i += 2;
		}
		else if (strcmp(argv[i], "-m") == 0)
		{
			if (argv[i + 1] == NULL) {
				printf("error: -m must follow a number!\n");
				return -5;
			}
			int num = (argv[i + 1][0] - '0'); // todo
			if (num <= 0) {
				printf("error: -w must follow a positive integer!\n");
				return -6;
			}
			phraseFrequencyOn = 1;
			phraseLength = num;
			i += 2;
		}
		else if (strcmp(argv[i], "-n") == 0)
		{
			if (argv[i + 1] == NULL) {
				printf("error: -m must follow a number!\n");
				return -7;
			}
			string num = argv[i + 1];
			std::string::size_type sz;
			topNWords = std::stoi(num, &sz);
			i += 2;
		}
	}
	return 0;
}
