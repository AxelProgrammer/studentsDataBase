#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

// === Структура студента ===
struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

// === Объявления функций ===
std::string toLower(const std::string& str);
bool containsIgnoreCase(const std::string& text, const std::string& pattern);

template <typename T>
T safeInput(const std::string& prompt, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max());

std::string safeStringInput(const std::string& prompt);
void addStudent(std::vector<Student>& database);
void displayStudents(const std::vector<Student>& database);
void searchByName(const std::vector<Student>& database, const std::string& name);
void searchByMajor(const std::vector<Student>& database, const std::string& major);
