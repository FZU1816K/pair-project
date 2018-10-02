/**
 * File name: Clines.cpp
 * Description: COUNT lines
 * Function List:
	int Get()         //Return number, for UnitTest
	void Fwrite();    //Write result into file
	void Count();     //Count file's lines
	void Show();      //Show result in screen
 */
#ifndef CLINES_H_
#define CLINES_H_
#include<string>
class Line
{
private:
	int number;
	std::string finname;
	std::string foutname;

public:
	Line(std::string filein, std::string fileout);
	Line();
	int Get();
	void Fwrite();
	void Count();
	void Show();
};

#endif
