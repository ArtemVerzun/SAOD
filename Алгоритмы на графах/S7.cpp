#include <iostream>
#include<conio.h>

using namespace std;

void poisk(int n, int m, int k, int** matr, int* mas) {
    for (int j = 0; j < m; j++)
    {

        if (matr[k][j] == 1) {
            matr[k][j] = 0;
            for (int i = 0; i < n; i++)
            {
                if (matr[i][j] == 1) {
                    matr[i][j] = 0;
                    mas[i] = 1;
                    mas[k] = 1;
                    k = i;
                    poisk(n, m, k, matr, mas);
                }
            }
        }
    }
}


int main()
{
    system("color F1");
    setlocale(LC_ALL, "rus");
    int** matr, ** mt;
    int* mas;
    int n, m, kontr = 0;
    cout << "Введите кол-во человек: ";
    cin >> n;
    matr = new int* [n];
    mt = new int* [n];
    while (1) {
        cout << "Введите кол-во знакомых: ";
        cin >> m;
        if (m >= n - 1 && m <= (n * (n - 1) / 2)) { 
            for (int i = 0; i < n; i++) { 
                matr[i] = new int[m]; 
                mt[i] = new int[m]; 
            } 
            break; 
        }
        else { cout << "Повторите ввод\n"; }
    }
    mas = new int[n + 1];

    cout << "Введите связь отношений в матрицу инцидентности:\n";
    cout << "____матрица____\n";
    cout << "\n";
    int st;
    for (int i = 0; i < n; i++)
    {
        mas[i] = 0;
        cin >> st;
        for (int j = 0; j < m; j++)
        {
            matr[i][j] = st % 10;
            st = st / 10;
            //cin>> matr[i][j];// esli >10              
            mt[i][j] = matr[i][j];
        }
    }
    cout << "_______________";
    cout << "\n";

    int k = 0;
    poisk(n, m, k, matr, mas);

    /*
    //delete[]matr;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << mt[i][j];
        }
        cout << "\n";
    }*/
    cout << "\n";
    //цикл проверки на возможность знакомств
    for (int i = 0; i < n; i++)
    {
        // std::cout << mas[i];
        if (mas[i] == 0) {
            mas[n] = 1; 
        }
    }
    if (mas[n] == 1) { 
        cout << "Невозможно всех познакомить\n"; 
    }
    else { 
        cout << "Познакомить всех возможно\n"; 
    }
}
