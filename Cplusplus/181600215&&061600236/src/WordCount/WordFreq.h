#pragma once
#include<iostream>
#include<fstream>
#include<regex>
#include<map>
using namespace std;

bool cmp(pair<string, int> a, pair<string, int> b);
bool IsLetter(char ch);
bool IsWord(string word);
int WordFreq(string s);
void TopNWords();