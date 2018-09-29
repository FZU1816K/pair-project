#pragma once
#include <string>

using namespace std;

int inputPos;
string inputFilename;
int outputPos;
string outputFilename;
int weightPos;
bool weightBool;
int phrasePos; // 词组长度参数
int phraseLen;
int topNPos;
int topN;

int Argv_handle(char **argv); // string 0~9 stand for -i, in.txt, -o , out.txt , w , 0|1, m , num , n , num

