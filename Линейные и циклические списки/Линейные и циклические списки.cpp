#include<iostream>
#include <cmath>

using namespace std;

struct list {
	double count;
	list* next;
};

void AddListElem(double newListElem, list*& first) {
	list* newElem = new list;
	newElem->count = newListElem;
	newElem->next = NULL;
	if (first == NULL) {
		first = newElem;
	}
	else {
		list* tmp = first;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = newElem;
	}
}

void DeleteListElem(int nomer, list*& first) {

	if (nomer == 0) {
		list* tmp = first;
		first = first->next;
		free(tmp);
	}
	else {
		list* tmp = first;
		list* tmpDel = first;
		for (int i = 0; i < nomer - 1; i++) {
			tmp = tmp->next;
		}
		tmpDel = tmp->next;
		tmp->next = tmpDel->next;
		free(tmpDel);
	}
}


void OutputList(list*& first) {
	list* tmp = first;
	while (tmp != NULL) {
		cout << tmp->count << " ";
		tmp = tmp->next;

	}
	cout << endl;
}

void Func(list*& first, list*& listCel, list*& listDrob) {
	double cel, drob;
	list* tmp = first;
	while (tmp != NULL) {
		drob = modf(tmp->count, &cel);
		if (drob != 0) {
			AddListElem(cel, listCel);
			AddListElem(drob, listDrob);
		}
		tmp = tmp->next;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	list* per = NULL; //первый элемент изначального списка
	list* listCel = NULL; //первый элемент списка целых частей
	list* listDrob = NULL; //первый элемент списка дробных частей
	int task;
	int index;
	double tempnum;
	cout << "1-добавить элемент" << endl;
	cout << "2-удалить элемент по индексу" << endl;
	cout << "3-вывести список" << endl;
	cout << "4-выполнить задание" << endl;
	cout << "5-выход из программы" << endl;
	while (true) {
		cout << "////выберете дальнейшие действия из списка////" << endl;
		cin >> task;
		switch (task)
		{
		case 1: cout << "Введите число" << endl;
			cin >> tempnum;
			AddListElem(tempnum, per); break;
		case 2:
			cout << "Введите индекс" << endl;
			cin >> index;
			DeleteListElem(index, per); break;
		case 3:
			OutputList(per); break;
		case 4:
			Func(per, listCel, listDrob);
			cout << "Изначальный список: ";
			OutputList(per);
			cout << endl << "Cписок целых частей: ";
			OutputList(listCel);
			cout << endl << "Cписок дробный частей: ";
			OutputList(listDrob); break;
		default:
			exit(0); break;
		}
	}

	return 0;
}
