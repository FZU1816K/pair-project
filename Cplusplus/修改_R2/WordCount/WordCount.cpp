/**************MAIN FUNCTION：WordCount******************/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include"Ccharacter.h"         //COUNT Character
#include"Cwords.h"             //COUNT Word
#include"Clines.h"             //COUNT Line
#include"Swords.h"             //COUNT words and SORT for TOPn
#include"Phrase.h"             //COUNT phrase and SORT for TOPn

/////////////////////////////////////////////////////////
int main(int argc, char * argv[])       //FOR windows IDE
////////////////////////////////////////////////////////
//int main()                            //FOR UnitTest
////////////////////////////////////////////////////////
{
	using namespace std;

	struct Parameter {
		string inFile;   /*-i option*/
		string outFile;  /*-o option*/
		int weight;      /*-w option*/
		int length;      /*-m option*/
		int num;         /*-n option*/
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
	/**************************************/
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

	/*******************************************************
	//   FOR  TEST   //
	para.inFile = "E:/学习/软工实践/作业2/2/修改_R1/Debug/CountFrequency_3.txt";
	para.outFile = "output.txt";
	para.weight = 0;
	para.length = 2;
	para.num = 10;
    //for (int i = 0; i < 10000; i++) {
	/*********************************************************/


	/********************************************************/
	//   FOR windows IDE  //
	if (argc == 1)                       //quit if no arguments
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
		Wsort sw(para.inFile,para.outFile,para.weight,para.num);
		Psort ps(para.inFile, para.outFile, para.length, para.num);

		cc.Count();
		cl.Count();
		cw.Count();
		
		int line = cl.Get();          //get the number of lines

		cc.Adjust(line);              //Without manual annotation
		cc.Show();
		cc.Fwrite();
		////////////////////////////////////////////////
		
		cw.Show();
		cw.Fwrite();
		////////////////////////////////////////////////
		
		
		cl.Show();
		cl.Fwrite();
		////////////////////////////////////////////////
		if (!flagm)
		{
			sw.CS();
		    sw.Show();
		    sw.Fwrite();
		}
		////////////////////////////////////////////////
		if (flagm)
		{
			ps.PS();
		    ps.Show();
		    ps.Fwrite();
		}
		
	/**********************************************************/

//	}
	return 0;
}