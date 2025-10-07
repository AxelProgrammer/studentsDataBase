#include "student_lib.h"

std::string toLower(const std::string& str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lower;
}

bool containsIgnoreCase(const std::string& text, const std::string& pattern) {
    return toLower(text).find(toLower(pattern)) != std::string::npos;
}

template <typename T>
T safeInput(const std::string& prompt, T min, T max) {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Попробуйте снова.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

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

void addStudent(std::vector<Student>& database) {
    Student student;
    student.name = safeStringInput("Введите имя студента: ");
    student.age = safeInput<int>("Введите возраст студента: ", 0, 150);
    student.major = safeStringInput("Введите специальность студента: ");
    student.gpa = safeInput<double>("Введите средний балл студента (0.0 - 5.0): ", 0.0, 5.0);

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

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

// Эксплицитная инстанциация шаблона (чтобы не было ошибок линковки)
template int safeInput<int>(const std::string&, int, int);
template double safeInput<double>(const std::string&, double, double);
