#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

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
    double averageGrade = 0.0;
};

void CheckOutputFile(std::fstream&);
void CheckFile(std::ifstream&);
int32_t CountPeople(std::ifstream&);
void InputPeople(std::ifstream&, std::string*, int32_t);
void FillBinary(std::fstream&, std::string*, int32_t);
void FillStructuresFromStudents(std::ifstream&, FullStudent*, int32_t);
void FillStructuresFromMarks(std::ifstream&, GradeRecord*, int32_t);
void FillStructuresFromAverageMarks(std::fstream& fin, StudentWithAverage*, int32_t);
void MergeSurnamesMarks(FullStudent*, GradeRecord*, int32_t, int32_t);
void MakeBin(std::fstream&, FullStudent*, int32_t);
void CalculateAverageAndWrite(std::fstream&, FullStudent*, StudentWithAverage*, int32_t);
void MakeAverageBin(std::fstream&, StudentWithAverage*, int32_t);
void WriteString(std::fstream&, std::string&);
void MakeFailingBin(std::fstream&, FullStudent*, int32_t);
void PrintStudentToConsole(std::string&, int32_t, int32_t);
void PrintAverageGradeToCons(int32_t, std::string&, std::string&, std::string&, double);
void PrintStudentToConsole(int32_t, int32_t, std::string&, std::string&, std::string&, int32_t, int32_t, int32_t);
bool isFailing(FullStudent&);
bool CompareFailing(FullStudent&, FullStudent&);
bool CompareByAvg(FullStudent&, FullStudent&);
void Merge(FullStudent*, int32_t, int32_t, int32_t, FullStudent*, bool (*compareFunc)(FullStudent&, FullStudent&));
void MergeSort(FullStudent*, int32_t, int32_t, FullStudent*, bool (*compareFunc)(FullStudent&, FullStudent&));
int32_t countFailingStudents(FullStudent*, int32_t);
void WriteSortedFailing(std::fstream&, FullStudent*, int32_t);
int32_t ExtractFailingStudents(FullStudent*, int32_t, FullStudent*);
void PrintFailingStudentsToConsole(FullStudent*, int32_t);
void saveStudentsToTextFile(std::string&, FullStudent*, int32_t);
void SuccessFul(std::fstream&, FullStudent*, int32_t);
bool CompareAlphabetically(FullStudent&, FullStudent&);
void PrintGradeSheet(FullStudent*, int32_t, int32_t);
void PrintAvgGrade(FullStudent*, int32_t, int32_t);
FullStudent* GenerateGroupGradeSheet(FullStudent*, int32_t, int32_t, int32_t&);
FullStudent* GenerateGroupGradeAvg(FullStudent*, int32_t, int32_t, int32_t&);
void ReadFullStudFromBin(std::fstream&, FullStudent*, int32_t);
void BinToTxt(std::fstream&, std::fstream&);
void PrintBinary(std::fstream&);
void WriteStudentText(std::fstream&);
void SortByAverage(FullStudent*, int32_t);
void ValidateGrades(GradeRecord&);

#endif

