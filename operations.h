#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct FullStudent {
    int32_t group{};
    int32_t recordBook{};
    std::string surname;
    std::string name;
    std::string patronymic;
    int32_t gradeMA{};
    int32_t gradeGEO{};
    int32_t gradePROG{};
};

struct GradeRecord {
    int32_t group{};
    int32_t recordBook{};
    int32_t gradeMA{};
    int32_t gradeGEO{};
    int32_t gradePROG{};
};

struct StudentWithAverage {
    int32_t group{};
    int32_t recordBook{};
    std::string surname;
    std::string name;
    std::string patronymic;
    float averageGrade = 0.0f;
};

void isValidGroup(const std::string&);
void isValidRecordBook(const std::string&);
void isValidSubject(const std::string&);
void isValidGrade(const std::string&);
void validateGradeLine(const std::string&);
void checkOutputFile(std::fstream&);
void checkFile(std::ifstream&);
int32_t countPeople(std::ifstream&);
void inputPeople(std::ifstream&, std::string*, int32_t);
void fillBinary(std::fstream&, std::string*, int32_t);
void fillStructuresFromStudents(std::ifstream&, FullStudent*, int32_t);
void fillStructuresFromMarks(std::ifstream&, GradeRecord*, int32_t);
void fillStructuresFromAverageMarks(std::fstream& fin, StudentWithAverage*, int32_t);
void mergeSurnamesMarks(FullStudent*, GradeRecord*, int32_t, int32_t);
void makeMainBin(std::fstream&, FullStudent*, int32_t);
void calculateAverageAndWrite(std::fstream&, FullStudent*, StudentWithAverage*, int32_t);
void makeAverageBin(std::fstream&, StudentWithAverage*, int32_t);

#endif
