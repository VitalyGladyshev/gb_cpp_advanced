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

    string text, sentence;
    int wordCount = 0;
    cout << "\tВведите набор предложений. Для завершения введите: стоп" << endl;
    cout << "\t#:> ";
    map<int, list<string>> mapCount;

    while(cin >> text)
    {
        if (text == "стоп")
            break;
        sentence += " ";
        sentence += text;
        wordCount++;
        if (text.back() == '.' || text.back() == '!' || text.back() == '?')
        {
            cout << "\tСлов " << wordCount << ": " << sentence << endl;
            mapCount[wordCount].push_back(sentence);
            sentence.clear();
            wordCount = 0;
        }
    }

    for (const auto& [number, sentenceList]: mapCount)
    {
        cout << "\tСлов: " << number << " Предложений: " << sentenceList.size() << endl;
        for (const auto& sentence: sentenceList)
            cout << "\t\t" << sentence << endl;
        cout << endl;
    }
}