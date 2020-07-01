#include "Utils.h"
#include "Date.h"

// функци€ дл€ смены регистра текста
// строка, 0=нижний/1=верхний регистр
string strCase(string s, int f) {
	// размер строки
	int size = s.size();
	// нова€ строка дл€ результата
	// присваиваем значение старой, чтобы получить строку той же длины
	string r = s;

	// провер€ем, в какой регистр нужно перевести текст
	if (f) {
		// посимвольно переводим текст в верхний регистр
		for (int i = 0; i < size; i++) {
			r[i] = char(toupper(s[i]));
		}
	}
	else {
		// посимвольно переводим текст в нижний регистр
		for (int i = 0; i < size; i++) {
			r[i] = char(tolower(s[i]));
		}
	}
	// возвращаем новую строку
	return r;
}

string dateToStr(Date d) {
	string ret = "";
	if (d.day > 0) {
		if (d.day < 10)
			ret.append("0");
		ret.append(to_string(d.day));
	}

	if (ret != "")
		ret.append(".");
	if (d.mon > 0) {
		if (d.mon < 10)
			ret.append("0");
		ret.append(to_string(d.mon));
	}

	if (ret != "")
		ret.append(".");
	if (d.year > 0)
		ret.append(to_string(d.year));
	return ret;
}

Date parseDotDate(string sdate) {
	Date r;
	Date bad = Date(-1, -1, -1);
	int len = sdate.length();
	sdate.append("a");
	if (sdate.find_first_not_of("0123456789.") != len)
		return bad;
	sdate = sdate.substr(0, sdate.length() - 1);
	char* c_st = new char[sdate.length() + 1];
	strcpy_s(c_st, sdate.length() + 1, sdate.c_str());
	char* part, * posn;
	part = strtok_s(c_st, ".", &posn);
	int c = 0;
	while (part != NULL) {
		switch (c)
		{
		case 0:
			r.day = stoi(part);
			break;
		case 1:
			r.mon = stoi(part);
			break;
		case 2:
			r.year = stoi(part);
			break;
		default:
			break;
		}

		part = strtok_s(NULL, ".", &posn);
		c++;
	}

	delete c_st;
	delete part;
	posn = nullptr;
	if (c != 3)
		return bad;
	return r;
}

// ѕроверка строки на возможность конвертировани€ в положительное число
int isValidInt(string num) {
	if (num == "" || num.length() > 9)
		return 0;
	num.append("z");
	if (num.find_first_not_of("0123456789") != num.length() - 1)
		return 0;
	return 1;
}
// ѕроверка строки на наличие недопустимых символов
int checkSpec(string name, int type) {
	name.append("$");
	name = strCase(name, 0);
	switch (type)
	{
	case 0:
		return (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzйцукенгшщзхъфывапролджэ€чсмитьбю") == name.length() - 1);
	case 1:
		return (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789.-йцукенгшщзхъфывапролджэ€чсмитьбю") == name.length() - 1);
	default:
		break;
	}

	return 0;
}

string trim(string str) {
	string result = "";
	if (str == "") return "";
	int rLen = str.length();
	char c = str[0];
	int count = 0;
	while (c == ' ') {
		count++;
		c = str[count];
	}

	str = str.substr(count, rLen - count);
	c = str[rLen - count - 1];
	while (c == ' ') {
		rLen--;
		c = str[rLen - count - 1];
	}

	str = str.substr(0, rLen - count);
	return str;
}

