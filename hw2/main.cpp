//
// Created by Гладышев ВВ on 02.05.2022.
// C++: сложные моменты
// ДЗ к уроку 2 Модель памяти и время выполнения
//

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Timer.h"

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

//count_if и find
void CntFind(string& s)
{
    int counter = 0;
    Timer timer("\tПодсчёт гласных count_if и find");

    timer.print();
    cout << "\t\tГласных: " << counter << endl << endl;
}

//count_if и цикл for
void CntFor(string& s)
{
    int counter = 0;
    Timer timer("\tПодсчёт гласных count_if и цикл for");

    timer.print();
    cout << "\t\tГласных: " << counter << endl << endl;
}

//цикл for и find
void ForFind(string& s)
{
    int counter = 0;
    Timer timer("\tПодсчёт гласных цикл for и find");

    timer.print();
    cout << "\t\tГласных: " << counter << endl << endl;
}

//2 цикла for
void ForFor(string& s)
{
    int counter = 0;
    Timer timer("\tПодсчёт гласных 2 цикла for");

    timer.print();
    cout << "\t\tГласных: " << counter << endl << endl;
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

    Timer timer_fl("\t\tЗагрузка файла");
    ifstream file_load("C:\\Users\\glvv2\\CLionProjects\\gb_cpp_advanced\\hw2\\voyna-i-mir-tom-1_.txt");
    file_load.seekg(0, std::ios::end);
    size_t file_size = file_load.tellg();
    file_load.seekg(0);
    string s(file_size, ' ');
    file_load.read(&s[0], file_size);
    file_load.close();

    cout << "\tФайл voyna-i-mir-tom-1_.txt размер: " << file_size << " байт" << endl;
    cout << "\t\t" << s.substr(0, 42) << "..." << endl;
    timer_fl.print();
    cout << endl;

    //count_if и find
    CntFind(s);
    //count_if и цикл for
    CntFor(s);
    //цикл for и find
    ForFind(s);
    //2 цикла for
    ForFor(s);
}
