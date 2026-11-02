#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

enum { ROWS = 9, COLS = 6 };

// Рекурсивне формування матриці
void Create(int a[ROWS][COLS], int index, int Low, int High)
{
    if (index >= ROWS * COLS)
        return;

    int i = index / COLS;
    int j = index % COLS;

	a[i][j] = Low + rand() % (High - Low + 1); // Генерація випадкового числа в діапазоні [Low, High]

	Create(a, index + 1, Low, High); // Рекурсивний виклик для наступного елемента
}

// Рекурсивне виведення матриці
void Print(int a[ROWS][COLS], int index)
{
	if (index >= ROWS * COLS) // Базовий випадок: якщо індекс перевищує кількість елементів, завершити рекурсію
        return;

    int i = index / COLS;
    int j = index % COLS;

    cout << setw(4) << a[i][j];

	if (j == COLS - 1) // Якщо досягнуто останній стовпець, перейти на новий рядок
        cout << endl;

	Print(a, index + 1); // Рекурсивний виклик для наступного елемента
}

// Рекурсивний обмін двох стовпців
void Change(int a[ROWS][COLS], int col1, int col2, int row) // row - поточний рядок
{
    if (row >= ROWS)
        return;

    int temp = a[row][col1];
    a[row][col1] = a[row][col2];
    a[row][col2] = temp;

	Change(a, col1, col2, row + 1); // Рекурсивний виклик для наступного рядка
}

// Рекурсивний прохід сортування
void SortPass(int a[ROWS][COLS], int j, int limit)
{
    if (j >= limit)
        return;

    bool needSwap = false;

    if (a[0][j] > a[0][j + 1])
        needSwap = true;

    else if (a[0][j] == a[0][j + 1] &&
        a[1][j] < a[1][j + 1])
        needSwap = true;

    else if (a[0][j] == a[0][j + 1] &&
        a[1][j] == a[1][j + 1] &&
        a[2][j] < a[2][j + 1])
        needSwap = true;

    if (needSwap)
        Change(a, j, j + 1, 0);

    SortPass(a, j + 1, limit);
}

// Рекурсивне сортування стовпців
void Sort(int a[ROWS][COLS], int pass)
{
    if (pass >= COLS - 1)
        return;

    SortPass(a, 0, COLS - pass - 1);

    Sort(a, pass + 1);
}

// Рекурсивне обчислення суми та кількості
void Calc(int a[ROWS][COLS], int index, int& S, int& k)
{
    if (index >= ROWS * COLS)
        return;

    int i = index / COLS;
    int j = index % COLS;

    if (a[i][j] % 2 == 0 && a[i][j] % 7 != 0)
    {
        S += a[i][j];
        k++;
        a[i][j] = 0;
    }

    Calc(a, index + 1, S, k);
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    int Z[ROWS][COLS];

    Create(Z, 0, 18, 74);

    cout << "Initial matrix:" << endl;
    Print(Z, 0);

    Sort(Z, 0);

    cout << "Sorted matrix:" << endl;
    Print(Z, 0);

    int S = 0;
    int k = 0;

    Calc(Z, 0, S, k);

    cout << "Sum = " << S << endl;
    cout << "Count = " << k << endl;

    cout << "Modified matrix:" << endl;
    Print(Z, 0);

    return 0;
}