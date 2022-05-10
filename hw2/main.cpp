//
// Created by Гладышев ВВ on 02.05.2022.
// C++: сложные моменты
// ДЗ к уроку 2 Модель памяти и время выполнения
//

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void Swap(T* ptr1, T* ptr2)
{
    T tempPtr = move(*ptr1);
    *ptr1 = move(*ptr2);
    *ptr2 = move(tempPtr);
}

void PrintVecBegin(const vector<int> &vec)
{
    auto prnSize = vec.size() > 10 ? 10 : vec.size();
    cout << " длина " << vec.size() << ": ";
    for (int i = 0; i < prnSize; i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

template <typename T1>
void SortPointers(vector<T1*> &vecPtrs)
{
    sort(vecPtrs.begin(), vecPtrs.end(),
         [](T1* val_1, T1* val_2){ return *val_1 < *val_2; });
}

void PrintVecPtrs(const vector<int *> &vecPtrs)
{
    for(const auto& ptr : vecPtrs)
        cout << *ptr << " ";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
// Задание 1
    cout << "Задание 1" << endl;

    int size = 100'000;
    vector<int> numbers_1, numbers_2;
    for (size_t i = 0; i < size; i++)
    {
        numbers_1.push_back(rand());
        numbers_2.push_back(rand());
    }

    cout << "\tnumbers_1";
    PrintVecBegin(numbers_1);
    cout << "\tnumbers_2";
    PrintVecBegin(numbers_2);

    auto start = chrono::steady_clock::now();
    Swap(&numbers_1, &numbers_2);
    auto end = chrono::steady_clock::now();
    chrono::duration<double> Time = end - start;
    cout << "\tSwap: " << Time.count() * 1000 << " мсек."<< endl;

    cout << "\tnumbers_1";
    PrintVecBegin(numbers_1);
    cout << "\tnumbers_2";
    PrintVecBegin(numbers_2);
    cout << endl;

// Задание 2
    cout << "Задание 2" << endl;
    int v1 = 150, v2 = 100, v3 = 300, v4 = 50, v5 = 200;
    vector<int *> vectorPtrs { &v1, &v2, &v3, &v4, &v5 };

    cout << "\tvectorPtrs: ";
    PrintVecPtrs(vectorPtrs);

    start = chrono::steady_clock::now();
    SortPointers(vectorPtrs);
    end = chrono::steady_clock::now();
    Time = end - start;
    cout << "\tSortPointers: " << Time.count() * 1000 << " мсек."<< endl;

    cout << "\tvectorPtrs: ";
    PrintVecPtrs(vectorPtrs);
    cout << endl;

// Задание 3
    cout << "Задание 3" << endl;


}
