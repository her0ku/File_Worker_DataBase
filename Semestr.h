#pragma once
#include "Subj.h"
class Semestr
{
	friend class Student;
	friend class Zachetka;
	friend class Univer;
public:
	Subj* _subjects[10];
	int sc = 0;
	Semestr();
	int hasSubj(string);
	Subj* getByTitle(string);
	int addSubj(Subj*);
	float average();
};

