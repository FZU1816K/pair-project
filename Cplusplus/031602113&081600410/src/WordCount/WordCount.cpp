#define _CRT_SECURE_NO_DEPRECATE
/*#include"CharCount.h"
#include"LineCount.h"
#include"WordCount.h"
#include"Frequency.h"
#include"w-phase.h"
#include"phrase.h"
#include"w-frequency.h"
#include"cmp.h"*/
#include"all.h"
#include<math.h>




int main(int argc, char** argv) {
	char input[100];
	char output[100];
	int times = 10;
	int weight = 0;
	int m = 0;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'i') {
				strcpy(input, argv[i + 1]);
				i++;
			}
			else if (argv[i][1] == 'o') {
				strcpy(output, argv[i + 1]);
				i++;
			}
			else if (argv[i][1] == 'w')
			{
				if (argv[i + 1][0] == '0')
					weight = 0;
				else if (argv[i + 1][0] == '1')
					weight = 1;
				i++;
			}
			else if (argv[i][1] == 'n') {
				int len = int(strlen(argv[i + 1]));
				times = 0;
				for (int j = len - 1; j >= 0; j--) {
					if ('0' <= argv[i + 1][j] && argv[i + 1][j] <= '9') {
						times += (argv[i + 1][j] - '0')*int(pow(10, len - 1 - j));
					}
				}
				i++;
			}
			else if (argv[i][1] == 'm') {
				int len = int(strlen(argv[i + 1]));
				for (int j = len - 1; j >= 0; j--) {
					if ('0' <= argv[i + 1][j] && argv[i + 1][j] <= '9') {
						m += (argv[i + 1][j] - '0')*int(pow(10, len - 1 - j));
					}
				}

				i++;
			}
		}
	}
	charCount(input, output);
	wordCount(input, output);
	lineCount(input, output);
	if (m != 0) {
		p_frequency(weight,times, m, input, output);
	}
	else
		frequency(weight, times, input, output);

	return 0;
}