#include "Utils.h"
#include "Semestr.h"
Semestr::Semestr() {
	sc = 0;
}

//добавление предмета в семестр
int Semestr::addSubj(Subj* s) {
	if (sc == 10)
		return 0;
	// проверяет, что такого предмета еще не существует
	if (!hasSubj(s->title)) {
		_subjects[sc] = s;
		sc++;
		return sc;
	}
	return 0;
}

//проверка предмета на существование
int Semestr::hasSubj(string title) {
	for (int i = 0; i < sc; i++) {
		if (trim(strCase(_subjects[i]->title, 0)) == trim(strCase(title, 0))) //переводим все в нижний регистр и тримаем
			return 1;
	}
	return 0;
}

// получить указатель но объект предмета по его названию
Subj* Semestr::getByTitle(string title)
{
	for (int i = 0; i < sc; i++) {
		if (trim(_subjects[i]->title) == trim(title)) //тримаем лишние пробелы
			return _subjects[i];
	}
	return nullptr;
}
