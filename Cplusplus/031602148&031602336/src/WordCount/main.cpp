#include "stdafx.h"
#include "File.h"
#include "Statistics.h"
#include "Parameter.h"
using namespace std;

int main(int argc, char *argv[])
{
	Parameter p;
	File f;
	Statistics	s;
	p.set();
	p.get_Parameter(argc, argv);
	f.open(argv[p.i], argv[p.o]);
	s.set(f.infile,p.w,p.m);
	f.output(s.cnum, s.wnum, s.lnum, s.word, p.n);
	f.close();
	//system("pause");
	return 0;
}