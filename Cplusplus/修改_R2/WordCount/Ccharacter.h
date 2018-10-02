/**
 * File name: Ccharacter.cpp
 * Description: COUNT characters
 * Function List:
    int Get()             //Return number, for UnitTest
	void Fwrite();        //Write result into file
	void Count();         //Count file's characters
	void Show();          //Show result in screen
	void Adjust(int line) //Without manual annotation
 */

#ifndef CCHARACTER_H_
#define CCHARACTER_H_
#include<string>
class Character
{
private:
	int number;          //character's number
	std::string finname; //input file name
	std::string foutname;//output file name

public:

	Character(std::string filein, std::string fileout);
	Character();
	int Get();
	void Fwrite();
	void Count();
	void Show();
	void Adjust(int line);
};

#endif
