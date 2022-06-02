//
// Created by Гладышев ВВ on 01.06.2022.
// C++: сложные моменты
// ДЗ к уроку 7. Пространство имен и бинарная серилизация
//

#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <vector>
#include "zlib.h"
//#include "car.pb.h"

using namespace std;

//Классы с сериализацией/десериализацией
class FullName
{
private:
    string _lastName;       //фамилия
    string _firstName;      //имя
    string _patronymic;     //отчество

public:
    FullName() {}
    FullName(string firstName, string lastName, string patronymic) :
        _firstName(firstName), _lastName(lastName), _patronymic(patronymic) {}

    void printFullName()
    {
        cout << "\tФИО: " << _firstName << " " << _lastName << " " << _patronymic << endl;
    }

    void ser(string fileName)
    {
        ofstream WF(fileName, ios::binary);
        char* D = reinterpret_cast<char*>(this);
        WF.write(D, sizeof(*this));
        WF.close();
    }

    void deser(string fileName)
    {
        ifstream RF(fileName, ios::binary);
        RF.read(reinterpret_cast<char*>(this), sizeof(*this));
        RF.close();
    }
};

class Student
{
    FullName _fullName;     // полное имя
    vector<int> _marks;     // массив оценок
    double _marksAverage;   // средний балл

public:
    Student() {}
    Student(FullName& fullName, initializer_list<int> marks) : _fullName(fullName), _marks(marks)
    {
        _marksAverage = accumulate(_marks.begin(), _marks.end(), static_cast<double>(0)) / _marks.size();
    }

    void printStudent()
    {
        _fullName.printFullName();
        cout << "\t\tСредний балл: " << _marksAverage << endl;
    }

    void ser(string fileName)
    {
        ofstream WF(fileName, ios::binary);
        char* D = reinterpret_cast<char*>(this);
        WF.write(D, sizeof(*this));
        WF.close();
    }

    void deser(string fileName)
    {
        ifstream RF(fileName, ios::binary);
        RF.read(reinterpret_cast<char*>(this), sizeof(*this));
        RF.close();
    }
};

//Интерфейсы
class IRepository {
    virtual void Open() = 0; // бинарная десериализация в файл virtual void Save() = 0; // бинарная сериализация в файл
};

class IMethods {
    virtual double GetAverageScore(const FullName& name) = 0;
    virtual string GetAllInfo(const FullName& name) = 0;
    virtual string GetAllInfo() = 0;
};

class StudentsGroup
{
    vector<Student> _students;

public:
    StudentsGroup() {}
    StudentsGroup(initializer_list<Student> students) : _students(students) {}

    void printStudent()
    {
        cout << "\tСтуденты группы: " << endl;
        for(auto& student : _students)
            student.printStudent();
        cout << endl;
    }

    void ser(string fileName)
    {
        ofstream WF(fileName, ios::binary);
        char* D = reinterpret_cast<char*>(this);
        WF.write(D, sizeof(*this));
        WF.close();
    }

    void deser(string fileName)
    {
        ifstream RF(fileName, ios::binary);
        RF.read(reinterpret_cast<char*>(this), sizeof(*this));
        RF.close();
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
// Задание 1
    cout << "Ставим и проверяем работоспособность protobuf" << endl;
    cout << "\tCompiled with zlib " << ZLIB_VERSION << " using zlib " << zlib_version << endl;

//    Car car;
//    car.set_brand("Toyota");
//    car.set_model("Camry");
//    car.set_year(2011);
//    cout << car.brand() << " " << car.model() << " " << car.year() << endl;
//    ofstream out("/Users/semyon/Desktop/protobuf_lesson/car.bin", ios_base::binary);
//    car.SerializeToOstream(&out);

    cout << endl;

// Задание 2-3
    FullName ivan("Иванов"s, "Иван"s, "Иванович"s);
    FullName petr("Петров"s, "Пётр"s, "Петрович"s);

    Student studentIvan(ivan, {4, 5, 3, 4, 5, 3, 4, 5});
    Student studentPetr(petr, {5, 4, 5, 4, 5, 3, 5, 5});

    studentIvan.ser("Ivan.dat");
    Student studentX;
    studentX.deser("Ivan.dat");
    studentX.printStudent();
    cout << endl;

    StudentsGroup group({studentIvan, studentPetr});
    group.ser("Group.dat");

    StudentsGroup groupX;
    groupX.deser("Group.dat");
    groupX.printStudent();

    return 0;
}