#include <iostream>
#include <ctime>
#include <stdlib.h>


using namespace std;

int KolChet(int* C, int x);
int Krat(int* B, int y);


int KolChet(int* C, int x)
{
    int sum = 0;
    for (int i = 0; i < x; i = i + 1)
    {
        if ((C[i] % 2) == 0 && (C[i]!=0))
        {
            sum += 1;
        }        
    }
    cout << "Количество четных элементов в массиве: " << sum << "\n";
    return sum;
}

int computeOut(int A) {
    return A;
}

int Krat(int* B, int y)
{
    cout << "Элементы кратные 10, уменьшенные на один порядок: \n";
    for (int i = 0; i < y; i = i + 1)
    {
        if ((B[i] % 10) == 0)
        {
            B[i] = B[i] / 10;
            cout << "A[" << i << "]= " << B[i] << endl;
        } 
        
    }
    return 0;
}


int main ()
{
    
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    int* A = new int[n];
    cout << "Заполнение массива: \n";
    int sum = 0;
    for (int i = 0; i < n; i = i + 1) {
          A[i] = 0 + rand() % n - ((n / 2) - 1);
          cout << "A[" << i << "]= " << A[i] << endl;
          
    }
    

  int Key_board = 0;

  while (Key_board == 0) 
  {
    cout << "\n";
    cout << "Меню: \n";
    cout << "Введите 1, если хотите подсчитать кол-во четных элементов в массиве. \n";
    cout << "Введите 2, если хотите уменьшить все значения кратные 10 на один порядок. \n";
    cout << "Введите 3, если хотите выйти из прграммы. \n";
    cout << "Ввод: ";
    cin >> Key_board;
    cout << "\n";
    int s;
    switch (Key_board)
    {
        case 1: 
        {
            //
            sum = KolChet(A, n);
            cout << computeOut(sum);;
            int Key_board_2 = 0;
            cout << "Нажмите 1, чтобы венуться в меню. \n";
            cout << "Нажмите 2, чтобы выйти из программы. \n";
            cout << "Ввод: ";
            while (Key_board_2 == 0)
            {
                cin >> Key_board_2;
                switch (Key_board_2)
                {
                    case 1: 
                    {
                        Key_board = 0;
                        break;
                    }
                    case 2:
                    {
                        cout << "Осуществляется выход из программы.\n" << endl;
                        exit(EXIT_SUCCESS);
                        break;
                    }
                    default:
                    {
                        cout << "Ошибка! Запрос введен некорректно.\n";
                        cout << "Повторите ввод! \n";
                        cout << "Ввод: ";
                        Key_board_2 = 0;
                        break;
                    }
                }
            }
            break;
        }
        case 2:
        {
            Krat(A, n);
            int Key_board_1 = 0;
            cout << "Нажмите 1, чтобы венуться в меню. \n";
            cout << "Нажмите 2, чтобы выйти из программы. \n";
            cout << "Ввод: ";
            while (Key_board_1 == 0)
            {
                cin >> Key_board_1;
                switch (Key_board_1)
                {
                    case 1:
                    {
                        Key_board = 0;
                        break;
                    }
                    case 2:
                    {
                        cout << "Осуществляется выход из программы.\n" << endl;
                        exit(EXIT_SUCCESS);
                        break;
                    }
                    default:
                    {
                        cout << "Ошибка! Запрос введен некорректно. \n";
                        cout << "Повторите ввод! \n";
                        cout << "Ввод: ";
                        Key_board_1 = 0;
                        break;
                    }
                }
            }
            break;
        }
        case 3:
        {
            cout << "Осуществляется выход из программы.\n" << endl;
            exit(EXIT_SUCCESS);
            break;
        }
        default:
        {
            cout << "Ошибка! Запрос введен некорректно. \n";
            cout << "Повторите ввод! \n";
            cout << "Ввод: ";
            Key_board = 0;
            break;
        }
    }
  }
  delete[] A;
  return 0;
}

