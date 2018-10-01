#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "pch.h"
using namespace std;

int CountWord(string inputFilename,bool weightOn);

void stringCut(string inStr);
void WordClassify(string word);


void stringCutWithLen(string inStr,int phraseLen);