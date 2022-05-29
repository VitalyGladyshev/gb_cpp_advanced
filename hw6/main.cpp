//
// Created by Гладышев ВВ on 24.05.2022.
// C++: сложные моменты
// ДЗ к уроку 6 Параллельное программирование. Многопоточность
//
#define _USE_MATH_DEFINES

#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>
#include <condition_variable>
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

mutex mut;
size_t curN;
condition_variable data_cond;

int GetPrimeNumber(int count)
{
    if (count > 0)
    {
        if (count > 1)
        {
            vector<int> primeNumbers {2};
            for (int i = 3; primeNumbers.size() < count; i+=2)
            {
                bool prime = true;
                int limit = ceil(i/2);
                for (const auto pn : primeNumbers)
                {
                    if (!(i % pn))
                    {
                        prime = false;
                        break;
                    }
                    if (pn > limit)
                        break;
                }
                if (prime)
                {
                    primeNumbers.push_back(i);
                    curN = primeNumbers.size();
                    if(!(curN % 10))
                    {
                        lock_guard<mutex> lk(mut);
                        data_cond.notify_one();
                    }
                }
            }
            return primeNumbers.back();
        }
        else
            return 2;
    }
    else
        return -1;
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

    Timer primeNumberTimer("\tПростое число N=100'000");
    cout << "\tЧисло: " << GetPrimeNumber(100'000) << endl;
    primeNumberTimer.print();

    curN = 0;
    size_t curNL = curN;
    Timer primeNumberTimer2("\tПростое число N=100'000 в потоке");
    thread prThr(GetPrimeNumber, 100'000);

    while(true)
    {
        unique_lock<mutex> lk(mut);
        data_cond.wait(lk, [&curNL] {return curNL != curN; });
        curNL = curN;
//        pcout{} << "\tНомер: " << curNL << endl;
        cout << "\tНомер: " << curNL << "\r"; //endl;
        cout.flush();
        lk.unlock();
        if (curNL == 100'000)
            break;
    }
    cout << endl;
    prThr.join();
    primeNumberTimer2.print();
    cout << endl;

// Задание 3
    cout << "Задание 3" << endl;


}
