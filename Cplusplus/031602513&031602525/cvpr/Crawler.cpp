//我当时是一段函数一段函数运行成功的，如果一起运行，会有莫名的错误2333

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <sstream>
using namespace std;
#define MAXSIZE 1024
#pragma comment(lib, "Wininet.lib") 
void urlopen(_TCHAR*);

int lkft1(string str)
{
	int flag = 0;
	if (str.length() < 20){
		return  1;
	}
	if (str[11] != 'p'){
		flag = 1;
	}
	if (str[12] != 't'){
		flag = 1;
	}
	if (str[13] != 'i'){
		flag = 1;
	}
	return flag;//0 为标题 1 不是标题
}

//flag函数
int my_flag(string str)//str == sline  2 title 1 abstract 	//pdf.link 4  arXiv 5  author 6  month 7  year 8
{
	int i = 20, flag = 0;
	if (str.length() > 10 && str[1] == 'b' &&str[2] == 'r' && str[5] == 'b' && str[6] == 'r')
	{
		flag = 1;
	}
	if (str.length() > 15 && str[9] == 'p' &&str[10] == 'a' && str[11] == 'p' && str[12] == 'e')
	{
		flag = 2;
	}
	if (str.length() > 20 && str[0] == '[' && str[1] == '<' && str[2] == 'a'){
		while (str[i] != '>'){
			i++;
		}
		if (str[i + 1] == 'p'){
			flag = 4;
		}
		else if (str[i + 1] == 'a'){
			flag = 5;
		}
	}
	if (str.length() > 20 && str[0] == 'a' && str[1] == 'u' && str[2] == 't' && str[3] == 'h'){
		flag = 6;
	}
	if (str.length() > 10 && str[0] == 'm' && str[1] == 'o' && str[2] == 'n' && str[3] == 't'){
		flag = 7;
	}
	if (str.length() > 10 && str[0] == 'y' && str[1] == 'e' && str[2] == 'a' && str[3] == 'r'){
		flag = 8;
	}
	return flag;
}

//下载html的函数 
void urlopen(TCHAR* url)
{
	std::ofstream write;
	write.open("text1.txt");

	HINTERNET hSession = InternetOpen(_T("UrlTest"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession != NULL)
	{
		HINTERNET hHttp = InternetOpenUrl(hSession, url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
		if (hHttp != NULL)
		{
			BYTE Temp[MAXSIZE];
			ULONG Number = 1;
			while (Number > 0)
			{
				InternetReadFile(hHttp, Temp, MAXSIZE - 1, &Number);
				Temp[Number] = '\0';			
				write << Temp;
			}
			InternetCloseHandle(hHttp);
			hHttp = NULL;
		}
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
	write.close();
}

//由url下载html的函数 
void urlopen2()
{
	std::ofstream write;
	int flag=0,abs=0;
	ifstream inf;
	string sline,tt;
	TCHAR url[MAXSIZE];
	inf.open("text3.txt");
	write.open("text4.txt");
	while (getline(inf, sline))
	{
		if (sline.length() > 20){
			_stprintf_s(url, MAXSIZE, _T("%S"), sline.c_str());
			HINTERNET hSession = InternetOpen(_T("UrlTest"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
			if (hSession != NULL)
			{
				HINTERNET hHttp = InternetOpenUrl(hSession, url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
				if (hHttp != NULL)
				{
					printf("%d\n",flag);
					flag++;
					BYTE Temp[MAXSIZE];
					ULONG Number = 1;
					while (Number > 0)
					{
						InternetReadFile(hHttp, Temp, MAXSIZE - 1, &Number);
						Temp[Number] = '\0';	
						write << Temp;
					}
					InternetCloseHandle(hHttp);
					hHttp = NULL;
				}
				InternetCloseHandle(hSession);
				hSession = NULL;
			}
		}
	}
	write.close();
}

int _tmain(int argc, TCHAR* argv[])
{	
	ifstream inf;
	int i, k = 0, flag = 0,abs = 0,num = 0;  
	string url = "http://openaccess.thecvf.com/";
	string url2[300];
	std::ofstream write;
	string sline;
	
	//第一步，从首页获得论文的具体网址    写到 text1.txt 中
	urlopen(_T("http://openaccess.thecvf.com/CVPR2018.py"));

	//第二步，将其修改为可查看模式  到 text2.txt 中
	inf.open("text1.txt");
	write.open("text2.txt");
	while (getline(inf, sline))
	{
		write << sline << endl << endl;
	}
	write.close();	 
	
	//第三步，对 text2.txt 逐行分析，若包含网址，生成str加上前缀成为这篇论文具体的网址
	inf.open("text2.txt");
	write.open("text3.txt");
	while (getline(inf, sline))
	{
		if (!lkft1(sline))
		{	
			for (i = 0;  i < 300; i++)
			{
				url2[i].clear();
				if (i < url.length())
				{
					url2[i] = url[i];
				}
			}
			k = 29;
			i = 32;
			while (sline[i] != '"')
			{
				url2[k] = sline[i];
				k++;
				i++;
			}
			for (i = 0; i < 300; i++)
			{
				write << url2[i];
			}
			write << endl;
		}
	}
	write.close();
	
	//第四步，通过text3中各篇论文的url，将所有论文的html载到text4中 
	urlopen2();

	//第五步，将论文修改为可查看模式
	inf.open("text4.txt");
	write.open("text5.txt");
	while (getline(inf, sline))
	{
		write << sline << endl << endl;
	}
	write.close();
	
	//第六步，对论文的title，abstract等要素进行分析
	inf.open("text5.txt");
	write.open("text6.txt");
	while (getline(inf, sline))
	{
		flag = my_flag(sline);
		if (flag == 2||flag==1){
			abs = 3;
		}
		if (flag == 2){
			if (num != 0){
				write << endl << endl;
			}
			write << num<<endl<<"Title: ";
			num++;
		}
		if (flag == 1){
			write << "Abstract: ";
		}
		if (abs == 1){
			i = 0;
			while (sline[i] != '<'){
				write << sline[i];
				i++;
			}
			write << endl;
		}
		if (abs > 0){
			abs--;
		}
		//author
		if (flag == 6){
			i = 10;
			write << "Author: ";
			while (sline[i] != '}'){
				write << sline[i];
				i++;
			}
			write << endl;
		}
		//arXiv
		if (flag == 5){
			i = 40;
			write << "arXiv: ";
			while (sline[i] != '"'){
				write << sline[i];
				i++;
			}
			write << endl;
		}
		//pdf
		if (flag == 4){
			i = 16;
			write << "PDF_LINK: ";
			write << url;
			while (sline[i] != '"'){
				write << sline[i];
				i++;
			}
			write << endl;
		}
		//month 7
		if (flag == 7){
			i = 9;
			write << "Month: ";
			while (sline[i] != '}'){
				write << sline[i];
				i++;
			}
			write << endl;
		}
		//year 8
		if (flag == 8){
			i = 8;
			write << "Year: ";
			while (sline[i] != '}'){
				write << sline[i];
				i++;
			}
			write << endl;
		}

	}
	write.close();

//text1 官网的html
//text2 可查看的html 
//text3 各篇论文的url 
//text4 各篇论文的html 
//text5 可查看的论文html 
//text6 最终txt文件 

	return 0;
}
