//
// Created by Гладышев ВВ on 26.04.2022.
// C++: сложные моменты
// ДЗ к уроку 1 Вспомогательные классы для удобной работы
//

#include <iostream>

using namespace std;

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
