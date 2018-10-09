#include "stdafx.h"
#include "AnalyzeArguments.h"

string inputFile="input.txt";
string outputFile="result.txt";
bool weightOnWord=1;
int phraseLen = 3;
int topN = 10;
bool _m=0;

int AnalyseParameter(char **argv)
{
	bool _i=0, _o=0, _w = 0;
	int id = 1;
	while (argv[id] != NULL) {
		if (strcmp(argv[id], "-i") == 0) {
			if (argv[id + 1] != NULL) {
				inputFile = argv[id + 1];
				_i = 1;
			}
			else {
				cout << "parameter error." << endl;
				return 0;
			}
			id += 2;
		}
		else if (strcmp(argv[id], "-o") == 0) {
			if (argv[id + 1] != NULL) {
				outputFile = argv[id + 1];
				_o = 1;
			}
			else {
				cout << "parameter error." << endl;
				return 0;
			}
			id += 2;
		}
		else if (strcmp(argv[id], "-m") == 0) {
			_m = 1;
			if (argv[id + 1] != NULL) {
				phraseLen = atoi(argv[id + 1]);
			}
			else {
				cout << "parameter error." << endl;
				return 0;
			}
			id += 2;
		}
		else if (strcmp(argv[id], "-n") == 0) {
			if (argv[id + 1] != NULL) {
				topN = atoi(argv[id + 1]);
			}
			else {
				cout << "parameter error." << endl;
				return 0;
			}
			id += 2;
		}
		else if (strcmp(argv[id], "-w") == 0) {
			if (argv[id + 1] != NULL) {
				weightOnWord = atoi(argv[id + 1]);
				_w = 1;
			}
			else {
				cout << "parameter error." << endl;
				return 0;
			}
			id += 2;
		}
		else {
			cout << "parameter error." << endl;
			return 0;
		}
	}

	return (_i && _o && _w);
}

