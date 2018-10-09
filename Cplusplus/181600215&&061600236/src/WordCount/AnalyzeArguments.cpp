#include "stdafx.h"
#include "AnalyzeArguments.h"

string inputFile="input7.txt";
string outputFile="rsult.txt";
int phraseLen=3;
int topN=10;
bool weightOnWord=0;

int AnalyseParameter(char **argv)
{
	int id = 1;
	while (argv[id] != NULL) {
		cout << id<<" "<<argv[id] << endl;
		if (strcmp(argv[id], "-i") == 0) {
			if (argv[id + 1] != NULL) {
				inputFile = argv[id + 1];
			}
			else {
				cout << "parameter error." << endl;
				return -1;
			}
			id += 2;
		}
		else if (strcmp(argv[id], "-o") == 0) {
			if (argv[id + 1] != NULL) {
				outputFile = argv[id + 1];
			}
			else {
				cout << "parameter error." << endl;
				return -1;
			}
			id += 2;
		}
		else if (strcmp(argv[id], "-m") == 0) {
			if (argv[id + 1] != NULL) {
				phraseLen = atoi(argv[id + 1]);
			}
			else {
				cout << "parameter error." << endl;
				return -1;
			}
			id += 2;
		}
		else if (strcmp(argv[id], "-n") == 0) {
			if (argv[id + 1] != NULL) {
				topN = atoi(argv[id + 1]);
			}
			else {
				cout << "parameter error." << endl;
				return -1;
			}
			id += 2;
		}
		else if (strcmp(argv[id], "-w") == 0) {
			if (argv[id + 1] != NULL) {
				if (atoi(argv[id + 1]) == 1) {
					weightOnWord = 1;
				}
			}
			else {
				cout << "parameter error." << endl;
				return -1;
			}
			id += 2;
		}
		else {
			cout << "parameter error." << endl;
			return -1;
		}

		return 1;
	}
	
	return 1;
}

