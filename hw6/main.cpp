//
// Created by Гладышев ВВ on 24.05.2022.
// C++: сложные моменты
// ДЗ к уроку 6 Параллельное программирование. Многопоточность
//
#define _USE_MATH_DEFINES

#include <iostream>
#include <sstream>
#include<thread>
#include<mutex>
#include "Timer.h"

using namespace std;

//Класс pcout


class pcout: public ostringstream
{
public:
    pcout() = default;

    ~pcout()
    {
        std::lock_guard<std::mutex> guard(_mutexPrint);
        std::cout << this->str();
    }

private:
    std::mutex _mutexPrint;
};

void func1()
{
    for (int i = 0; i < 10; i++)
    {
        this_thread::sleep_for(100ms);
        cout << i << " ";
    }
    cout << endl;
}

void func2()
{
    for (int i = 10; i < 100; i+=10)
    {
        this_thread::sleep_for(100ms);
        cout << i << " ";
    }
    cout << endl;
    consol_color::SetColor(15, 0);
}

ostream pout(std::cout.rdbuf());

void func3()
{
    for (int i = 0; i < 10; i++)
    {
        this_thread::sleep_for(100ms);
        pcout{} << i << " ";
    }
    cout << endl;
}

void func4()
{
    for (int i = 10; i <= 100; i+=10)
    {
        this_thread::sleep_for(100ms);
        pcout{} << i << " ";
    }
    cout << endl;
    consol_color::SetColor(15, 0);
}

int main() {
    setlocale(LC_ALL, "Russian");
// Задание 1
    cout << "Задание " << endl;
    thread thr_1(func1);
    thread thr_2(func2);
    thr_1.join();
    thr_2.join();

    thread thr_3(func3);
    thread thr_4(func4);
    thr_3.join();
    thr_4.join();
    cout << endl;

// Задание 2
    cout << "Задание 2" << endl;

    cout << endl;

// Задание 3
    cout << "Задание 3" << endl;


}
