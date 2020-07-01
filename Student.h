#pragma once
#pragma once
#include "Person.h"
#include "Zachetka.h"
class Student : public Person {
	friend class Univer;
	friend class StudentArray;
	Date _edate;
	string _group;
	string _fac;
	string _kaf;
	Zachetka* _zach;
public:
	void fullIntroduce();
	Student(string, string, string, int, Date, string, string, string, Date, Zachetka*);
	Student(string);
	~Student();
	string dataForExport();
};
