// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <locale.h>
#include <ctime> 
using namespace std;

int main() {
    srand(time(0));
    setlocale(0, "");
    int mas[6][6] = //исходный массив
    {
      {256,272,288,304,-36,336},
      {272,289,304,323,340,-38},
      {288,306,324,342,360,378},
      {304,323,342,361,380,399},
      {-36,340,360,380,400,420},
      {336,-38,378,399,420,441}
    };
    int row = sizeof(mas) / sizeof(mas[0]);//количество строк (изменяются во время работы)
    int col = sizeof(mas[0]) / sizeof(mas[0][0]);//количество столбцов (изменяются во время работы)
    int row2 = row;//количество строк (не изменяются во время работы)
    int col2 = col;//количество столбцов (не изменяются во время работы)
    double max = 0, min = 0, y = 0;
    int max_sh = 0, min_sh = 0, itr = 0, str = 0, itr_sh = 1;
    int count_select = 0, count_str = 0, column_array = col;
    int row_array = row, del_str = 0;
    double* strA2 = new double[row2]; //массивы используемые для рассчета стратегий
    double* strB2 = new double[col2];
    for (int j = 0; j < row2; j++) 
    {
        strA2[j] = 7; 
    }
    for (int j = 0; j < col2; j++) 
    { 
        strB2[j] = 7; 
    }
    int** mas1 = new int* [row];
    int** mas2 = new int* [row_array];//создание нового масива под доминирующие строки
    for (int i = 0; i < row_array; i++) //создание массива в который копируется исходный
    {
        mas1[i] = new int[col];
        mas2[i] = new int[col];
    }
    cout << "Исходная матрица:" << endl;
    for (int i = 0; i < row; i++) //копирование и вывод исходного массива
    {
        for (int j = 0; j < col; j++)
        {
            mas1[i][j] = mas[i][j];
            cout << mas1[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    for (int check_i = row - 1; check_i >= 0; check_i--) //поиск не доминирующих строк и их обнуление
    {
        for (int i = row - 1; i >= 0; i--)
        {
            for (int j = 0; j < col; j++)
            {
                if (check_i == i) 
                { 
                    continue; 
                }
                if (mas1[check_i][j] == 0) 
                { 
                    continue; 
                }
                else 
                {
                    if (mas1[check_i][j] == mas1[i][j] || mas1[check_i][j] < mas1[i][j]) 
                    { 
                        count_select++; 
                    }
                }
            }
            if (count_select == col)
            {
                for (int j = 0; j < col; j++) 
                { 
                    mas1[check_i][j] = 0; 
                }
                row_array--;
            }
            count_select = 0;
        }
    }
    for (int i = 0; i < row; i++) //создание массива с доминирующими строками
    {
        for (int j = 0; j < col; j++)
        {
            if (mas1[i][j] == 0)
            {
                strA2[i] = 0;
                count_select++;
            }
        }
        if (count_select != col)
        {
            for (int j = 0; j < col; j++) 
            { 
                mas2[count_str][j] = mas1[i][j]; 
            }
            count_str++;
        }
        count_select = 0;
    }

    for (int i = 0; i < row; i++) // очистка массива
    {
        delete[] mas1[i]; 
    }
    row = row_array; //декрементируем строки
   
    for (int check_i = 0; check_i < col; check_i++) //поиск не доминирующих столбцов и их обнуление
    {
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < row; j++)
            {
                if (check_i == i) 
                { 
                    continue; 
                }
                if (mas2[j][i] == 0) 
                { 
                    continue; 
                }
                else 
                { 
                    if (mas2[j][check_i] == mas2[j][i] || mas2[j][check_i] > mas2[j][i]) 
                    {
                        count_select++; 
                    }
                }
            }
            if (count_select == row)
            {
                for (int j = 0; j < row; j++)
                {
                    mas2[j][check_i] = 0;
                }
                column_array--;
            }
            count_select = 0;
        }
    }

    mas1 = new int* [row];//создание нового массива
    for (int i = 0; i < row_array; i++)
    {
        mas1[i] = new int[column_array];
    }
    int count_col = 0;
    for (int i = 0; i < col; i++) //создание массива с доминирующими столбцами
    {
        for (int j = 0; j < row; j++)
        {
            if (mas2[j][i] == 0)
            {
                strB2[i] = 0;
                count_select++;
            }
        }
        if (count_select != row)
        {
            for (int j = 0; j < row; j++)
            { 
                mas1[j][count_col] = mas2[j][i]; 
            }
            count_col++;
        }
        count_select = 0;
    }

    for (int i = 0; i < row; i++) 
    { 
        delete[] mas2[i]; 
    }
    col = column_array;

    cout << "Упрощенная матрица:" << endl;  //вывод массива с доминирующими строками и столбцами
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << mas1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "Введите количество итераций: ";
    cin >> itr;
    cout << "Выберете стратегию игрока  B(1-" << col << "): ";
    cin >> str;
    str--;

    int* A = new int[row]; //массивы под выбранные стратегии игроков, их проигрыши и выйгрыши (должны быть именно здесь)
    int* SA = new int[row];
    int* B = new int[col];
    int* SB = new int[col];
    double* strA = new double[row]; //окончательный массив игрока A
    double* strB = new double[col]; //окончательный массив игрока B

    for (int i = 0; i < row; i++)
    {
        strA[i] = 0;
        A[i] = 0;
        SA[i] = 0;
    }
    for (int i = 0; i < col; i++)
    {
        strB[i] = 0;
        B[i] = 0;
        SB[i] = 0;
    }

    int LA = (itr == 0) ? 1 : 1+(int)ceil(log10(abs(itr) + 0.5)); // переменные для setw() (строка названий столбцов в итерационном методе) 
    int LB = row + (row - 1) + 4;
    int LC = col + (col - 1) + 4;
    int LD = row * 4 + (row - 1);
    int LE = col * 4 + (col - 1) + 3;
    int LF = 6 + 2;
    int LG = 6 + 2;
    int LI = 6 + 2;
    int sum_L = LA + LB + LC + LD + LE + LF + LG + LI; //сумма всех setw() для вывода "-"
    cout << endl << setw(LA) << "N" << setw(LB) << "strA" << setw(LC) << "strB" << setw(LD) << "Sa" << setw(LE) << "Sb" << setw(LF) << "y_" << setw(LG) << "y-" << setw(LI) << "y*" << endl;
    for (int i = 0; i < sum_L; i++)
    {
        cout << "-";
    }
    cout << endl;

    B[str] = 1;
    while (itr_sh <= itr) //итерационный метод
    {
        for (int i = 0; i < row; i++)
        {
            if (itr_sh == 1)
            {
                SA[i] = mas1[i][str];
            }
            else
            {
                SA[i] = SA[i] + mas1[i][str];
            }
        }
        max = SA[0];
        for (int i = 0; i < row; i++)
        {
            if (max < SA[i])
            {
                max = SA[i];
                max_sh = i;
            }
            if (max == SA[0])
            {
                max_sh = 0;
                max = SA[0];
            }
        }

        A[max_sh] = 1;
        if (itr_sh != 1) 
        { 
            strA[max_sh] = strA[max_sh] + 1; 
        }

        for (int i = 0; i < col; i++)
        {
            if (itr_sh == 1)
            {
                SB[i] = mas1[max_sh][i];
            }
            else
            {
                SB[i] = SB[i] + mas1[max_sh][i];
            }
        }

        if (itr_sh != 1)
        {
            B[min_sh] = 1;
            strB[min_sh] = strB[min_sh] + 1;
        }
        min = SB[0];
        for (int i = 0; i < col; i++)
        {
            if (min > SB[i])
            {
                min = SB[i];
                min_sh = i;
            }
            if (min == SB[0])
            {
                min_sh = 0;
                min = SB[0];
            }
        }
        y = ((min / itr_sh) + (max / itr_sh)) / 2;
       cout << setw(4) << itr_sh << "  ";
        for (int i = 0; i < row; i++)
        {
            cout << A[i] << " ";
            A[i] = 0;
        }
        cout << "  ";
        for (int i = 0; i < col; i++)
        {
            cout << B[i] << " ";
            B[i] = 0;
        }
        cout << "  ";
        for (int i = 0; i < row; i++) 
        { 
            cout << setw(4) << SA[i] << " "; 
        }
        cout << "  ";
        for (int i = 0; i < col; i++) 
        { 
            cout << setw(4) << SB[i] << " "; 
        }
        cout << fixed << setw(6) << setprecision(1) << max / itr_sh << " " << setw(6) << min / itr_sh << " " << setw(6) << y << endl;
        str = min_sh;
        itr_sh++;
    }
    for (int i = 0; i < sum_L; i++) 
    { 
        cout << "-"; 
    }
    for (int i = 0; i < row; i++) 
    { 
        strA[i] = strA[i] / itr; 
    }
    for (int i = 0; i < col; i++) 
    { 
        strB[i] = strB[i] / itr; 
    }
   
    int countRowCol_strAB = 0;
    for (int i = 0; i < row2; i++)
    {
        if (strA2[i] == 7)
        {
            strA2[i] = strA[countRowCol_strAB];
            countRowCol_strAB++;
        }
    }
    countRowCol_strAB = 0;
    for (int i = 0; i < col2; i++)
    {
        if (strB2[i] == 7)
        {
            strB2[i] = strB[countRowCol_strAB];
            countRowCol_strAB++;
        }
    }
    cout << endl << endl << "Результат:" << endl;
    cout << "p= (";
    for (int i = 0; i < row2; i++)
    {
        cout << fixed << setw(5) << setprecision(3) << strA2[i] << "; ";
    }
    cout << ")" << endl;
    cout << "q= (";
    for (int i = 0; i < col2; i++)
    {
        cout << fixed << setw(5) << setprecision(3) << strB2[i] << "; ";
    }
    cout << ")" << endl;
    cout << "y= " << y << endl;
    delete[] strA2;
    delete[] strB2;
    delete[] strA;
    delete[] strB;
    for (int i = 0; i < row; i++) 
    { 
        delete[] mas1[i]; 
    }
    cout << endl;
    cout << "runtime = " << clock() / 1000.0 << endl; //время работы программы 
    return 0;
}