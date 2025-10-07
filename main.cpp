#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

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

// Функция безопасного ввода числа
template <typename T>
T safeInput(const std::string& prompt, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear(); // Сброс флага ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            std::cout << "Неверный ввод. Попробуйте снова.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка остатка строки
            return value;
        }
    }
}

// Функция безопасного ввода строки
std::string safeStringInput(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input.empty()) {
            std::cout << "❌ Ввод не может быть пустым. Попробуйте снова.\n";
        } else {
            return input;
        }
    }
}

// Добавление студента
void addStudent(std::vector<Student>& database) {
    Student student;
    student.name = safeStringInput("Введите имя студента: ");
    student.age = safeInput<int>("Введите возраст студента: ", 0, 150);
    student.major = safeStringInput("Введите специальность студента: ");
    student.gpa = safeInput<double>("Введите средний балл студента (0.0 - 5.0): ", 0.0, 5.0);

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

// Вывод всех студентов
void displayStudents(const std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных пуста.\n";
        return;
    }
    std::cout << "Список студентов:\n";
    for (const Student& s : database) {
        std::cout << "Имя: " << s.name << "\n";
        std::cout << "Возраст: " << s.age << "\n";
        std::cout << "Специальность: " << s.major << "\n";
        std::cout << "Средний балл: " << s.gpa << "\n\n";
    }
}

// Поиск по имени
void searchByName(const std::vector<Student>& database, const std::string& name) {
    bool found = false;
    for (const auto& s : database) {
        if (containsIgnoreCase(s.name, name)) {
            if (!found) std::cout << "Найденные студенты по имени '" << name << "':\n";
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
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
