#include "Utils.h"
#include "Semestr.h"
Semestr::Semestr() {
	sc = 0;
}

//���������� �������� � �������
int Semestr::addSubj(Subj* s) {
	if (sc == 10)
		return 0;
	// ���������, ��� ������ �������� ��� �� ����������
	if (!hasSubj(s->title)) {
		_subjects[sc] = s;
		sc++;
		return sc;
	}
	return 0;
}

//�������� �������� �� �������������
int Semestr::hasSubj(string title) {
	for (int i = 0; i < sc; i++) {
		if (trim(strCase(_subjects[i]->title, 0)) == trim(strCase(title, 0))) //��������� ��� � ������ ������� � �������
			return 1;
	}
	return 0;
}

// �������� ��������� �� ������ �������� �� ��� ��������
Subj* Semestr::getByTitle(string title)
{
	for (int i = 0; i < sc; i++) {
		if (trim(_subjects[i]->title) == trim(title)) //������� ������ �������
			return _subjects[i];
	}
	return nullptr;
}
