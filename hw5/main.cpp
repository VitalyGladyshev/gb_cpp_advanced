//
// Created by Гладышев ВВ on 22.05.2022.
// C++: сложные моменты
// ДЗ к уроку 5 Алгоритмы STL
//

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>

using namespace std;

template<typename T>
void printWordsCount(T iterBegin, T iterEnd)
{
    set<string> setWords;
    while(iterBegin != iterEnd)
    {
        setWords.insert(*iterBegin);
        ++iterBegin;
    }

    auto it = setWords.begin();
    cout << "\t\t";
    while(it != setWords.end())
    {
        cout << *it << " ";
        ++it;
    }
}

template<typename I>
void print_container(const I& cont)
{
    for(const auto el : cont)
        cout << el << " ";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
// Задание 1
    cout << "Задание 1" << endl;

    vector<string> v1 = {"один", "два", "три", "один", "четыре", "два", "пять"};
    cout << "\tvector: ";
    print_container(v1);
    printWordsCount(v1.begin(), v1.end());
    cout << endl << endl;

    list<string> l1 = {"один", "два", "три", "один", "четыре", "два", "пять"};
    cout << "\tlist: ";
    print_container(l1);
    printWordsCount(l1.begin(), l1.end());
    cout << endl << endl;

    deque<string> d1 = {"один", "два", "три", "один", "четыре", "два", "пять"};
    cout << "\tdeque: ";
    print_container(d1);
    printWordsCount(d1.begin(), d1.end());
    cout << endl << endl;

// Задание 2
    cout << "Задание 2" << endl;

//    ifstream file_load("C:\\Users\\glvv2\\CLionProjects\\gb_cpp_advanced\\hw2\\voyna-i-mir-tom-1.txt");
//    string text;
//    map<string, int> mapCount;
//    while(file_load >> text)
//        ++mapCount[text];
//
//    auto it = mapCount.begin();
//    for (int i=0; i < 600; i++)
//        it++;
//    for(int i=0; i < 20; i++)
//    {
//        cout << it->first << " " << it->second << endl;
//        it++;
//    }

    cout << endl;
}