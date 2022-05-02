//
// Created by Гладышев ВВ on 26.04.2022.
// C++: сложные моменты
// ДЗ к уроку 1 Вспомогательные классы для удобной работы
//

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <fstream>
#include <optional>
#include <iomanip>
#include <algorithm>

using namespace std;

//Структура Сотрудник
struct Person
{
private:
    string _lastName;       //фамилия
    string _firstName;      //имя
    string _patronymic;     //отчество

public:
    //Конструкторы
    Person() : _lastName(""), _firstName(""), _patronymic("") {}
    Person(string lastName, string firstName, string patronymic = "") :
        _lastName(std::move(lastName)), _firstName(std::move(firstName)),
        _patronymic(std::move(patronymic)) {}

    //Прегружаем оператор <
    friend bool operator< (const Person& person_1, const Person& person_2)
    {
        return tie(person_1._lastName, person_1._firstName, person_1._patronymic) <
               tie(person_2._lastName, person_2._firstName, person_2._patronymic);
    }
    //Прегружаем оператор ==
    friend bool operator== (const Person& person_1, const Person& person_2)
    {
        return tie(person_1._lastName, person_1._firstName, person_1._patronymic) ==
                tie(person_2._lastName, person_2._firstName, person_2._patronymic);
    }
    //Прегружаем оператор ==
    friend bool operator== (const Person& person, const string& lastName)
    {
        return person._lastName == lastName;
    }
    //Прегружаем оператор <<
    friend ostream& operator<< (ostream &out, const Person& person)
    {
        out << setw(15) << right << person._lastName
            << setw(15) << right << person._firstName
            << setw(15) << right << person._patronymic;
        return out;
    }
};

//Структура Номер телефона
struct PhoneNumber
{
private:
    int16_t _countryCode;       //код страны
    int16_t _cityCode;          //код города
    string _phoneNumber;        //номер телефона
    optional<int16_t> _extensionNumber;   //добавочный номер

public:
    //Конструкторы
    PhoneNumber() : _countryCode(0), _cityCode(0), _phoneNumber(""), _extensionNumber(0) {}
    PhoneNumber(int16_t countryCode, int16_t cityCode, string phNumber,
                optional<int16_t> extensionNumber = nullopt) : _countryCode(countryCode),
                _cityCode(cityCode), _phoneNumber(std::move(phNumber)),
                _extensionNumber(extensionNumber) {}

    //Прегружаем оператор <
    friend bool operator< (const PhoneNumber& phoneNumber_1, const PhoneNumber& phoneNumber_2)
    {
        return tie(phoneNumber_1._countryCode, phoneNumber_1._cityCode,
                   phoneNumber_1._phoneNumber, phoneNumber_1._extensionNumber) <
                tie(phoneNumber_2._countryCode, phoneNumber_2._cityCode,
                    phoneNumber_2._phoneNumber, phoneNumber_2._extensionNumber);
    }
    //Прегружаем оператор ==
    friend bool operator== (const PhoneNumber& phoneNumber_1, const PhoneNumber& phoneNumber_2)
    {
        return tie(phoneNumber_1._countryCode, phoneNumber_1._cityCode,
                   phoneNumber_1._phoneNumber, phoneNumber_1._extensionNumber) ==
               tie(phoneNumber_2._countryCode, phoneNumber_2._cityCode,
                   phoneNumber_2._phoneNumber, phoneNumber_2._extensionNumber);
    }
    //Прегружаем оператор <<
    friend ostream& operator<< (ostream &out, const PhoneNumber& phoneNumber)
    {
        out << "+" << phoneNumber._countryCode << "(" << phoneNumber._cityCode
            << ")" << phoneNumber._phoneNumber;
        if (phoneNumber._extensionNumber != nullopt)
            out << " " << phoneNumber._extensionNumber.value();
        return out;
    }
};

//Класс Телефонная книга
class PhoneBook
{
private:
    vector<pair<Person, PhoneNumber>> _personPhone;     //запись в телефонной книге

public:
    //Конструкторы
    PhoneBook(ifstream &fin)
    {
        string tempString;
        while(getline(fin, tempString))
        {
            string lName, fName, pat, fullNumber, number, codeNumber;
            int16_t cCode, sCode, ext_ = -1;

            istringstream iss(tempString);
            iss >> lName >> fName >> pat >> fullNumber >> ext_;
            number = fullNumber.substr(fullNumber.size()-7, 7);
            codeNumber = fullNumber.substr(1, fullNumber.size()-9);
            string delimiter = "(";
            cCode = stoi(codeNumber.substr(0, codeNumber.find(delimiter)));
            sCode = stoi(codeNumber.substr(codeNumber.find(delimiter) + 1,
                                      codeNumber.size() - (codeNumber.find(delimiter)+1)));

            Person person(lName, fName, pat);
            optional<int16_t> ext;
            if (ext_ != -1)
                ext = ext_;
            else
                ext = nullopt;
            PhoneNumber pNumber(cCode, sCode, number, ext);
            pair<Person, PhoneNumber> line(person, pNumber);
            _personPhone.push_back(line);
        }
    }

    //Сортировка по имени
    void SortByName()
    {
        sort(_personPhone.begin(), _personPhone.end(),
             [](pair<Person, PhoneNumber> line1, pair<Person, PhoneNumber> line2)
             {return line1.first < line2.first;});
    }
    //Сортировка по номеру телефона
    void SortByPhone()
    {
        sort(_personPhone.begin(), _personPhone.end(),
             [](pair<Person, PhoneNumber> line1, pair<Person, PhoneNumber> line2)
             {return line1.second < line2.second;});
    }
    //Получить номер (по фамилии)
    pair<string, string> GetPhoneNumber(const string& _lastName)
    {
        for(const auto& phoneBookLine: _personPhone)
        {
            if (phoneBookLine.first == _lastName)
            {
                stringstream ss;
                ss << phoneBookLine.second;
                return make_pair(ss.str(), _lastName);
            }
        }
        return make_pair("", "not found");
    }
    //Изменить номер
    void ChangePhoneNumber(const Person& person, const PhoneNumber& phoneNumber)
    {
        for (auto& phoneBookLine: _personPhone)
        {
            if (phoneBookLine.first == person)
                phoneBookLine.second = phoneNumber;
        }
    }
    //Прегружаем оператор <<
    friend ostream& operator<< (ostream &out, const PhoneBook& phoneBook)
    {
        for (auto line : phoneBook._personPhone)
            out << "\t" << line.first << "\t" << line.second << endl;
        return out;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
// Задание 1
    cout << "Задания 1, 2" << endl;

    vector<Person> persons
    {
        {"Ivanov", "Ivan", "Ivanovich"},
        {"Sidorov", "Petr", "Petrovich"},
        {"Kotov", "Vasilii", "Eliseevich"},
        {"Mironova", "Margarita", "Vladimirovna"}
    };

    vector<PhoneNumber> phoneNumbers
    {
        {19, 87, "4827563", 16},
        {6, 145, "1534445", 23},
        {18, 164, "3948575", nullopt},
        {7, 14, "5648365", 45}
    };

    ofstream out("phonebook.txt");

    for (int i = 0; i < persons.size(); i++)
    {
        cout << persons[i] << "\t" << phoneNumbers[i] << endl;
        out << persons[i] << "\t" << phoneNumbers[i] << endl;
    }

// Задание 3
    cout << "\nЗадание 3" << endl;

    ifstream file("phonebook.txt");     // путь к файлу PhoneBook.txt
    PhoneBook book(file);
    file.close();
    cout << book;

    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;

    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;

    cout << "-----GetPhoneNumber-----" << endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона человека,
    // либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname)
    {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            cout << get<1>(answer);
        else
            cout << get<0>(answer);
        cout << endl;
    };
    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
                           PhoneNumber{7, 123, "15344458", nullopt});
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
                           PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;
}
