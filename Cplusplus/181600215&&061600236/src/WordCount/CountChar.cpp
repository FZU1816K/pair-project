#include "pch.h"
#include "CountChar.h"


int CountChar(string name) {
	int ch;
	ifstream file;
	file.open(name);
	int characters = 0, len = 0, rnow = 0;
	while (ch = getchar()) {
		if (ch >= 128) continue;
		if (ch == '\n' || ch == -1) {
			if (rnow == 1) characters += len - 7;
			if (rnow == 2) characters += len - 10;
			rnow = (rnow + 1) % 5;
			len = 0;
			if (ch == -1) break;
		}
		else len++;
	}
	if (characters == 0) {
		cout << "File not found!";
		exit(1);
	}
	file.close();
	return characters;
}