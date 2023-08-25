#include <iostream>

struct Task {
	uint16_t priority; //приоритет
	uint16_t taskTime; //момент поступления
	uint16_t durationTime; //время выполнения
	uint16_t* ind; //индикатор занятости
};
//список задач
struct TaskList {
	Task* taskValues;
	TaskList* next;
};

const int N = 1; //размер очереди

//фу-я добавления задачи в очередь
void pushToQueue(TaskList*& IncomingTask, Task Queue[], bool& emptyQueue, bool& allTasksGone) {
	emptyQueue = false; //очередь не пустая
	if (IncomingTask != NULL) //список задач не пуст
	{
		for (int i = 0; i < N; i++) {
			if (Queue[i].ind == NULL) // если не занято
			{
				Queue[i].durationTime = IncomingTask->taskValues->durationTime; //добавляем 
				Queue[i].priority = IncomingTask->taskValues->priority;         //характеристики
				Queue[i].taskTime = IncomingTask->taskValues->taskTime;         //задач
				Queue[i].ind = &Queue[i].priority;
				IncomingTask = IncomingTask->next; //переход к следующей задачи
				emptyQueue = false; //очередь не пуста
				break;
			}
		}
		//проверка на переполнение
		/*if (Queue[N - 1].ind != NULL) {
			std::cout << "Переполнение очереди!!!";
			exit(1);
		}*/
	}
	if (IncomingTask == NULL) //если список задач пуст
		allTasksGone = true;
	else allTasksGone = false;
}

//фу-я добавления задачи в стек
void pushToStack(TaskList*& Stack, Task*& OurProcessor, bool& emptyStack, bool& processorIsFree) {
	processorIsFree = true; //процессор свободен
	//Стек - односвязный линейный список
	TaskList* p = new TaskList;
	Task* t = new Task;
	t->durationTime = OurProcessor->durationTime; //передача
	t->priority = OurProcessor->priority;         //характеристик
	t->taskTime = OurProcessor->taskTime;         //задач
	p->taskValues = t;
	//проверка, является ли список пустым
	if (Stack == NULL) {
		p->next = NULL; //первый элемент
	}
	else//если существует
	{
		p->next = Stack; //добавление в начало
	}
	Stack = p;
	emptyStack = false; //стек не пустой
}

//фу-я взятия задачи из очереди
void getFromQueue(Task Queue[], Task*& OurProcessor, bool& emptyQueue, bool& processorIsFree) {
	processorIsFree = false; //процессор не свободен
	if (Queue[0].ind == NULL) //если 1й элемен пустой
		emptyQueue = true; //очередь пуста
	for (int i = N - 1; i > -1; i--) //с конца очереди
	{
		if (Queue[i].ind != NULL) //если элемент не пустой
		{
			OurProcessor->durationTime = Queue[i].durationTime; //передача
			OurProcessor->priority = Queue[i].priority;         //храктеристик задач
			OurProcessor->taskTime = Queue[i].taskTime;         //в процессор
			Queue[i].ind = NULL; //обнуляем элемент
			Queue[i].durationTime = 0; // и все
			Queue[i].priority = 0;     //характеристики
			Queue[i].taskTime = 0;     //задач
			processorIsFree = false;   //процессор не пустой
			if (Queue[0].ind == NULL)  //если 1й элемент очереди пуст
				emptyQueue = true; //очередь пуста
			return;
		}
	}
	if (Queue == NULL)
		emptyQueue = true; //если список после удаления оказался пуст 
	else emptyQueue = false;
}

//фу-я взятия задачи из стека
void getFromStack(TaskList*& Stack, Task*& OurProcessor, bool& emptyStack, bool& processorIsFree) {
	processorIsFree = false; //процессор не свободен
	TaskList* temp, * p;
	temp = Stack; //элемент стека
	if (temp->next == NULL) //если следующий элемент пуст
	{
		OurProcessor->durationTime = temp->taskValues->durationTime; //передача
		OurProcessor->priority = temp->taskValues->priority;         //характеристик задач
		OurProcessor->taskTime = temp->taskValues->taskTime;         //в процессор
		Stack = NULL; //стек пуст
		emptyStack = true;

		return;
	}
	//пока следующий элемент не пуст
	while (temp->next != NULL) {
		p = temp;
		temp = temp->next; //идем по стеку
		if (temp->next == NULL) //ести элемент следующий пуст
		{
			OurProcessor->durationTime = temp->taskValues->durationTime; //передача
			OurProcessor->priority = temp->taskValues->priority;         //характеристик задач
			OurProcessor->taskTime = temp->taskValues->taskTime;         //в процессор
			p->next = NULL;
		}
	}

	if (Stack == NULL)
		emptyStack = true; //если список после удаления оказался пуст
	else emptyStack = false;

}

//фу-я показывает содержание очередей
void showStruct(Task Queue[]) {
	int i = 0;
	while (Queue[i].ind != NULL) //пока элемент не пуст
	{
		std::cout << "Время поступления задачи " << Queue[i].taskTime << " Приоритет задачи ";
		std::cout << Queue[i].priority << " Такты задачи " << Queue[i].durationTime << std::endl;
		i++;
	}
}

//фу-я показывает содержание стека
void showStack(TaskList* STRUCT) {
	TaskList* p = STRUCT;
	while (p != NULL) //пока элемент не пуст
	{
		std::cout << "Время поступления задачи " << p->taskValues->taskTime << " Приоритет задачи ";
		std::cout << p->taskValues->priority << " Такты задачи " << p->taskValues->durationTime << std::endl;
		p = p->next;
	}
}

//фу-я показывает содержание процессора
void showStructElem(Task* OurProcessor) {
	std::cout << "Время поступления задачи " << OurProcessor->taskTime << " Приоритет задачи ";
	std::cout << OurProcessor->priority << " Такты задачи " << OurProcessor->durationTime << std::endl;
}

//фу-я работы процессора
void processorLoop(TaskList*& IncomingTask, Task Queue0[], Task Queue1[], Task Queue2[]) {
	TaskList* Stack = NULL;
	Task* OurProcessor = new Task;
	OurProcessor->priority = 0; //нулевой приоритет
	OurProcessor->durationTime = 0; //нулевой такт
	bool emptyQueue0 = true; //Проверка пустоты очередей
	bool emptyQueue1 = true;
	bool emptyQueue2 = true;
	bool emptyStack = true; //Проверка пустоты стека
	bool processorIsFree = true; //Проверка занятости процессора
	bool allTasksGone = false;//проверка пустоты списка задач
	int timer = 1; //таймер
	while (true) {
		if (!allTasksGone) //пока не все задачи выполнены
		{
			if (IncomingTask->taskValues->taskTime == timer) //если совпал таймер с временем поступления
			{
				if (IncomingTask->taskValues->priority == 3)//3-высокий приоритет
					pushToQueue(IncomingTask, Queue0, emptyQueue0, allTasksGone); //добавдение в очередь по приоритету
				else if (IncomingTask->taskValues->priority == 2)
					pushToQueue(IncomingTask, Queue1, emptyQueue1, allTasksGone);
				else if (IncomingTask->taskValues->priority == 1)//1-низкий приоритет
					pushToQueue(IncomingTask, Queue2, emptyQueue2, allTasksGone);
			}
		}
		if (!emptyQueue0) //если не пустая очередь
		{
			if (Queue0->priority > OurProcessor->priority || processorIsFree) //если приоритет из очереди больше приоритета из процессора или процессор свободен
			{
				if (OurProcessor->durationTime > 0) //если такт больше 0
					pushToStack(Stack, OurProcessor, emptyStack, processorIsFree); //добавление в стек
				getFromQueue(Queue0, OurProcessor, emptyQueue0, processorIsFree); //взятие из очереди
			}
		}
		if (!emptyQueue1) {
			if (Queue1->priority > OurProcessor->priority || processorIsFree) {
				if (OurProcessor->durationTime > 0)
					pushToStack(Stack, OurProcessor, emptyStack, processorIsFree);
				getFromQueue(Queue1, OurProcessor, emptyQueue1, processorIsFree);
			}
		}
		if (!emptyQueue2) {
			if (Queue2->priority > OurProcessor->priority || processorIsFree) {
				if (OurProcessor->durationTime > 0)
					pushToStack(Stack, OurProcessor, emptyStack, processorIsFree);
				getFromQueue(Queue2, OurProcessor, emptyQueue2, processorIsFree);
			}
		}
		//если стек не пустой и пустые очереди
		if (!emptyStack && emptyQueue0 && emptyQueue1 && emptyQueue2) {
			if (processorIsFree) //процессор свободен
				getFromStack(Stack, OurProcessor, emptyStack, processorIsFree); //взять задачу из стека
		}
		std::cout << std::endl << "Идет " << timer << " такт" << std::endl;
		//если не пустой список
		if (!allTasksGone) {
			std::cout << "Входные задания" << std::endl;
			showStack(IncomingTask); //показать список задач
		}
		//если не пустой стек, показать содержимое
		if (!emptyStack) {
			std::cout << "Содержимое стэка" << std::endl;
			showStack(Stack);
		}
		//если не пустые очереди, показать содержимое
		if (!emptyQueue0) {
			std::cout << "Содержимое очереди 0" << std::endl;
			showStruct(Queue0);
		}
		if (!emptyQueue1) {
			std::cout << "Содержимое очереди 1" << std::endl;
			showStruct(Queue1);
		}
		if (!emptyQueue2) {
			std::cout << "Содержимое очереди 2" << std::endl;
			showStruct(Queue2);
		}
		//если процессор занят, показать содержимое
		if (!processorIsFree) {
			std::cout << "Содержимое процессора" << std::endl;
			showStructElem(OurProcessor);
		}
		else
			std::cout << "Процессор свободен" << std::endl;
		//если процессор занят
		if (!processorIsFree) {
			if (OurProcessor->durationTime)
				OurProcessor->durationTime--; //уменьшить такт
			if (OurProcessor->durationTime <= 0) //если такт меньше 0
			{
				OurProcessor->durationTime = 0; //обнуляем такт
				OurProcessor->priority = 0; //обнуляем приоритет
				processorIsFree = true; //процессор свободен
			}
		}
		timer++; //таймер идет
		if (emptyStack && processorIsFree && allTasksGone && emptyQueue0 && emptyQueue1 && emptyQueue2)
			break; //если все свободно, завершаем
	}
	IncomingTask = NULL; //список задач пуст
}

int main() {

	setlocale(LC_ALL, "rus");

	int n; //кол-во задач
	uint16_t prior; //приоритет
	uint16_t taskT; //время поступления
	uint16_t durationT; //такт
	TaskList* IncomingT = NULL; //список задач
	TaskList* cur = NULL; //текущий элемент
	int a;


		std::cout << "Введите количество задач их момент постуления, длительность выполнения, приоритет. \n\n";
		std::cout << "Количество задач: \n";
		std::cin >> n;

		//инициализация списка
		//заполнение IncomingTask

		for (int i = 0; i < n; i++) {
			std::cout << " Время поступления задачи " << i + 1 << ": \n";
			std::cin >> taskT;
			std::cout << " Такты задачи " << i + 1 << ": " << std::endl;
			std::cin >> durationT;
			std::cout << " Приоритет задачи " << i + 1 << ": \n";
			std::cin >> prior;

			TaskList* p = new TaskList;
			Task* t = new Task;
			t->durationTime = durationT;
			t->priority = prior;
			t->taskTime = taskT;
			p->taskValues = t;

			//проверка, является ли список пустым
			if (IncomingT == NULL) {
				p->next = NULL;
				IncomingT = p;
			}
			else {
				p->next = NULL;
				cur->next = p;
			}
			cur = p;
		}
		

	Task Queue0[N];//массив структур, очередь 1
	for (int i = 0; i < N; i++)
		Queue0[i].ind = NULL;

	Task Queue1[N];//массив структур, очередь 2
	for (int i = 0; i < N; i++)
		Queue1[i].ind = NULL;

	Task Queue2[N];//массив структур, очередь 3
	for (int i = 0; i < N; i++)
		Queue2[i].ind = NULL;

	processorLoop(IncomingT, Queue0, Queue1, Queue2); //фу-я работы процессора

	std::cout << std::endl;
	system("pause");
	return 0;
}
