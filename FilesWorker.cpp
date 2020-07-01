#include "FilesWorker.h"
#include <string>
#include <iostream>
using namespace std;

string fheader = "\1\3\3\7"; //строчка для валидации БД.фалйа

int fileExists(string name) {
	FILE* file = nullptr;
	fopen_s(&file, name.c_str(), "r");
	if (file) 
	{
		fclose(file);
		return true;
	}

	else 
	{
		return false;
	}

}

int ReadOut(string* str) 
{
	FILE* out = nullptr;
	fopen_s(&out, "db.bin", "w");
	str->insert(0, fheader);
	char c = '0';
	for (int t = 0; t < str->length(); t++) 
	{
		c = (*str)[t];
		fwrite(&c, 1, 1, out);
	}

	c = '\0';
	fwrite(&c, 1, 1, out);
	fclose(out);
	return 1;
}

string ContentRead() 
{
	FILE* in = nullptr;
	fopen_s(&in, "db.bin", "r");
	string result = "";
	char c = '0';
	fseek(in, 0, 0);
	for (int i = 0; i < 4; i++) 
	{
		fread(&c, 1, 1, in);
		if (c != fheader[i]) 
		{
			cout << "База данных не соответствует!" << endl;
			system("pause");
			exit(0);
		}
	}
	fseek(in, 4, 0);
	while (c != '\0') 
	{
		fread(&c, 1, 1, in);
		result += c;
	}
	fclose(in);
	return result;
}

