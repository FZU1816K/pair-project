#include<get_result.h>
#include<something.h>
void Generate_result()
{
	fstream file;
	string line; // Read line by line
	file.open(openfile2);

	fstream file1;
	file1.open(fileName2, ios::out | ios::binary);

	smatch result;
	regex pattern1("(<div id=\"papertitle\">)");  //Match the previous line of title
	regex pattern2("(<br><br><div id=\"abstract\" >)");  //Match the previous line of abstract

	int flag1 = 0;
	int flag2 = 0;
	int count = 0;

	while (getline(file, line))
	{
		if (flag1 == 1)
		{
			for (int j = 6; j > 0; j--) { line.pop_back(); }  //Delete the last </div>
			file1 << count++ << endl;
			file1 << "Title: " << line << endl;
			flag1 = 0;
		}
		if (regex_match(line, result, pattern1) == true) {
			flag1 = 1;
		}

		if (flag2 == 1)
		{
			for (int j = 6; j > 0; j--) { line.pop_back(); }
			file1 << "Abstract: " << line << endl;
			file1 << endl;
			file1 << endl;
			flag2 = 0;
		}
		if (regex_match(line, result, pattern2) == true) {
			flag2 = 1;
		}

	}
	file.close();
	file1.close();
}
