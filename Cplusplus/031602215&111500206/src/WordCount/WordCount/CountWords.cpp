#include "CountWords.h"

int Transition(int state, char input, int * count)
{
	switch (state)
	{
	case OUTWORD:
		if (Separator(input)) return OUTWORD; 
		if (isalpha(input)) return P1; 
		if (IsNum(input)) return NotAWord;

	case NotAWord:
		if (Separator(input)) return OUTWORD;
		else return NotAWord;

	case P1:
		if (IsNum(input)) return NotAWord;
		if (isalpha(input)) return P2;
		else return OUTWORD;

	case P2:
		if (IsNum(input)) return NotAWord;
		if (isalpha(input)) return P3;
		else return OUTWORD;

	case P3:
		if (IsNum(input)) return NotAWord;
		if (isalpha(input)) return VALIDWORD;
		else return OUTWORD;

	case VALIDWORD:
		if (isalnum(input)) return VALIDWORD;
		else { (*count)++; return OUTWORD; }
	}
	return ERRORSTATE;
}


int CountWords(std::string line)
{
	int count = 0;
	char c;
	int state = OUTWORD;
	int i = 0;
	while ((c = line[i]) != '\0' && state != ERRORSTATE) {
		if (!(c >= 1 && c <= 255)) //non - ascii character should not included
		{
			state = OUTWORD;
			i++;
			continue;
		}
		c = tolower(c);
		state = Transition(state, c, &count);
		i++;
	}
	if (state == ERRORSTATE) {
		std::cout << "DFA error state." << std::endl;
	}
	if (state == VALIDWORD) {
		count++;
	}
	return count;
}
