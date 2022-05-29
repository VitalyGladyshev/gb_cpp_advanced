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
#include <random>
#include <condition_variable>
#include <algorithm>
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

double randInt(const uint32_t& lower_bound, const uint32_t& upper_bound)
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

    uniform_real_distribution<double> uniform(lower_bound,upper_bound);
    default_random_engine re(seed);

    return static_cast<int>(uniform(re));
}

vector<int> things;
void owner()
{
    for(int i = 0; i < 60; i++)
    {
        this_thread::sleep_for(500ms);
        lock_guard<mutex> lk(mut);
        int thing = randInt(0, 1000);
//        cout << "\tПринёс: " << thing << endl;
        things.push_back(thing);
        sort(things.begin(), things.end());
        data_cond.notify_one();
    }
}

void thief()
{
    for(int i = 0; i < 30; i++)
    {
        this_thread::sleep_for(1000ms);
        lock_guard<mutex> lk(mut);

        if(things.size())
        {
//            cout << "\tУнёс: " << things.back() << endl;
            things.pop_back();
        }

        data_cond.notify_one();
    }
}

int main()
{
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

    Timer timerOT("timerOT");
    thread thO(owner);
    thread thT(thief);

    size_t thingsSize = 0;
    while (true)
    {
        unique_lock<mutex> lk(mut);
        data_cond.wait(lk, [&thingsSize] {return thingsSize != things.size(); });
        thingsSize = things.size();
        cout << "\tВещи: ";
        for(const auto th: things)
            cout << th << " ";
        cout << "\r";
//        cout << "\t timerOT.elaps(): " << timerOT.elaps() << endl;
        cout.flush();
        lk.unlock();
        if(timerOT.elaps() > 29500)
            break;
    }

    thO.join();
    thT.join();
}
