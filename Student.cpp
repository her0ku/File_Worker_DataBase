#include "Utils.h"
#include "Student.h"
#include "Zachetka.h"
#include <string>
#include <iostream>
Student::Student(string sname, string fname, string mname, int gender, Date bdate, string group, string facul, string kaf, Date edate, Zachetka* zach) {
	_sname = sname;
	_fname = fname;
	_mname = mname;
	_gender = gender;
	_bdate = bdate;
	_fac = facul;
	_kaf = kaf;
	_edate = edate;
	_group = group;
	_zach = zach;
}

Student::~Student() {
	delete _zach;
}

/*
		Структура блока студента имеет вид:
		(переносы строк  и пробелы отсутствуют,
		здесь добавлены для	большей читабельности)

		Фамилия (\1) Имя (\1) Отчество (\1) ПОЛ (\1)					// данные студента
		ДАТА РОЖДЕНИЯ (\1)ГОД ПОСТУПЛЕНИЯ (\1) ФАКУЛЬТЕТ (\1)			// данные студента
		КАФЕДРА (\1) ГРУППА (\1) НОМЕР ЗАЧЁТКИ(\2)						// данные студента
		Subj1 (\2) 5 (\3) Subj2 (\2) 4 (\3)(\1)							// первый семестр с двумя предметами
		(\1)															// второй семестр - нет сессии
		Subj3 (\2) 5 (\3) Subj4 (\2) 4 (\3)(\1)							// третий семестр с двумя предметами
		(\6)															// конец данных студента

	*/

string Student::dataForExport() {
	string result;
	char s = '\1';
	string el = "\2";
	result.append(this->_sname + s + this->_fname + s + this->_mname + s + to_string(this->_gender) + s);
	result.append(dateToStr(this->_bdate) + s + dateToStr(this->_edate) + s + this->_fac + s);
	result.append(this->_kaf + s + this->_group + s + this->_zach->_num + el);
	result.append(_zach->dump());
	result.append("\6");
	return result;
}

Student::Student(string data) {
	int ch = 0;
	char c = '1';
	int i = 0;
	string sname, fname, mname,
		gender, birth, edate,
		fac, kaf, group, zach_num;
	for (i; i < data.length(); i++) {
		c = data[i];
		if (c == '\1') {
			ch++;
			continue;
		}
		else if (c == '\2')
		{
			break;
		}
			// структура описана в функции dataForExpotr()
		switch (ch) {
		case 0: {
			sname += c; break;
		}
		case 1: {
			fname += c; break;
		}
		case 2: {
			mname += c; break;
		}
		case 3: {
			gender += c; break;
		}
		case 4: {
			birth += c; break;
		}
		case 5: {
			edate += c; break;
		}
		case 6: {
			fac += c; break;
		}
		case 7: {
			kaf += c; break;
		}
		case 8: {
			group += c; break;
		}
		case 9: {
			zach_num += c; break;
		}
		default:
			break;
		}
	}
	_sname = sname;
	_fname = fname;
	_mname = mname;
	_gender = stoi(gender);
	_bdate = parseDotDate(birth);
	_fac = fac;
	_kaf = kaf;
	_edate.year = stoi(edate);
	_group = group;
	Zachetka* zach = new Zachetka(zach_num);
	c = data[++i];
	while (c != '\6') {
		Semestr* sem = new Semestr();
		while (c != '\1' && c != '\6') {
			string stitle = "", smark = "";
			while (c != '\2' && c != '\1') {
				stitle += c;
				c = data[++i];
			}
			c = data[++i];
			while (c != '\3' && c != '\1') {
				smark += c;
				c = data[++i];
			}
			c = data[++i];
			Subj* sub = new Subj(stitle, stoi(smark));
			sem->addSubj(sub);
		}
		zach->addSem(sem);
		c = data[++i];
	}
	_zach = zach;
}

void Student::fullIntroduce() {
	Person::fullIntroduce();
	cout << "Номер зачётной книжки: " << this->_zach->_num << " | Год поступления: " << dateToStr(this->_edate) << endl;
	cout << "Группа: " << this->_group << " | Факультет: " << this->_fac << " | Кафедра: " << this->_kaf << endl;
}