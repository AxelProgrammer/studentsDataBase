#include "student_lib.h"

#ifdef _WIN32
#include <windows.h>
#endif

// g++ -std=c++17 student_lib.cpp main.cpp -o main.exe
// .\main.exe

int main() {
    #ifdef _WIN32
        SetConsoleCP(65001);
        SetConsoleOutputCP(65001);
    #endif

    std::vector<Student> database;

    int choice;
    do {
        choice = safeInput<int>(
            "\nМеню:\n"
            "1. Добавить студента\n"
            "2. Вывести список студентов\n"
            "3. Поиск по имени\n"
            "4. Поиск по специальности\n"
            "0. Выход\n"
            "Выберите действие: ", 0, 4
        );

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3: {
                std::string name = safeStringInput("Введите имя (или часть имени): ");
                searchByName(database, name);
                break;
            }
            case 4: {
                std::string major = safeStringInput("Введите специальность (или часть названия): ");
                searchByMajor(database, major);
                break;
            }
            case 0:
                std::cout << "Выход из программы.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
