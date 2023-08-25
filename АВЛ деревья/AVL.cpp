#include <windows.h>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
using namespace std;
struct Tree
{
	int value;
	int depth;

	Tree* left;
	Tree* right;
}*t;

struct list
{
	Tree* val;
	list* next;

	list(Tree* VAL, list* NEXT) :
		val(VAL),
		next(NEXT)
	{};
};

void	init(Tree*& head, int value = 0);
void	del_tree(Tree*& head);
void	add(Tree*& head, int value);
void	del(Tree*& head, int value);
void	print(Tree*& head, int level);
void	walk(Tree*& head);
void	task1(Tree*& head);
void	task2(Tree*& head);
Tree*& find(Tree*& head, int value);
Tree*& find_min(Tree*& head);
Tree*& find_max(Tree*& head);
Tree* find_min_depth_element(Tree*& head);
Tree* find_max_depth_element(Tree*& head);
void	list_find(Tree*& head, list*& l);
void	delete_list(list*& l);
int		depth(Tree*& head);
int		count(Tree*& head);
int		balance_factor(Tree*& head);
bool	is_find(Tree*& head, int value);
//----------------балансировка----------------
void	left(Tree*& head);
void	right(Tree*& head);
void	big_left(Tree*& head);
void	big_right(Tree*& head);
void	refresh(Tree*& head, int start_depth = 0);
void	balance(Tree*& head);
void	fix_balance(Tree*& head);
//--------------------------------------------
void	comand(Tree*& head);
bool	equal(const char a[], const char b[]);




void	init(Tree*& head, int value)
{
	head = new Tree;

	head->value = value;

	head->left = nullptr;
	head->right = nullptr;
}

//функция удаления АВЛ дерева
void	del_tree(Tree*& head)
{
	if (head->left)
	{
		del_tree(head->left);
		delete head->left;
	}
	if (head->right)
	{
		del_tree(head->right);
		delete head->right;
	}

	if (head->depth == 0) head = nullptr;
}

//функция добавления элемента в АВЛ дерево
void	add(Tree*& head, int value)
{
	if (head)
	{
		if (value == head->value)
		{
			cout << "Элемент уже сожержится в дереве\n";
			_getch();
			return;
		}
		else if (value < head->value)
			add(head->left, value);
		else
			add(head->right, value);
	}
	else
		init(head, value);

	balance(head);
	refresh(head);
}

//функция удаления элемента из АВЛ дерева
void	del(Tree*& head, int value)
{
	if (!is_find(head, value))
	{
		cout << "Указанного элемента нет в дереве\n";
		_getch();
		return;
	}

	Tree*& deleter = find(head, value);

	if (deleter->left == nullptr && deleter->right == nullptr)
	{
		delete deleter;
		deleter = nullptr;
	}
	else if (deleter->right)
	{
		Tree*& mn = find_min(deleter->right);
		deleter->value = mn->value;

		if (mn->right)
		{
			mn->value = mn->right->value;
			Tree* tmp = mn->right;
			delete tmp;
			mn->right = nullptr;
		}
		else
		{
			delete mn;
			mn = nullptr;
		}
	}
	else
	{
		deleter->value = deleter->left->value;
		delete deleter->left;
		deleter->left = nullptr;
	}

	fix_balance(head);
	refresh(head);
}

//функция вывода АВЛ дерева на экран
void	print(Tree*& ptr, int level)
{
	if (ptr != NULL)
	{
		print(ptr->right, level + 1);
		printf("\n");
		if (ptr == t)
			cout << "root-> ";
		for (int i = 0; i < level && ptr != t; i++)
			cout << "        ";
		cout << ptr->value;
		print(ptr->left, level + 1);
	}
}

//функция симметричного обхода АВЛ дерева
void	walk(Tree*& head)
{
	if (!head) return;
	walk(head->left); //обходим левое поддерево
	cout << setw(2) << head->value << ' '; //посещяем корень
	walk(head->right); // обходим правое поддерево
}

//функция балансировки элементов
void	task1(Tree*& head)
{
	Tree* mn = find_min_depth_element(head);
	Tree* mx = find_max_depth_element(head);

	while (mn->depth != mx->depth)
	{
		del(head, mn->value);
		del(head, mx->value);

		mn = find_min_depth_element(head);
		mx = find_max_depth_element(head);
	}
}

//функция вывода глубины
void  task2(Tree*& head)
{
	Tree* mn = find_min_depth_element(head);
	Tree* mx = find_max_depth_element(head);
	cout << "Глубина максимального:" << mx->depth << "\nЗначение: " << mx->value;
	cout << "\nГлубина минимального:" << mn->depth << "\nЗначение: " << mn->value;
}
Tree*& find(Tree*& head, int value)
{
	if (value == head->value) return head;
	else if (value < head->value && head->left != nullptr) return find(head->left, value);
	else if (value > head->value&& head->right != nullptr) return find(head->right, value);
}

Tree*& find_min(Tree*& head)
{
	if (head->left) return find_min(head->left);
	return head;
}

Tree*& find_max(Tree*& head)
{
	if (head->right) return find_max(head->right);
	return head;
}

Tree* find_min_depth_element(Tree*& head)
{
	list* l = nullptr;

	list_find(head, l);

	Tree* elem = l->val;

	list* tmp = l;

	while (tmp)
	{
		if (tmp->val->depth < elem->depth) elem = tmp->val;

		tmp = tmp->next;
	}

	delete_list(l);

	return elem;
}

Tree* find_max_depth_element(Tree*& head)
{
	list* l = nullptr;

	list_find(head, l);

	Tree* elem = l->val;

	list* tmp = l;

	while (tmp)
	{
		if (tmp->val->depth > elem->depth) elem = tmp->val;

		tmp = tmp->next;
	}

	delete_list(l);

	return elem;
}

void	list_find(Tree*& head, list*& l)
{
	if (!head) return;

	list_find(head->left, l);
	list_find(head->right, l);

	if (!head->left && !head->right)
	{
		list* tmp = new list(head, l);
		l = tmp;
	}
}

void	delete_list(list*& l)
{
	if (!l) return;

	delete_list(l->next);

	delete l;
}

int		depth(Tree*& head)
{
	if (!head) return 0;
	return 1 + max(depth(head->left), depth(head->right));
}

int		count(Tree*& head)
{
	int val = 0;
	val += head != nullptr;
	if (head)
	{
		val += count(head->left);
		val += count(head->right);
	}
	return val;
}

int		balance_factor(Tree*& head)
{
	if (!head) return 0;
	return depth(head->right) - depth(head->left);
}

bool	is_find(Tree*& head, int value)
{
	if (head == nullptr)		   return false;
	else if (value == head->value) return true;
	else if (value < head->value && head->left != nullptr) return is_find(head->left, value);
	else if (value > head->value&& head->right != nullptr) return is_find(head->right, value);

	return false;
}



//-------------------------балансировка-------------------------
void	left(Tree*& head)
{
	Tree* x = head;
	Tree* y = head->right;
	Tree* changer = y->left;

	y->left = x;
	x->right = changer;

	head = y;
}

void	right(Tree*& head)
{
	Tree* x = head->left;
	Tree* y = head;
	Tree* changer = x->right;

	y->left = changer;
	x->right = y;

	head = x;
}

void	big_left(Tree*& head)
{
	right(head->right);
	left(head);
}

void	big_right(Tree*& head)
{
	left(head->left);
	right(head);
}

//обновляет глубину
void	refresh(Tree*& head, int start_depth)
{
	if (!head) return;

	head->depth = start_depth;

	refresh(head->left, start_depth + 1);
	refresh(head->right, start_depth + 1);
}

void	balance(Tree*& head)
{
	if (balance_factor(head) == 2)
	{
		left(head);
		if (balance_factor(head) == -2) big_right(head);
	}
	else if (balance_factor(head) == -2)
	{
		right(head);
		if (balance_factor(head) == 2) big_left(head);
	}
}

void	fix_balance(Tree*& head)
{
	if (!head) return;

	fix_balance(head->left);
	fix_balance(head->right);

	balance(head);
}
//--------------------------------------------------------------

void	comand(Tree*& head)
{
	cout << " >> ";
	char str[255] = "";
	int value;
	cin >> str;

	if (equal(str, "1"))
	{
		cin >> value;
		add(head, value);

	}
	else if (equal(str, "2"))
	{
		cin >> value;
		del(head, value);
	}
	else if (equal(str, "7"))
	{

		print(head, 1);

		_getch();
	}
	else if (equal(str, "3"))
	{
		cin >> value;
		if (!is_find(head, value)) cout << "Элемент " << value << " не найден в дереве\n";
		else
		{
			Tree* t = find(head, value);
			cout << "Элемент " << value << " найден в дереве за " << t->depth << " шагов\n";
		}

		_getch();
	}
	else if (equal(str, "4"))
	{
		task1(head);

	}
	else if (equal(str, "5"))
	{
		task2(head);
		_getch();
	}
	else if (equal(str, "6"))
	{
		walk(head);
		_getch();
	}
	else if (equal(str, "0"))
	{
		exit(0);
	}
	else
	{

		cout << "Введена несуществующая команда!\n";
		cout << " ================================================================================\n"
			<< " |1- добавить число в АВЛ дерево                                                |\n"
			<< " |2- удалить число из АВЛ дерева                                                |\n"
			<< " |3- поиск числа в АВЛ дереве                                                   |\n"
			<< " |4- балансировка элементов путём удаления максимального и минимального листа   |\n"
			<< " |5- вывод глубины и значений максимального и минимального листа                |\n"
			<< " |6- симметричный обход дерева с выводом очерёдности обхода вершин на экран     |\n"
			<< " |7- вывод АВЛ дерева                                                           |\n"
			<< " |0- выход из программы                                                         |\n";
		cout << " ================================================================================\n";

		_getch();
	}
}

bool	equal(const char a[], const char b[])
{
	for (int i = 0; i < 255; i++)
	{
		if (a[i] != b[i]) return false;
		if (a[i] == '\0') return true;
	}
	return true;
}

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(NULL));

	while (true)
	{
		system("cls");
		print(t, 1);
		cout << "\n\n";
		cout << " ================================================================================\n"
			<< " |1- добавить число в АВЛ дерево                                                |\n"
			<< " |2- удалить число из АВЛ дерева                                                |\n"
			<< " |3- поиск числа в АВЛ дереве                                                   |\n"
			<< " |4- балансировка элементов путём удаления максимального и минимального листа   |\n"
			<< " |5- вывод глубины и значений максимального и минимального листа                |\n"
			<< " |6- симметричный обход дерева с выводом очерёдности обхода вершин на экран     |\n"
			<< " |7- вывод АВЛ дерева                                                           |\n"
			<< " |0- выход из программы                                                         |\n";
		cout << " ================================================================================\n";
		cout << "\n";
		comand(t);
	}

	del_tree(t);

	return 0;
}