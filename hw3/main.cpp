//
// Created by Гладышев ВВ on 11.05.2022.
// C++: сложные моменты
// ДЗ к уроку 3 Последовательные контейнеры STL
//

#include <iostream>
#include <random>
#include <list>
#include <array>
#include <ostream>
#include <iomanip>
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

template<typename T>
class MyIter
{
public:
    MyIter() {};
    MyIter(T& val) { Ptr = &val; };

    void operator=(T val) { *Ptr = val; }
    T operator*() { return *Ptr; }
    void operator++() { Ptr++; }
    void operator++(int val) { Ptr++; }

private:
    T* Ptr;
};

//Класс Квадратная матрица SqureMatrix
template<typename T>
class SquareMatrix
{
public:
    //Конструктор
    SquareMatrix(/*uint32_t matrixSize*/) : _matrixSize(3)
    {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();

        uniform_real_distribution<double> uniform(0, 10);
        default_random_engine re(seed);

        for (int i = 0; i < _matrixSize; i++)
        {
            vector<T> line;
            for (int j = 0; j < _matrixSize; j++)
                line.push_back(static_cast<T>(uniform(re)));
            _matrix.push_back(line);
        }
    };

    //Вычисляем определитель
    double GetDeterminant()
    {

        return 0;
    }

    //Перегрузка оператора вывода
    friend ostream& operator<< (ostream& os, const SquareMatrix& myMatrix)
    {
        for (int i = 0; i < myMatrix._matrix.size(); i++)
        {
            os << "\t";
            for (int j = 0; j < myMatrix._matrix[i].size(); j++)
                os << setprecision(3) << myMatrix._matrix[i][j] << "\t";
            os << endl;
        }
        return os;
    }

private:
    uint32_t _matrixSize;
    vector<vector<T>> _matrix;
};

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

    SquareMatrix<double> myMatrix;
    cout << myMatrix;

    cout << endl;

// Задание 3
    cout << "Задание 3" << endl;

    double arrayDouble[] = {23.45, 45.67, 45.67, 78.56, 34.56};

    cout << "\t";
    for (MyIter it: arrayDouble)
        cout << *it << " ";
    cout << endl;

    MyIter it1(*arrayDouble);
    it1++;
    it1 = 10;

    cout << "\t";
    for (MyIter it: arrayDouble)
        cout << *it << " ";
    cout << endl;
}