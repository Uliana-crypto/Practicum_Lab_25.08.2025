#include "operations.h"

int main()
{
	try {
		std::ifstream fin_stud("Students.txt");
		CheckFile(fin_stud);
		int32_t size_p = CountPeople(fin_stud);
		std::string* lines = new std::string[size_p];
		InputPeople(fin_stud, lines, size_p);

		std::fstream bin_p("FillStudents.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(bin_p);
		FillBinary(bin_p, lines, size_p);
		bin_p.close();

		std::ifstream fin_grade("Studentgrades.txt");
		CheckFile(fin_grade);
		int32_t size_e = CountPeople(fin_grade);
		InputPeople(fin_grade, lines, size_e);

		if (size_p > size_e || size_p < size_e) {
			throw std::runtime_error("Student file contains more lines than marks file and conversely");
		}

		std::fstream bin_e("Grades.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(bin_e);
		FillBinary(bin_e, lines, size_e);
		bin_e.close();

		delete[] lines;

		FullStudent* students = new FullStudent[size_p];
		FillStructuresFromStudents(fin_stud, students, size_p);
		fin_stud.close();

		GradeRecord* grades = new GradeRecord[size_e];
		FillStructuresFromMarks(fin_grade, grades, size_e);
		for (int32_t i = 0; i < size_e; ++i) {
			ValidateGrades(grades[i]);
		}
		fin_grade.close();

		MergeSurnamesMarks(students, grades, size_p, size_e);
		std::fstream stud_bin("Merge.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(stud_bin);
		MakeBin(stud_bin, students, size_p);
		for (int32_t i{}; i < size_p; ++i) {
			PrintStudentToConsole(students[i].group, students[i].recordBook, students[i].surname, students[i].name, students[i].patronymic, students[i].gradeMA, students[i].gradeGEO, students[i].gradePROG);
		}
		stud_bin.close();

		std::fstream binFile("Merge.bin", std::ios::in);
		std::fstream stud_txt("Merge.txt", std::ios::out);
		CheckOutputFile(stud_txt);
		BinToTxt(binFile, stud_txt);
		binFile.close();
		stud_txt.close();

		std::fstream avg_bin("AverageScore.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(avg_bin);
		StudentWithAverage* avgList = new StudentWithAverage[size_p];
		FillStructuresFromAverageMarks(avg_bin, avgList, size_p);
		CalculateAverageAndWrite(avg_bin, students, avgList, size_p);
		MakeAverageBin(avg_bin, avgList, size_p);
		avg_bin.close();

		std::fstream bin("AverageScore.bin", std::ios::in);
		std::fstream txt("AverageScore.txt", std::ios::out);
		CheckOutputFile(txt);
		BinToTxt(bin, txt);
		bin.close();
		txt.close();

		std::fstream fail_bin("FailingStudents.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(fail_bin);
		MakeFailingBin(fail_bin, students, size_p);
		std::cout << "Array of failures before sorting\n";
		PrintBinary(fail_bin);
		fail_bin.close();

		std::fstream fail_bin_a("SuccessfulStudents.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(fail_bin_a);
		SuccessFul(fail_bin_a, students, size_p);
		fail_bin_a.close();

		FullStudent* failing = new FullStudent[size_p];
		int32_t failCount = ExtractFailingStudents(students, size_p, failing);
		FullStudent* temp = new FullStudent[failCount];
		MergeSort(failing, 0, failCount, temp, CompareFailing);

		std::fstream sortedFailBin("SortedFailing.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(sortedFailBin);
		WriteSortedFailing(sortedFailBin, failing, failCount);
		std::cout << "Array of failures after sorting\n";
		PrintBinary(sortedFailBin);
		sortedFailBin.close();

		std::fstream fail_bin_stat("StatementAlphabet.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(fail_bin_stat);

		int32_t targetGroup1{};
		int32_t targetGroup2{};
		std::cout << "\nEnter group number to sort alphabetically: ";
		std::cin >> targetGroup1;
		std::cin.ignore();

		int32_t filteredSize = 0;
		std::ifstream fin_group("Studentgrades.txt");
		CheckFile(fin_group);

		FullStudent* filtered = GenerateGroupGradeSheet(students, size_p, targetGroup1, filteredSize);
		PrintGradeSheet(filtered, filteredSize, targetGroup1);
		MakeBin(fail_bin_stat, filtered, filteredSize);
		fail_bin_stat.close();

		std::cout << "\nEnter group number to sort by average score: ";
		std::cin >> targetGroup2;
		std::cin.ignore();

		FullStudent* sortedByAvg = GenerateGroupGradeAvg(students, size_p, targetGroup2, filteredSize);
		PrintAvgGrade(sortedByAvg, filteredSize, targetGroup2);
		MakeBin(fail_bin_stat, sortedByAvg, filteredSize);
		fin_group.close();


		delete[]students;
		delete[]grades;
		delete[]failing;
		delete[]temp;
		delete[]avgList;
		delete[]filtered;
		delete[]sortedByAvg;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}