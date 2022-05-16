//
// Created by Гладышев ВВ on 13.05.2022.
// C++: сложные моменты
// ДЗ к уроку 4 Алгоритмы STL
//

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include "..\\Timer.h"

using namespace std;

template<typename I, typename T>
void insert_sorted(I& cont, T val)
{
    auto it = cont.begin();
    while(it != cont.end())
    {
        if(*it > val)
        {
            cont.insert(it, val);
            return;
        }
        it++;
    }
}

template<typename I>
void print_container(const I& cont)
{
    cout << "\t";
    for(const auto el : cont)
        cout << el << " ";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
// Задание 1
    cout << "Задание 1" << endl;

//    Timer timer_t1("\tЗадание 1");
    cout << "vector<int>" << endl;
    vector<int> v1 = {1, 2, 3, 4, 5};
    print_container(v1);
    insert_sorted(v1, 3);
    print_container(v1);
    cout << endl;

    cout << "deque<float>" << endl;
    deque<float> d1 = {4, 5, 6, 7, 8};
    print_container(d1);
    insert_sorted(d1, 6.7);
    print_container(d1);
    cout << endl;

    cout << "list<string>" << endl;
    list<string> l1 = {"abc"s, "bcd"s, "cde"s, "fgh"s};
    print_container(l1);
    insert_sorted(l1, "def");
    print_container(l1);
    cout << endl;

// Задание 2
    cout << "Задание 2" << endl;

}
