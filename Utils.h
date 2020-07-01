#pragma once
#define clean cin.clear(); cin.ignore(cin.rdbuf()->in_avail()); _flushall();
#define cls system("cls");
#define checkReturn(zn) if(tmp=="0"){cls;showStudentChangeDialog(zn);break;};
#include <string>
#include "Date.h"
#include "FilesWorker.h"
#include "StudentArray.h"
#include "LanguageDefinitions.h"
using namespace std;
string strCase(string, int);
string dateToStr(Date d);
Date parseDotDate(string);
int isValidInt(string);
int checkSpec(string, int);
string trim(string);