#include "StudentArray.h"
#include <iostream>
#include <string>
using namespace std;
StudentArray::StudentArray() {
	length = 0;
}

// Перегрузка оператора индексации
Student& StudentArray::operator[] (const int index)
{
	// есл индекс выходит за границы списка - вызвать исключение
	if (index < 0 || index >= length)
		throw out_of_range("Индекс находится за пределами списка");
	else {
		// В цикле выполняем столько итераций, какой индекс был получен
// тем самым получаем i-й элемент списка
		pCurrent = pStart;
		for (int i = 0; i < index; i++)
		{
			pCurrent = pCurrent->next_item;
		}

		return *pCurrent->val;
	}
}

StudentArray::~StudentArray() {
	for (int i = 0; i < length; i++)
	{
		pTemp = pStart->next_item;
		delete pStart->val;
		delete pStart;
		pStart = pTemp;
	}

}


void StudentArray::addItem(Student* value)
{
	pCurrent = new ListItem; // создать новый элемент списка
	pCurrent->val = value;
	if (!length)
	{
		pStart = pCurrent;
		pCurrent->previous_item = pCurrent;
		pCurrent->next_item = pCurrent;
		pTemp = pCurrent;
	}

	else
	{
		pCurrent->previous_item = pTemp;
		pCurrent->next_item = pTemp->next_item;
		pTemp->next_item = pCurrent;
		pTemp = pCurrent;
	}

	length++;
}

void StudentArray::StudentRemove(string zach) {
	pCurrent = pStart;
	for (int i = 0; i <= length; i++)
	{
		if (pCurrent->val->_zach->_num == zach)
		{
			if (i == 0) {
				pStart = pCurrent->next_item;
				pCurrent->next_item->previous_item = nullptr;
			}
			else {
				// берем в найденном элементе адрес предыдущего и в поле следующего
				// предыдущего элемента записываем значение следующего из найденного
				pCurrent->previous_item->next_item = pCurrent->next_item;
				//берем в найденном элементе адрес последующего и в поле предыдущего
				//следующего элемента записываем значение предыдущего из найденного
				pCurrent->next_item->previous_item = pCurrent->previous_item;
			}

			delete pCurrent->val;
			delete pCurrent;
			length--;
			return;
		}

		else
			pCurrent = pCurrent->next_item;
	}
}

