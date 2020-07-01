#include "Utils.h"
#include "Person.h"
#include <string>
#include <iostream>
using namespace std;
void Person::fullIntroduce() {
	cout << "Фамилия: " << this->_sname << " Имя: " << this->_fname << " Отчество: " << this->_mname << endl;
	cout << "Пол: " << (this->_gender ? "М" : "Ж") << " | День рождения: " << dateToStr(this->_bdate) << endl;
}
