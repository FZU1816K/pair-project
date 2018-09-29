#include "arg_handle.h"
#include "pch.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;


extern int inputPos;
extern string inputFilename;
extern int outputPos;
extern string outputFilename;
extern int weightPos;
extern bool weightBool;
extern int phrasePos; // 词组长度参数
extern int phraseLen;
extern int topNPos;
extern int topN;

bool isNum(string str)
{
	stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d))
	{
		return false;
	}
	if (sin >> c)
	{
		return false;
	}
	return true;
}

int Argv_handle(char **argv) //return 0 -everything is ok,-1 something wrong
{
	
	
	inputPos = 9;
	int idx = 1;
	while (argv[idx]!=NULL)
	{
		if (strcmp(argv[idx], "-i") == 0)
		{
			if (argv[idx+1] != NULL)//next_argment_detect
			{
				inputFilename = argv[idx + 1];
			}
			idx+=2;
		}
		
		else if (strcmp(argv[idx], "-o") == 0)
		{
			if (argv[idx + 1] != NULL)//next_argment_detect
			{
				outputFilename = argv[idx + 1];
			}
			idx += 2;
		}
		
		
		else if (strcmp(argv[idx], "-w") == 0)
		{
			char * temp = argv[idx + 1];
			int t = atoi(temp);
			if (t==0||t==1)//next_argment_detect
			{
				weightBool = t;
			}
			idx += 2;
		}
		
		else if(strcmp(argv[idx], "-m") == 0)
		{
			if (argv[idx + 1] == NULL)
			{
				
			}
			bool isNumber = isNum(argv[idx + 1]);
			int t = atoi(argv[idx]);
			if (!isNumber)
			{
				//error
			}
			phraseLen = t;
			idx += 2;
		}

		else if (strcmp(argv[idx], "-n") == 0)
		{
			if (argv[idx + 1] == NULL)
			{
				//error
			}
			bool isNubmer = isNum(argv[idx + 1]);

			int t = atoi(argv[idx + 1]);
			if (t <= 0)
			{
				//error
			}
			topN = t;
			idx += 2;
		}
		else
		{
			printf("error usage.\n");
		}
	}
	return 0;
}