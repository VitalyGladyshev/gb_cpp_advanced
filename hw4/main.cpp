//
// Created by Гладышев ВВ on 13.05.2022.
// C++: сложные моменты
// ДЗ к уроку 4 Алгоритмы STL
//

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <random>
#include <algorithm>
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
    cout << "\t\t";
    for(const auto el : cont)
        cout << el << " ";
    cout << endl;
}

double randDouble(const uint32_t& lower_bound, const uint32_t& upper_bound)
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

    uniform_real_distribution<double> uniform(lower_bound,upper_bound);
    default_random_engine re(seed);

    return uniform(re);
}

int main() {
    setlocale(LC_ALL, "Russian");
// Задание 1
    cout << "Задание 1" << endl;

//    Timer timer_t1("\tЗадание 1");
    cout << "\tvector<int>" << endl;
    vector<int> v1 = {1, 2, 3, 4, 5};
    print_container(v1);
    insert_sorted(v1, 3);
    print_container(v1);
    cout << endl;

    cout << "\tdeque<float>" << endl;
    deque<float> d1 = {4, 5, 6, 7, 8};
    print_container(d1);
    insert_sorted(d1, 6.7);
    print_container(d1);
    cout << endl;

    cout << "\tlist<string>" << endl;
    list<string> l1 = {"abc"s, "bcd"s, "cde"s, "fgh"s};
    print_container(l1);
    insert_sorted(l1, "def");
    print_container(l1);
    cout << endl;

// Задание 2
    cout << "Задание 2" << endl;
    vector<double> parameter(100);
    vector<double> parameter_discretized;
    generate(parameter.begin(), parameter.end(),
             [](){return (randDouble(0, 100));});
    for_each(parameter.begin(), parameter.end(),
             [&parameter_discretized](double d){ parameter_discretized.push_back(trunc(d)); });

    print_container(parameter);
    print_container(parameter_discretized);

    transform(parameter.begin(), parameter.end(), parameter_discretized.begin(),
              parameter_discretized.begin(), //back_inserter(temp),
              minus<double>());
    transform(parameter_discretized.begin(), parameter_discretized.end(), parameter_discretized.begin(),
              [](double x) {return x * x; });
//    print_container(parameter_discretized);

    cout << "\tОшибка: " << accumulate(parameter_discretized.begin(), parameter_discretized.end(),
                                       static_cast<double>(0)) << endl;
}
