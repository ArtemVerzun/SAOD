#include <iostream>
#include <ctime>
using namespace std;

const int N = 20;
const double factor = 1.247;

// заполнение массива
void fill_mas(int mas[N]) {
	for (int i = 0; i < N; i++)
		mas[i] = rand() % 100 + 1;
}

// вывод массива
void show_mas(int mas[N]) {
	for (int i = 0; i < N; i++) {
		if ((i % 10 == 0) && (i != 0))
			cout << endl;
		cout << mas[i] << "[" << i + 1 << "] ";

	}
	cout << endl;
}

// сортировка массива методом простого извлечения
void sort_mas(int mas[N]) {
	int numOfCompare = 0;    //Сравнения
	int numOfReshuffle = 0;  //Перестановки
		for (int i = N-1; i > 0; i--) {
			int Max = 0;
			for (int j=1; j <= i; j++)
			if (mas[j] > mas[Max]) 
				Max = j;
				int Tmp = mas[i];
				mas[i] = mas[Max];
				mas[Max] = Tmp;
				numOfCompare++;
				numOfReshuffle++;
		}
		
		cout << endl << "Сравнения: " << numOfCompare << " Перестановки: " << numOfReshuffle << endl << endl;
}

// подсчёт длины массива
int lenght_mas(int mas[N]) {
	int length = 0;
	for (int i = 0; i < N; i++) {
		if (mas[i] != NULL) {
			length++;
		}
	}
	return length;
}

// поиск элемента по индексу
int search_index(int key, int mas[N]) {
	if (key > N) {
		cout << "Некорректные данные" << endl;
		return 0;
	}
	else
		return mas[key - 1];
}

// поиск элемента по значение
int search_count(int key, int mas[N]) {
	int left = 0;
	int right = N;
	int middle = (right + left) / 2;
	int res = 0;
	cout << endl;
	while (true) {
		middle = (right + left) / 2;
		if (key < mas[middle]) {
			right = middle;
		}
		else if (key > mas[middle]) {
			left = middle;
		}
		else {
			res = middle;
			break;
		}
		if (left >= right) {
			cout << "Некорректные данные" << endl;
			res = 0;
			break;
		}
	}
	return res + 1;
}

// добавить элемент
void add_elem(int count, int mas[N]) {
	if (N > lenght_mas(mas)) {
		mas[0] = count;
		sort_mas(mas);
	}
	else {
		cout << "Переполнение массива" << endl;
		cout << "Для добавления элемента, необходимо удалить какое-нибудь значение " << endl;
	}
}

//количество различных чисел среди элементов массива
void task(int mas[N]) {
	int i = 1;
	int temp = 0;

	for (int i = 1; i < N; i++)
	{
		if (mas[i] != mas[i + 1])
			temp++;
	}
	cout << endl << temp << endl;
}

// удаление элемента массива
void del_elem(int key, int mas[N]) {
	mas[key] = NULL;
	sort_mas(mas);
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "Rus");

	int mas[N];
	int choose;
	int tempint;

	fill_mas(mas); 
	show_mas(mas); 
	cout << endl << "Oтсортированный массив: ";
	sort_mas(mas);
	show_mas(mas);

	while (true) {
		cout << "___________________________________________" << endl;
		cout << "1-добавить" << endl; 
		cout << "2-удалить" << endl;
		cout << "3-найти по индексу" << endl; 
		cout << "4-найти элемент" << endl; 
		cout << "5-количество различных элементов" << endl; 
		cout << "6-сгенерировать новый массив" << endl; 
		cout << "7-выход" << endl;
		cout << "Введите: ";
		cin >> choose;
		cout << "___________________________________________" << endl;
		switch (choose)
		{
		case 1:
			cout << endl << "Введите добавляемое значение:  ";
			cin >> tempint;
			add_elem(tempint, mas);
			show_mas(mas);
			break;
		case 2:
			cout << endl << "Введите индекс удаляемого элемента: ";
			cin >> tempint;
			del_elem(tempint - 1, mas);
			show_mas(mas);
			break;
		case 3:
			cout << endl << "Введите порядковый номер элемента: ";
			cin >> tempint;
			cout << endl << "Элемент : " << search_index(tempint, mas) << endl;
			break;
		case 4:
			cout << endl << "Введите элемент: ";
			cin >> tempint;
			cout << endl << "Элемент : " << search_count(tempint, mas) << endl;
			break;
		case 5:
			cout << endl << "Количество различных элементов : ";
			task(mas);
			cout << endl;
			break;
		case 6:
			cout << "Новый массив: " << endl;
			fill_mas(mas);
			show_mas(mas);
			cout << endl << "Oтсортированный массив: ";
			sort_mas(mas);
			show_mas(mas);
			break;
		case 7:
			exit(0);
			break;
		}
	}
	return 0;
}

