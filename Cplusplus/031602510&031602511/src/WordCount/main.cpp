#include <iostream>
#include "InputFile.h"

using namespace std;

int main() 
{
	string order_inputPath;
	int order_weight = 0;
	string order_outputPath;
	int order_phraseLength = 1;
	int order_sortNum = 10;

	order_inputPath = "input.txt";
	order_phraseLength = 3;

	InputFile inputFile(order_inputPath, order_phraseLength, order_weight, order_sortNum);



	/*≤‚ ‘”Ôæ‰*/
	cout << "characters: " << inputFile.getCrtNum() << endl;
	cout << "words: " << inputFile.getWordNum() << endl;
	cout << "lines: " << inputFile.getLineNum() << endl;
	vector<pair<string, int>> orderWord = inputFile.getOrderWord();
	vector<pair<string, int>>::iterator outItor;
	outItor = orderWord.begin();
	for (int i = 0; i < 10 && outItor != orderWord.end(); i++, outItor++) {
		cout << "<" << outItor->first << ">" << ": " << outItor->second << endl;
	}
	system("pause");


	return 0;
}