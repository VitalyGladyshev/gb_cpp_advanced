//
// Created by Гладышев ВВ on 06.06.2022.
// C++: сложные моменты
// ДЗ к уроку 8. Тестирование
//

#include <algorithm>
#include <string>
#include <numeric>
#include <iostream>
#include <fstream>
#include <vector>
#include <gtest/gtest.h>

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

    string printFullName() const
    {
        ostringstream os;
        os << "\tФИО: " << _firstName << " " << _lastName << " " << _patronymic << endl;
        return os.str();
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
        if(_marks.size())
            _marksAverage = accumulate(_marks.begin(), _marks.end(), static_cast<double>(0)) / _marks.size();
        else
            _marksAverage = 0;
    }

    double GetAverage() const
    {
        return _marksAverage;
    }

    string printStudent() const
    {
        ostringstream os;
        os << _fullName.printFullName();
        os << "\t\tСредний балл: " << _marksAverage << endl;
        return os.str();
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
    virtual void Open(string fileName) = 0; // бинарная десериализация в файл
    virtual void Save(string fileName) = 0; // бинарная сериализация в файл
};

class IMethods {
    virtual double GetAverageScore() const = 0;
    virtual string GetAllInfo() const = 0;
};

class StudentsGroup : public IRepository, IMethods
{
    vector<Student> _students;

public:
    StudentsGroup() {}
    StudentsGroup(initializer_list<Student> students) : _students(students) {}

    virtual double GetAverageScore() const
    {
        double average = 0;
        for(const auto& student : _students)
            average += student.GetAverage();
        if (_students.size())
            return average / _students.size();
        else
            return 0;
    }

    virtual string GetAllInfo() const
    {
        ostringstream os;
        os << "\tСтуденты группы: " << endl;
        for(const auto& student : _students)
            os << student.printStudent();
        os << "\tСредний балл группы: " << GetAverageScore() << endl;
        os << endl;
        return os.str();
    }

    virtual void Save(string fileName)
    {
        ofstream WF(fileName, ios::binary);
        char* D = reinterpret_cast<char*>(this);
        WF.write(D, sizeof(*this));
        WF.close();
    }

    virtual void Open(string fileName)
    {
        ifstream RF(fileName, ios::binary);
        RF.read(reinterpret_cast<char*>(this), sizeof(*this));
        RF.close();
    }
};

class TestDate : public testing::Test{
protected:
    void SetUp() override
    {
        pIvan = new FullName("Иванов"s, "Иван"s, "Иванович"s);
        pPetr = new FullName("Петров"s, "Пётр"s, "Петрович"s);
        pStudentIvan = new Student(*pIvan, {4, 5, 3, 4, 5, 3, 4, 5});
        pStudentPetr = new Student(*pPetr, {5, 4, 5, 4, 5, 3, 5, 5});
        pGroup = new StudentsGroup({*pStudentIvan, *pStudentPetr});
    }

    void TearDown() override
    {
        delete pIvan;
        delete pPetr;
        delete pStudentIvan;
        delete pStudentPetr;
        delete pGroup;
    }

    FullName *pIvan;
    FullName *pPetr;
    Student *pStudentIvan;
    Student *pStudentPetr;
    StudentsGroup *pGroup;
};

TEST_F(TestDate, average)
{
    ASSERT_DOUBLE_EQ(pGroup->GetAverageScore(), 4.3125);
}

TEST_F(TestDate, names)
{
    ostringstream os;
    os << "\tФИО: Иванов Иван Иванович" << endl;

    ASSERT_STREQ(os.str().c_str(),
                 pIvan->printFullName().c_str()) << "you'll see this in case of an error";
}

int main()
{
    setlocale(LC_ALL, "Russian");

    FullName ivan("Иванов"s, "Иван"s, "Иванович"s);
    FullName petr("Петров"s, "Пётр"s, "Петрович"s);

    Student studentIvan(ivan, {4, 5, 3, 4, 5, 3, 4, 5});
    Student studentPetr(petr, {5, 4, 5, 4, 5, 3, 5, 5});

    studentIvan.ser("Ivan.dat");
    cout << studentIvan.printStudent();
    cout << endl;
    cout << studentPetr.printStudent();
    cout << endl;

    StudentsGroup group({studentIvan, studentPetr});
    group.Save("Group.dat");
    cout << group.GetAllInfo();

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
