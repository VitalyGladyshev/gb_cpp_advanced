//
// Created by Гладышев ВВ on 11.05.2022.
// C++: сложные моменты
// ДЗ к уроку 3 Последовательные контейнеры STL
//

#include <iostream>
#include <random>
#include <list>
#include "..\\Timer.h"

using namespace std;


double randDouble(const uint32_t& lower_bound, const uint32_t& upper_bound)
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

    uniform_real_distribution<double> uniform(lower_bound,upper_bound);
    default_random_engine re(seed);

    return uniform(re);
}

template <typename T>
void printIterable(const T& iterable)
{
    cout << "\t";
    for (auto i = iterable.begin(); i != iterable.end(); i++)
        cout << *i << " ";
    cout << endl;
}

template <typename T>
void PushMean(list<T>& sourceList)
{
    T counter = 0;
    for (auto i = sourceList.begin(); i != sourceList.end(); i++)
        counter += *i;
    sourceList.push_back(counter/sourceList.size());
}

int main()
{

    setlocale(LC_ALL, "Russian");
// Задание 1
    cout << "Задание 1" << endl;

    Timer timer_t1("\tДобавляем среднее значение в список");
    list<double> listRandDouble;

    for (int i = 0; i < 10; i++)
        listRandDouble.push_back(randDouble(0, 100));

    printIterable(listRandDouble);
    PushMean(listRandDouble);
    printIterable(listRandDouble);

    timer_t1.print();
    cout << endl;

// Задание 2
    cout << "Задание 2" << endl;

    cout << endl;

// Задание 3
    cout << "Задание 3" << endl;

}