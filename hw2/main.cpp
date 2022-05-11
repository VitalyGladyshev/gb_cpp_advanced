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

const vector<uint8_t> vowels {192, 224, 197, 229, 200, 201, 232, 233, 168, 184, 206, 238, 211, 243, 221, 253, 222,
                              254, 223, 255};

bool find_vowels(const char& ch)
{
    auto res = find(vowels.begin(), vowels.end(), static_cast<uint8_t>(ch));
    if (res != vowels.end())
        return true;
    else
        return false;
}

bool for_vowels(const char& ch)
{
    for (const auto& test_ch : vowels)
        if (test_ch == static_cast<uint8_t>(ch))
            return true;
    return false;
}

//count_if и find
void CntFind(const string& s)
{
    Timer timer("\tПодсчёт гласных count_if и find");
    auto counter = count_if(s.begin(), s.end(), find_vowels);
    timer.print();
    cout << "\t\tГласных: " << counter << endl << endl;
}

//count_if и цикл for
void CntFor(const string& s)
{
    Timer timer("\tПодсчёт гласных count_if и цикл for");
    auto counter = count_if(s.begin(), s.end(), for_vowels);
    timer.print();
    cout << "\t\tГласных: " << counter << endl << endl;
}

//цикл for и find
void ForFind(const string& s)
{
    int counter = 0;
    Timer timer("\tПодсчёт гласных цикл for и find");
    for (const auto& letter: s)
        if (find_vowels(letter))
            counter++;
    timer.print();
    cout << "\t\tГласных: " << counter << endl << endl;
}

//2 цикла for
void ForFor(const string& s)
{
    int counter = 0;
    Timer timer("\tПодсчёт гласных 2 цикла for");
    for (const auto& letter: s)
        for (const auto& test_ch : vowels)
            if (test_ch == static_cast<uint8_t>(letter))
                counter++;
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
    ifstream file_load("C:\\Users\\glvv2\\CLionProjects\\gb_cpp_advanced\\hw2\\voyna-i-mir-tom-1.txt");
    file_load.seekg(0, std::ios::end);
    size_t file_size = file_load.tellg();
    file_load.seekg(0);
    string s(file_size, ' ');
    file_load.read(&s[0], file_size);
    file_load.close();

    cout << "\tФайл voyna-i-mir-tom-1.txt размер: " << file_size << " байт" << endl;
//    cout << "\t\t" << s.substr(0, 42) << "..." << endl;
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
