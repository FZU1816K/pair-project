#pragma once
#include "pch.h"
using namespace std;
#include <string>

//enum PaperType{		// 论文属性枚举
//	oral,
//	spotlight,
//	poster
//};

struct Paper
{
	Paper(string &_title, string &_abstract)
		:title(_title), abstract(_abstract) {}
	string title;				// 论文标题
	string abstract;			// 论文摘要

	//vector<string> authors;	// 论文作者
	//PaperType paperType;		// 论文属性
	//string webside;			// 论文网站
	//string pdfLink;			// 论文PDF网站
};