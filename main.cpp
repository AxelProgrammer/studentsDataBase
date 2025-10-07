#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

// g++ -o main.exe main.cpp
// .\main.exe

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

// Преобразование строки в нижний регистр
std::string toLower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lower;
}

// Проверка, содержится ли подстрока (без учёта регистра)
bool containsIgnoreCase(const std::string& text, const std::string& pattern) {
    return toLower(text).find(toLower(pattern)) != std::string::npos;
}

// Функция для добавления студента в базу данных
void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin >> student.name;
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin >> student.major;
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

// Функция для вывода всех студентов из базы данных
void displayStudents(const std::vector<Student>& database) {
    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

// Поиск по имени
void searchByName(const std::vector<Student>& database, const std::string& name) {
    bool found = false;
    for (const auto& s : database) {
        if (containsIgnoreCase(s.name, name)) {
            if (!found) std::cout << "🔍 Найденные студенты по имени '" << name << "':\n";
            std::cout << "Имя: " << s.name << ", Возраст: " << s.age
                      << ", Специальность: " << s.major << ", Средний балл: " << s.gpa << "\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "Студенты с именем, содержащим '" << name << "', не найдены.\n";
}

// Поиск по специальности
void searchByMajor(const std::vector<Student>& database, const std::string& major) {
    bool found = false;
    for (const auto& s : database) {
        if (containsIgnoreCase(s.major, major)) {
            if (!found) std::cout << "Найденные студенты по специальности '" << major << "':\n";
            std::cout << "Имя: " << s.name << ", Возраст: " << s.age
                      << ", Специальность: " << s.major << ", Средний балл: " << s.gpa << "\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "Студенты со специальностью, содержащей '" << major << "', не найдены.\n";
}

int main() {

    #ifdef _WIN32
        SetConsoleCP(65001);       
        SetConsoleOutputCP(65001);
    #endif

    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Поиск по имени\n";
        std::cout << "4. Поиск по специальности\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3: {
                std::string name;
                std::cout << "Введите имя (или часть имени): ";
                std::cin >> name;
                searchByName(database, name);
                break;
            }
            case 4: {
                std::string major;
                std::cout << "Введите специальность (или часть названия): ";
                std::cin >> major;
                searchByMajor(database, major);
                break;
            }
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
