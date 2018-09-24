#pragma once
#include <string>

// 命令行参数会改变的环境变量

std::string inputFileName = "result.txt";
std::string outputFileName = "output.txt";
int weightFrequencyOn = 0;
int phraseFrequencyOn = 0;
int phraseLength = 0;
int topNWords = 10;

#define TITLE 1
#define ABSTRACT 2
#define NONWEIGHT 3

/*
extern string inputFileName;  // -i <input.txt> : define input file
extern string outputFileName; // -o <result.txt>: define output file
extern int weightFrequencyOn; // -w [0|1] : words in title count 10 when count frequency
extern int phraseFrequencyOn; // -m <number> : count phrase of <number> length
extern int phraseLength;
extern int topNWords;		  // -n <number> : count top <number> words*/