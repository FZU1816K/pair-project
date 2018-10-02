/**
 * File name: Cwords.cpp
 * Description: COUNT words
 * Function List:
	int Get()         //Return number, for UnitTest
	void Fwrite();    //Write result into file
	void Count();     //Count file's words
	void Show();      //Show result in screen
 */
#ifndef CWORDS_H_
#define CWORDS_H_
#include<string>

class Word
{
private:
	int number;
	std::string finname;
	std::string foutname;

public:

	Word(std::string file, std::string fileout);
	Word();
	int Get();
	void Fwrite();
	void Count();
	void Show();
};

#endif