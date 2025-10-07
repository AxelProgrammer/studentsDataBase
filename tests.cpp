#include <gtest/gtest.h>
#include <sstream>
#include "student_lib.h"

// --- Проверка toLower ---
TEST(FunctionTesting, toLower_basic) {
    EXPECT_EQ(toLower("HELLO"), "hello");
    EXPECT_EQ(toLower("HeLLo"), "hello");
    EXPECT_EQ(toLower("WORLD"), "world");
}

// --- Проверка containsIgnoreCase ---
TEST(FunctionTesting, containsIgnoreCase_basic) {
    EXPECT_TRUE(containsIgnoreCase("PROGRAMMING", "GRAMM"));
    EXPECT_TRUE(containsIgnoreCase("DataScience", "data"));
    EXPECT_FALSE(containsIgnoreCase("Math", "SCIENCE"));
}

// --- Добавление студента ---
TEST(StudentTesting, addStudent) {
    std::vector<Student> db;
    Student s1{"John", 20, "ComputerScience", 4.5};
    db.push_back(s1);
    ASSERT_EQ(db.size(), 1);
    EXPECT_EQ(db[0].name, "John");
    EXPECT_DOUBLE_EQ(db[0].gpa, 4.5);
}

// --- Поиск по имени ---
TEST(SearchTesting, searchByName_finds_student) {
    std::vector<Student> db = {{"John", 20, "ComputerScience", 4.5}};
    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    searchByName(db, "john");
    std::cout.rdbuf(oldCout);

    EXPECT_NE(buffer.str().find("John"), std::string::npos);
}

// --- Поиск по специальности ---
TEST(SearchTesting, searchByMajor_finds_student) {
    std::vector<Student> db = {{"John", 20, "ComputerScience", 4.5}};
    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    searchByMajor(db, "COMPUTER");
    std::cout.rdbuf(oldCout);

    EXPECT_NE(buffer.str().find("ComputerScience"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
