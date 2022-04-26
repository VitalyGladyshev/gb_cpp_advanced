//
// Created by Гладышев ВВ on 26.04.2022.
// C++: сложные моменты
// ДЗ к уроку 1 Вспомогательные классы для удобной работы
//

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

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
    //Прегружаем оператор <<
    friend ostream& operator<< (ostream &out, const Person& person)
    {
        out << "\tСотрудник: " << person._lastName << " " << person._firstName << " " <<
            person._patronymic << endl;
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
    int16_t _extensionNumber;   //добавочный номер

public:
    //Конструкторы
    PhoneNumber() : _countryCode(0), _cityCode(0), _phoneNumber(""), _extensionNumber(0) {}
    PhoneNumber(int16_t countryCode, int16_t cityCode, string phNumber,
                int16_t extensionNumber) : _countryCode(countryCode), _cityCode(cityCode),
                _phoneNumber(std::move(phNumber)), _extensionNumber(extensionNumber) {}

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
        out << "\tНомер телефона: " << phoneNumber._countryCode << " " << phoneNumber._cityCode
            << " " << phoneNumber._phoneNumber << " " << phoneNumber._extensionNumber << endl;
        return out;
    }
};

//Класс Телефонная книга
class PhoneBook
{
private:
    vector<pair<Person, PhoneNumber>> _personPhone;     //

public:
    PhoneBook(Person person, PhoneNumber phoneNumber)
    {
        //_personPhone.push_back();
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
// Задание 1
    cout << "Задание 1" << endl;

// Задание 2
    cout << "\nЗадание 2" << endl;

// Задание 3
    cout << "\nЗадание 3" << endl;

//    ifstream file("ХХХ"); // путь к файлу PhoneBook.txt PhoneBook book(file);
//    cout << book;
//    cout << "------SortByPhone-------" << endl;
//    book.SortByPhone();
//    cout << book;
//    cout << "------SortByName--------" << endl;
//    book.SortByName();
//    cout << book;
//    cout << "-----GetPhoneNumber-----" << endl;
// лямбда функция, которая принимает фамилию и выводит номер телефона человека, либо строку с ошибкой
//    auto print_phone_number = [&book](const string& surname)
//    {
//        cout << surname << "\t";
//        auto answer = book.GetPhoneNumber(surname);
//        if (get<0>(answer).empty())
//            cout << get<1>(answer);
//        else
//            cout << get<0>(answer);
//        cout << endl;
//    };
// вызовы лямбды
//    print_phone_number("Ivanov");
//    print_phone_number("Petrov");
//    cout << "----ChangePhoneNumber----" << endl;
//    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
//                           PhoneNumber{7, 123, "15344458", nullopt});
//    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
//                           PhoneNumber{ 16, 465, "9155448", 13 });
//    cout << book;
}
