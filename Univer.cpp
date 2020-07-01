#include "Univer.h"
#include "Subj.h"
#include "Zachetka.h"
#include "Semestr.h"
#include "Utils.h"
#include "Student.h"
#include <iostream>
#include <iomanip>

using namespace std;

Univer::Univer(string title) {
	_title = title;
	_students = new StudentArray();
	N = 0;
}
/*
Структура файла имеет вид :
(переносы строк  и пробелы отсутствуют,
	здесь добавлены для	большей читабельности)

	\1\3\3\7 Фамилия(\1) Имя(\1) Отчество(\1) ПОЛ(\1)			// данные студента, \1\3\3\7 = заголовок для проверки
	ДАТА РОЖДЕНИЯ(\1)ГОД ПОСТУПЛЕНИЯ(\1) ФАКУЛЬТЕТ(\1)			// данные студента
	КАФЕДРА(\1) ГРУППА(\1) НОМЕР ЗАЧЁТКИ(\2)						// данные студента
	Subj1(\2) 5 (\3) Subj2(\2) 4 (\3)(\1)							//  первый семестр с двумя предметами
	(\1)															// второй семестр - нет сессии
	Subj3(\2) 5 (\3) Subj4(\2) 4 (\3)(\1)							// третий семестр с двумя предметами
	(\6)															// конец данных студента, далее может быть такой же блок
	......															// другие студенты такого же вида
	(\0)
	*/
string Univer::exportAll() {
	string result;
	for (int i = 0; i < _students->length; i++) {
		result.append((*_students)[i].dataForExport());
	}
	return result;
}
void Univer::saveAll()
{
	string* str1 = new string(exportAll());
	ReadOut(str1);
	delete str1;
}
void Univer::loadAll()
{
	string data = ContentRead();
	string oneStud;
	int i = 0;
	char c = data[i];
	while (c != '\0') {
		oneStud = "";
		while (c != '\6' && c != '\0') {
			c = data[i];
			oneStud += c;
			i++;
		}
		c = data[i];
		Student* ns = new Student(oneStud);
		addStudent(ns);
	}
}
Univer::~Univer() {
	delete _students;
}
void Univer::showStudentChangeDialog(string zn) {
	Student* s = getByZach(zn);
	cout << "Введите номер пункта, в который хотите внести изменения:" << endl;
	cout << "1. Фамилия (" << s->_sname << ")" << endl;
	cout << "2. Имя (" << s->_fname << ")" << endl;
	cout << "3. Отчество (" << s->_mname << ")" << endl;
	cout << "4. Пол (" << to_string(s->_gender) << ")" << endl;
	cout << "5. День рождения (" << dateToStr(s->_bdate) << ")" << endl;
	cout << "6. Год поступления (" << to_string(s->_edate.year) << ")" << endl;
	cout << "7. Факультет (" << s->_fac << ")" << endl;
	cout << "8. Кафедра (" << s->_kaf << ")" << endl;
	cout << "9. Группа (" << s->_group << ")" << endl;
	cout << "10. Номер зачётки (" << s->_zach->_num << ")" << endl;
	cout << "11. Предмет" << endl;
	cout << "0. Выйти в главное меню" << endl;
	cout << "> ";
chng:
	string n;
	getline(cin, n);
	if (!isValidInt(n) || stoi(n) > 12 || stoi(n) < -1) {
		cls;
		goto chng;
	}
	if (n == "0")
	{
		cls;
		return;
	}
	changeStudent(zn, stoi(n));
	cls;
	return;
}
void Univer::changeStudent(string zach_num, int field) {
	string tmp;
	Student* t = getByZach(zach_num);
	switch (field)
	{
	case 1: {
	sname:
		cout << EXITHINT << endl;
		cout << "Фамилия (" << t->_sname << ") > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if (!checkSpec(tmp, 0)) {
			cout << CHR_ERR << endl;
			goto sname;
		}
		t->_sname = tmp; break;
	}
	case 2: {
	fne:
		cout << EXITHINT << endl;
		cout << "Имя (" << t->_fname << ") > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if (!checkSpec(tmp, 0)) {
			cout << CHR_ERR << endl;
			goto fne;
		}
		t->_fname = tmp; break;
	}
	case 3: {
	mne:
		cout << EXITHINT << endl;
		cout << "Отчество (" << t->_mname << ") > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if (!checkSpec(tmp, 0)) {
			cout << CHR_ERR << endl;
			goto mne;
		}
		t->_mname = tmp; break;
	}
	case 4: {
	gender_input:
		cout << "Пол [Ж,М] (" << to_string(t->_gender) << ") > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if ((strCase(tmp, 0) != "ж") && (strCase(tmp, 0) != "м")) {
			cout << INVINP;
			goto gender_input;
		}
		tmp = (strCase(tmp, 0) == "м" ? "1" : "0");
		t->_gender = stoi(tmp); break;
	}
	case 5: {
		Date bday;
	bdate_input:
		cout << EXITHINT << endl;
		cout << "Дата рождения {дд.мм.ГГГГ} (" << dateToStr(t->_bdate = bday) << ") > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if (!bday.isValid(parseDotDate(tmp)) || parseDotDate(tmp).year >= t->_edate.year) {
			cout << INVINP << " (возможно дата рождения превышает дату поступления)" << endl;
			goto bdate_input;
		}
		bday = parseDotDate(tmp);
		t->_bdate = bday; break;
	}
	case 6: {
		Date jdate;
	jdate_input:
		cout << EXITHINT << endl;
		cout << "Год поступления {ГГГГ} (" << to_string(t->_edate.year) << ") > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if (!isValidInt(tmp) || stoi(tmp) < 0 || stoi(tmp) > 9999 || stoi(tmp) <= t->_bdate.year) {
			cout << INVINP << " (возможно дата рождения больше даты поступления)" << endl;
			goto jdate_input;
		}
		jdate.year = stoi(tmp);
		t->_edate = jdate; break;
	}
	case 7: {
		cout << EXITHINT << endl;
		cout << "Факультет > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		tmp = trim(tmp);
		t->_fac = tmp;
		break;
	}
	case 8: {
		cout << EXITHINT << endl;
		cout << "Кафедра > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		tmp = trim(tmp);
		t->_kaf = tmp;
		break;
	}
	case 9: {
	gri:
		cout << EXITHINT << endl;
		cout << "Группа > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if (!checkSpec(tmp, 1)) {
			cout << CHR_ERR << endl;
			goto gri;
		}
		t->_group = tmp;  break;
	}
	case 10: {
	zang:
		cout << EXITHINT << endl;
		cout << "Номер зачётки (" << t->_zach->_num << ") > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if (checkSpec(tmp, 0) || !hasStudent(tmp))
			t->_zach->_num = tmp;
		else {
			cout << "Такой номер зачётной книжки уже существует или содержит недопустимые символы!" << endl;
			goto zang;
		}
		break;
	}
	case 11: {
		cout << EXITHINT << endl;
	semnum:
		cout << "Номер семестра > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if (!isValidInt(tmp) || stoi(tmp) > 9 || stoi(tmp) < 1) {
			cout << INVINP << endl;
			goto semnum;
		}
		Semestr* tsem = t->_zach->_sems[stoi(tmp) - 1];
		if (tsem->sc == 0) {
			cout << "В этой сессии предметов нет!" << endl;
			system("pause");
			cls;
			goto semnum;
		}
	cstitle:
		cout << "Название предмета, который вы хотите изменить > ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if (!tsem->hasSubj(tmp)) {
			cout << "Предмет не найден!" << endl;
			goto cstitle;
		}
		Subj* tsub = tsem->getByTitle(tmp);
	subjmenu:
		cls;
		cout << "Вы хотите изменить: " << endl;
		cout << "1. Название" << endl;
		cout << "2. Оценка" << endl;
		cout << "> ";
		getline(cin, tmp);
		checkReturn(zach_num);
		if (!isValidInt(tmp) || stoi(tmp) < 1 || stoi(tmp) > 2) {
			cout << INVINP << endl;
			goto subjmenu;
		}
		if (tmp == "1") {
		nstitle:
			cout << "Новое название предмета > ";
			getline(cin, tmp);
			checkReturn(zach_num);
			if (!tsem->hasSubj(tmp) && tmp != "") {
				tsub->title = trim(tmp);
			}
			else {
				cout << "Предмет с таким названием уже существует в данной сессии!" << endl;
				goto cstitle;
			}
		}
		else {
			cout << "Новая оценка (1=пересдача, 2-5=оценка) > ";
			getline(cin, tmp);
			checkReturn(zach_num);
			if (!isValidInt(tmp) || stoi(tmp) < 1 || stoi(tmp) > 5) {
				cout << INVINP << endl;
				goto cstitle;
			}
			else {
				tsub->mark = stoi(tmp);
			}
		}
		cls;
		break;
	}
	default:
		break;
	}
	return;
}
void Univer::addStudent(Student* S) {
	if (!hasStudent(S)) {
		_students->addItem(S);
		N++;
	}
	else {
		return;
	}
}
void Univer::removeStudent(string zach) {
	_students->StudentRemove(zach);
	N--;
	system("pause");
}
int Univer::hasStudent(Student* S) {
	return hasStudent(S->_zach->_num);
	return 0;
}
int Univer::hasStudent(string zach_num) {
	if (N)
		for (int i = 0; i < _students->length; i++) {
			if (strCase((*_students)[i]._zach->_num, 0) == strCase(zach_num, 0)) {
				return 1;
			}
		}
	return 0;
}
Student* Univer::getByZach(string zn) {
	for (int i = 0; i < _students->length; i++) {
		if (strCase((*_students)[i]._zach->_num, 0) == strCase(zn, 0)) {
			return &(*_students)[i];
		}
	}
}
void Univer::showStudents() {
	for (int i = 0; i < _students->length; i++) {
		(*_students)[i].fullIntroduce();
		cout << "Зачётка: " << endl;
		(*_students)[i]._zach->showAll();
		cout << "------------------------------------------------------------------------" << endl;
	}
}


void Univer::sort_by(int vib1, int vib2, int year1, int year2)
{
	float *mass_stud = new float[N];
	int *index = new int[N];
	vib1--;
	vib2--;
	if (vib1 != -1 && vib2 != -1 && year1 != 0 && year2 != 0)
	{
		for (int i = 0; i < N; i++)
		{
			Student* stud = &((*_students)[i]);
			float count_mark = 0;
			float percent = 0;
			float thr_mark = 0;
			float temp;
			for (int k = 0; k < stud->_zach->sc; k++)
			{
				for (int j = 0; j < stud->_zach->_sems[k]->sc; j++)
				{
					if (k == vib1 || k == vib2)
					{
						if (stud->_bdate.year <= year2 && stud->_bdate.year >= year1)
						{
							if (stud->_zach->_sems[k]->_subjects[j]->mark == 3)
							{
								thr_mark++;
							}
							count_mark++;
							index[i] = i;
						}
						else index[i] = -1;
					}
				}
			}
			/*cout << "Кол-во твроек = " << thr_mark << "\n";
			cout << "Оценка = " << count_mark << "\n";*/
			percent = (thr_mark / count_mark) * 100;
			/*cout << "Процентное содержнае 3ек = " << percent << "%\n";*/
			mass_stud[i] = percent;
			if (mass_stud[i] != mass_stud[i])
			{
				mass_stud[i] = 0;
			}
		}
	}
	else if (vib1 == -1 && vib2 == -1 && year1 != 0 && year2 != 0)
	{
		for (int i = 0; i < N; i++)
		{
			Student* stud = &((*_students)[i]);
			float count_mark = 0;
			float percent = 0;
			float thr_mark = 0;
			float temp;
			for (int k = 0; k < stud->_zach->sc; k++)
			{
				for (int j = 0; j < stud->_zach->_sems[k]->sc; j++)
				{
					if (stud->_bdate.year <= year2 && stud->_bdate.year >= year1)
					{
						if (stud->_zach->_sems[k]->_subjects[j]->mark == 3)
						{
							thr_mark++;
						}
						count_mark++;
						index[i] = i;
					}
					else index[i] = -1;
				}
			}
			percent = (thr_mark / count_mark) * 100;
			mass_stud[i] = percent;
			if (mass_stud[i] != mass_stud[i])
			{
				mass_stud[i] = 0;
			}
		}
	}
	else if (vib1 == -1 && vib2 == -1 && year1 == 0 && year2 == 0)
	{
		for (int i = 0; i < N; i++)
		{
			Student* stud = &((*_students)[i]);
			float count_mark = 0;
			float percent = 0;
			float thr_mark = 0;
			float temp;
			for (int k = 0; k < stud->_zach->sc; k++)
			{
				for (int j = 0; j < stud->_zach->_sems[k]->sc; j++)
				{
					if (stud->_zach->_sems[k]->_subjects[j]->mark == 3)
					{
						thr_mark++;
					}
					count_mark++;
				}
			}
			percent = (thr_mark / count_mark) * 100;
			mass_stud[i] = percent;
			if (mass_stud[i] != mass_stud[i])
			{
				mass_stud[i] = 0;
			}
			index[i] = i;
		}
	}
	else if (vib1 == vib2 && year1 != 0 && year2 != 0)
	{
		for (int i = 0; i < N; i++)
		{
			Student* stud = &((*_students)[i]);
			float count_mark = 0;
			float percent = 0;
			float thr_mark = 0;
			float temp;
			for (int k = 0; k < stud->_zach->sc; k++)
			{
				for (int j = 0; j < stud->_zach->_sems[k]->sc; j++)
				{
					if (k == vib1)
					{
						if (stud->_bdate.year <= year2 && stud->_bdate.year >= year1)
						{
							if (stud->_zach->_sems[k]->_subjects[j]->mark == 3)
							{
								thr_mark++;
								index[i] = i;
							}
							count_mark++;
						}
						else index[i] = -1;
					}
				}
			}
			percent = (thr_mark / count_mark) * 100;
			mass_stud[i] = percent;
			if (mass_stud[i] != mass_stud[i])
			{
				mass_stud[i] = 0;
			}
		}
	}
	else if (vib1 == vib2 && year1 == 0 && year2 == 0)
	{
		for (int i = 0; i < N; i++)
		{
			Student* stud = &((*_students)[i]);
			float count_mark = 0;
			float percent = 0;
			float thr_mark = 0;
			float temp;
			for (int k = 0; k < stud->_zach->sc; k++)
			{
				for (int j = 0; j < stud->_zach->_sems[k]->sc; j++)
				{
					if (k == vib1)
					{
						if (stud->_zach->_sems[k]->_subjects[j]->mark == 3)
						{
							thr_mark++;
						}
						count_mark++;
					}
				}
			}
			percent = (thr_mark / count_mark) * 100;
			mass_stud[i] = percent;
			if (mass_stud[i] != mass_stud[i])
			{
				mass_stud[i] = 0;
			}
			index[i] = i;
		}
	}
	else if (vib1 != -1 && vib2 != -1 && year1 == 0 && year2 == 0)
	{
		for (int i = 0; i < N; i++)
		{
			Student* stud = &((*_students)[i]);
			float count_mark = 0;
			float percent = 0;
			float thr_mark = 0;
			float temp;
			for (int k = 0; k < stud->_zach->sc; k++)
			{
				for (int j = 0; j < stud->_zach->_sems[k]->sc; j++)
				{
					if (k == vib1 || k == vib2)
					{
						if (stud->_zach->_sems[k]->_subjects[j]->mark == 3)
						{
							thr_mark++;
						}
						count_mark++;
					}
				}
			}
			percent = (thr_mark / count_mark) * 100;
			mass_stud[i] = percent;
			if (mass_stud[i] != mass_stud[i])
			{
				mass_stud[i] = 0;
			}
			index[i] = i;
		}
	}

		float t, ti;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N - i - 1; j++) {
				if (mass_stud[j] < mass_stud[j + 1]) {
					t = mass_stud[j];
					ti = index[j];

					mass_stud[j] = mass_stud[j + 1];
					index[j] = index[j + 1];

					mass_stud[j + 1] = t;
					index[j + 1] = ti;
				}
			}
		}

		cout << "\nОтсортированный массив студентов: " << endl;
		for (int i = 0; i < N; i++)
		{
			if (index[i] != -1)
			{
				cout << "\nПроцент троек у студента = " << setprecision(4) << mass_stud[i] << "%" << endl;
				(*_students)[index[i]].fullIntroduce();
				(*_students)[index[i]]._zach->showAll();
				cout << endl;
			}
		}

		delete mass_stud;
		delete index;
}