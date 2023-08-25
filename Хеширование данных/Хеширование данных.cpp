#include<iostream>
#include<string>
#include<ctime>
#include <fstream>
#include<vector>

using namespace std;                                          //     цццБцц |  2500  |  Двойное хеширование |

//const int numofsector = 2500;
//const int numofkey = 5000;

const int numofsector = 10; // кол-во сегментов таблицы
const int numofkey = 12;    // кол-во ключей

//Функция генерирования ключа
void gener_key(string key[numofkey]) {
	for (int i = 0; i < numofkey; i++) {
		string str;
		str += char(48 + (rand() + clock()) % 10);  //цифра
		str += char(48 + (rand() + clock()) % 10);  //цифра
		str += char(48 + (rand() + clock()) % 10);  //цифра
		str += char(65 + (rand() + clock()) % 26);  //буква
		str += char(48 + (rand() + clock()) % 10);  //цифра
		str += char(48 + (rand() + clock()) % 10);  //цифра
		key[i] = str;
	}
}

//Функция вывода на экран 
void show_key(string key[numofkey]) {
	for (int i = 0; i < numofkey; i++) {
		cout << key[i] << " ";
	}
}

//хеш-функция 
int creat_key(string key) {
	int k_int;
	k_int = ((int)key[0] * (int)key[1] + (int)key[2] * (int)key[3] + (int)key[4] * (int)key[5]) % numofsector;
	return k_int;
}

//вторая хеш-функция
int creat_key2(string key) {
	int k_int;
	k_int = 3 - (((int)key[0] * (int)key[1] + (int)key[2] * (int)key[3] + (int)key[4] * (int)key[5]) % 3);
	return k_int;
}

//создание таблицы для проверки
void creat_tab_check(string tab[numofsector], string key[numofkey], int kol[numofsector]) {
	for (int i = 0; i <= numofsector + 1; i++) {
		string prm = key[i];
		int kprm = creat_key(prm);
		tab[kprm] = tab[kprm] + ' ' + key[i];
		kol[kprm] ++;
	}
}

//Функция вывода таблицы на экран
void show_tab_check(string tab[numofsector]) {
	for (int i = 0; i < numofsector; i++) {
		cout << "\n" << i << ": " << tab[i];
	}
}

//заполнение файла 
void  outTab(int kol[numofsector]) {
	std::ofstream out("C:\\User\\Рабочий стол\\Структуры и Алгоритмы Обработки Данных\\lab4.txt");
	for (int i = 0; i < numofsector; i++) {
		out << i << " : " << kol[i] << endl;
	}
	out.close();
}


//Функция добавления элемента в хеш-таблицу
void add_num(string num, string tab[numofsector], string garbage[numofsector]) {
	int prm_key = creat_key(num);
	bool gar = 1;
	if (tab[prm_key].empty())
		tab[prm_key] = num;

	else if (tab[prm_key] == "delete")
		tab[prm_key] = num;

	else {
		gar = 1;
		int prm_key2 = creat_key2(num);
		for (int i = 1; i <= numofsector + 1; i++) {
			if (tab[(prm_key + i * prm_key2) % numofsector].empty()) {
				tab[(prm_key + i * prm_key2) % numofsector] = num;
				gar = 0;
				break;
			}
		}
		if (gar) {
			garbage[prm_key] = tab[prm_key];
			tab[prm_key] = num;
		}
	}
}

//Функция поиска элемента в таблице
void sear_elem(string num, string tab[numofsector]) {
	int prm_key = creat_key(num);
	if (tab[prm_key] == num)
		cout << "\nЭлемент " << num << " хранится под ключом: " << prm_key << endl;

	else if (tab[prm_key] == "delete") {

		int prm_key2 = creat_key2(num);
		for (int i = 1; i <= numofsector + 1; i++) {

			if (tab[(prm_key + i * prm_key2) % numofsector] == num) {
				cout << "\nЭлемент " << num << " хранится под ключом: " << ((prm_key + i * prm_key2) % numofsector) << endl;
				break;
			}
			else if (tab[(prm_key + i * prm_key2) % numofsector].empty()) {
				cout << "\nЭлемент " << num << " не найден." << endl;
				break;
			}

		}
	}
	else
		cout << "\nЭлемент " << num << " не найден." << endl;
}

//Функция вывода элемента 
void sear_key(string tab[numofsector]) {
	cout << "Введите номер ключа: ";
	int nk;
	cin >> nk;
	if ((nk < 0) || (nk > (numofsector - 1)))
		cout << "\nТакого ключа не существует.";
	else if (tab[nk] == "delete")
		cout << "\nПод данным ключем не хранится элемент";
	else
		cout << "Под ключом " << nk << " хранится элемент: " << tab[nk];
}

//Функция удаления элемента из таблицы
void del_num(int key, string tab[numofsector], string garbage[numofsector]) {
	tab[key].clear();
	tab[key] = "delete";
}

//Функция заполнения таблицы 
void creat_tab(string tab[numofsector], string key[numofkey], string garbage[numofsector]) {
	for (int i = 0; i < numofkey; i++) {
		string prmnum = key[i];
		add_num(prmnum, tab, garbage);
	}
}

//Функция вывода таблицы на экран 
void show_tab(string tab[numofsector]) {
	cout << endl;
	for (int i = 0; i < numofsector; i++) {
		cout << i << ": " << tab[i] << "\n";
	}
}


int main() {
	setlocale(LC_ALL, "rus");

	string key[numofkey];
	string tab[numofsector];
	string tab2[numofsector];
	string garbage[numofsector];
	int kol[numofsector] = { 0 };

	gener_key(key);
	//show_key(key);

	//cout << "\n\n============================================";
	//cout << "\nНе отсортированная хеш-таблица:" << endl;

	creat_tab_check(tab, key, kol);
	show_tab_check(tab);

	//outTab(kol);

	cout << "\n\n============================================";
	cout << "\nСозданная хеш-таблица:" << endl;
	creat_tab(tab2, key, garbage);
	show_tab(tab2);

	int n = -1;
	while (n != 0) {
		cout << endl <<
			"1 - Удалить ключ" << endl <<
			"2 - Добавить элемент" << endl <<
			"3 - Поиск ключа элемента" << endl <<
			"4 - Поиск элемента по номеру ключа" << endl <<
			"5 - Вывести таблицу" << endl <<
			"0 - Закончить выполнение программы\nВыберете действие: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> n;

		switch (n) {
		case 1: {
			cout << "\n\n=============================================================================";
			cout << "\nВведите количество ключей, которое надо будет удалить: ";
			int kolk;
			cin >> kolk;
			for (int i = 0; i < kolk; i++) {
				cout << "\nВведите ключ для удаления: ";
				int key_for_del;
				cin >> key_for_del;
				del_num(key_for_del, tab2, garbage);
			}
			break;
		}
		case 2: {
			cout << "\n\n=============================================================================";
			cout << "\nВведите число, которое хотите добавить (цццБцц): \n";
			string num;
			bool t = 1;
			cout << "Ввод ключа. Для выхода наберите EXIT\n";
			cout << " -> ", cin >> num;
			if (num[0] == 'E')
				if (num[1] == 'X')
					if (num[2] == 'I')
						if (num[3] == 'T')
							break;
			for (int j = 0; j < 6; j++) {
				if (j == 3)
					if (isalpha(num[j])) { t = true; }
					else { t = false; break; }
				else if (j == 0 || j == 1 || j == 2 || j == 4 || j == 5)
					if (isdigit(num[j])) { t = true; }
					else { t = false; break; }
				else { t = false; break; }
			}
			if (t == true) {
				add_num(num, tab2, garbage);
			}
			else { cout << "Ошибка, ключ введен не корректно \n"; break; }
			break;
		}
		case 3: {
			cout << "\n\n=============================================================================";
			cout << "\nВведите элемент, котовый хотите найти: ";
			string num;
			cin >> num;
			sear_elem(num, tab2);
			break;
		}
		case 4: {
			cout << "\n\n=============================================================================" << endl;
			sear_key(tab2);
			break;
		}
		case 5: {
			cout << "\n\n=============================================================================";
			cout << "\nХеш-таблица: " << endl;
			show_tab(tab2);
			break;
		}
		}
	}
	return 0;
}