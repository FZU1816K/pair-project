// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include<iostream>
#include <fstream>
#include <string>
#include <queue> 
using namespace std;

typedef struct
{
	string s;
	int frq = 0;
	int bl = 0;
}wd;

int n = 0;
int size;
int a[10000] = {};
wd temp, word[600000], ts;
string temps = "", str[800];
priority_queue<string, vector<string>, greater<string> > sorrt;

int charcount(char *tx, string txo);
int linecount(char *tx, string txo);
int wordcount(char *tx, string txo, int bo);
void  sor(wd *f, int n);
void wordmax(char *tx, string txo, int num, int m);

int ifchar(char c);
int ifword(string s);
void start(string s, int m);
int findword(string s);


// TODO: 在此处引用程序需要的其他头文件
