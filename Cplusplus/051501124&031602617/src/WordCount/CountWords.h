#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "pch.h"
#include <algorithm>
using namespace std;

int lineAmount;

int CountWord(string inputFilename,bool weightOn);
void stringCut(string inStr);
void WordClassify(string word);
void stringCutWithLen(string inStr,int phraseLen);