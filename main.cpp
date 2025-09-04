#include "operations.h"

int main()
{
	try {
		std::ifstream fin_stud("Students.txt");
		CheckFile(fin_stud);
		std::fstream bin_p("Parent.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(bin_p);
		int32_t size_p = CountPeople(fin_stud);
		std::string* lines = new std::string[size_p];
		InputPeople(fin_stud, lines, size_p);
		FillBinary(bin_p, lines, size_p);

		std::string line;
		bin_p.seekg(0, std::ios::beg);
		bin_p.seekp(0, std::ios::beg);
		while (bin_p.read(reinterpret_cast<char*>(&line), sizeof line))
		{
			std::cout << line << '\n';
		}

		std::ifstream fin_mark("Studentgrades.txt");
		CheckFile(fin_mark);
		std::fstream bin_e("Elementary.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(bin_e);
		int32_t size_e = CountPeople(fin_mark);
		InputPeople(fin_mark, lines, size_e);
		FillBinary(bin_e, lines, size_e);


		bin_e.seekg(0, std::ios::beg);
		bin_e.seekp(0, std::ios::beg);
		while (bin_e.read(reinterpret_cast<char*>(&line), sizeof line))
		{
			std::cout << line << '\n';
		}

		FullStudent* students = new FullStudent[size_p];
		FillStructuresFromStudents(fin_stud, students, size_p);

		GradeRecord* marks = new GradeRecord[size_e];
		FillStructuresFromMarks(fin_mark, marks, size_e);
		MergeSurnamesMarks(students, marks, size_p, size_e);
		std::fstream stud_bin("Merge.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(stud_bin);
		MakeBin(stud_bin, students, size_p);
		for (int32_t i{}; i < size_p; ++i) {
			PrintStudentToConsole(students[i].group, students[i].recordBook, students[i].surname, students[i].name, students[i].patronymic, students[i].gradeMA, students[i].gradeGEO, students[i].gradePROG);
		}
		stud_bin.close();

		std::fstream avg_bin("AverageScore.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(avg_bin);
		StudentWithAverage* avgList = new StudentWithAverage[size_p];
		FillStructuresFromAverageMarks(avg_bin, avgList, size_p);
		CalculateAverageAndWrite(avg_bin, students, avgList, size_p);
		MakeAverageBin(avg_bin, avgList, size_p);
		avg_bin.close();

		std::fstream fail_bin("FailingStudents.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(fail_bin);
		MakeFailingBin(fail_bin, students, size_p);
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
		sortedFailBin.close();

		std::fstream fail_bin_stat("StatementAlphabet.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckOutputFile(fail_bin_stat);
		int32_t targetGroup1{}, targetGroup2{};
		std::cout << "\nEnter the group number for the statement: ";
		std::cin >> targetGroup1;
		std::cin.ignore();
		int32_t filteredSize = 0;
		std::ifstream fin_group("Studentgrades.txt");
		CheckFile(fin_group);
		int32_t totalGroup = CountGroup(fin_group, size_p);

		FullStudent* filtered = GenerateGroupGradeSheet(students, size_p, targetGroup1, filteredSize);
		PrintGradeSheet(filtered, filteredSize, targetGroup1);
		MakeBin(fail_bin_stat, filtered, filteredSize);

		std::cout << "\nEnter the group number for the statement: ";
		std::cin >> targetGroup2;
		std::cin.ignore();
		FullStudent* sortedByAvg = GenerateGroupGradeAvg(students, size_p, targetGroup2, filteredSize);
		PrintAvgGrade(sortedByAvg, filteredSize, targetGroup2);
		MakeBin(fail_bin_stat, sortedByAvg, filteredSize);

		GoodStud(students, size_p);

		//BinToTxt("AverageScore.bin", "AverageScore.txt");
		BinToTxt("Merge.bin", "Merge.txt");


		delete[]students;
		delete[]marks;
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