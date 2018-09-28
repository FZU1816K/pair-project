/**************这是主调函数：WordCount******************/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include"Ccharacter.h" //计算字符个数的类Character
#include"Cwords.h" //计算单词个数的类Word （数据预处理）
#include"Clines.h" //计算行数的类Line
#include"Swords.h" //统计最多的10个单词及其词频的类Wsort （只需要调用Cword再进行排序就可以了吧）
#include"Phrase.h" //统计词组个数

/////////////////////////////////////////////////////////
int main(int argc, char * argv[])  //采用windows IDE时使用
////////////////////////////////////////////////////////
//int main()                             //单元测试时使用
////////////////////////////////////////////////////////
{
	using namespace std;

	struct Parameter {
		string inFile; /*-i option*/
		string outFile; /*-o option*/
		int weight; /*-w option*/
		int length; /*-m option*/
		int num; /*-n option*/
	}para;

	/*Initialization*/
	para.inFile = "";
	para.outFile = "";
	para.weight = 0;
	para.length = 0;
	para.num = 0;
	/*End of initialization*/

	int flagn = 0;
	int flagm = 0;

	for (int i = 1; i < argc; i++)
	{
		string s = argv[i];
		if (s == "-i")
		{
			i++;
			para.inFile = argv[i];
		}
		else if (s == "-o")
		{
			i++;
			para.outFile = argv[i];
		}
		else if (s == "-w")
		{
			i++;
			string ww = argv[i];
			para.weight = ww[0] - '0';
		}
		else if (s == "-m")
		{
			flagm = 1;
			i++;
			string mm = argv[i];
			for (int j = 0; j < mm.length(); j++)
			{
				para.length = para.length * 10 + (mm[j] - '0');
			}
		}
		else if (s == "-n")
		{
			i++;
			flagn = 1;
			string nn = argv[i];
			for (int j = 0; j < nn.length(); j++)
			{
				para.num = para.num * 10 + (nn[j] - '0');
			}
		}
		else
		{
			cout << s << endl;
			cerr << "无效参数" << endl;
			exit(EXIT_FAILURE);
		}
	}
	if (!flagn)
		para.num = 10;

	/********************************************************/
	//   测试时使用   //
	//std::string f = "E:/Users/lenovo/Source/repos/input.txt";
	//std::string fout = "result.txt";
//	for (int i = 0; i < 10000; i++) {
	/*********************************************************/


	/******************************************************/
	//   采用windows IDE时使用  //
	if (argc == 1)   //quit if no arguments
	{
		cerr << "Usage:" << argv[0] << "filename[s]\n";
		exit(EXIT_FAILURE);
	}
	if (argc < 7)
	{
		cerr << "Input too little filenames.\n";
		exit(EXIT_FAILURE);
	}
	/*
	for (int file = 1; file < argc; file++)
	{
		string f = argv[file];
	*/
	/*********************************************************/

	/*********************************************************/
		Character cc(para.inFile,para.outFile);
		Word cw(para.inFile,para.outFile);
		Line cl(para.inFile,para.outFile);
		Wsort sw(para.inFile,para.outFile,para.weight,para.num);                           /********改了*********/
		Psort ps(para.inFile, para.outFile, para.length, para.num);                         /********新增*********/
																					 ////////////////////////////////////////////////
		cc.count(); //无参调用
		cc.show();  //无参调用
		cc.fwrite();//无参调用
		////////////////////////////////////////////////
		cw.count();
		cw.show();
		cw.fwrite();
		////////////////////////////////////////////////
		cl.count();
		cl.show();
		cl.fwrite();
		////////////////////////////////////////////////
		if (!flagm)
		{
			sw.CS();
		    sw.show();
		    sw.fwrite();
		}
		////////////////////////////////////////////////
		if (flagm)
		{
			ps.PS();
		    ps.show();
		    ps.fwrite();
		}
		
	/**********************************************************/

//	}
	return 0;
}