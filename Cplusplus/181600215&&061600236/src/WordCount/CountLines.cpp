#include "pch.h"
#include "CountLines.h"

int CountLines(string name) {
	ifstream file;
	file.open(name);
	int line = 0, rnow = 0;
	int ch;
	while (ch = getchar()) {
		if (ch == '\n' || ch == -1) {
			if (rnow == 1) line++;
			if (rnow == 2) line++;
			rnow = (rnow + 1) % 5;
			if (ch == -1) break;
		}
	}
	file.close();
	return line;
}