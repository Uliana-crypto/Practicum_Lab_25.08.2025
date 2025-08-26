#include "operations.h"

int main()
{
	try {
		std::ifstream fin_stud("Students.txt");
		checkFile(fin_stud);
		std::fstream bin_p("Parent.bin", std::ios::in | std::ios::out | std::ios::binary);
		checkOutputFile(bin_p);
		int32_t size_p = countPeople(fin_stud);
		std::string* lines = new std::string[size_p];
		inputPeople(fin_stud, lines, size_p);
		fillBinary(bin_p, lines, size_p);

		std::string line;
		bin_p.seekg(0, std::ios::beg);
		bin_p.seekp(0, std::ios::beg);
		while (bin_p.read(reinterpret_cast<char*>(&line), sizeof line))
		{
			std::cout << line << '\n';
		}

		std::ifstream fin_mark("Studentgrades.txt");
		checkFile(fin_mark);
		std::fstream bin_e("Elementary.bin", std::ios::in | std::ios::out | std::ios::binary);
		checkOutputFile(bin_e);
		int32_t size_e = countPeople(fin_mark);
		inputPeople(fin_mark, lines, size_e);
		fillBinary(bin_e, lines, size_e);


		bin_e.seekg(0, std::ios::beg);
		bin_e.seekp(0, std::ios::beg);
		while (bin_e.read(reinterpret_cast<char*>(&line), sizeof line))
		{
			std::cout << line << '\n';
		}

		FullStudent* students = new FullStudent[size_p];
		fillStructuresFromStudents(fin_stud, students, size_p);

		GradeRecord* marks = new GradeRecord[size_e];
		fillStructuresFromMarks(fin_mark, marks, size_e);
		mergeSurnamesMarks(students, marks, size_p, size_e);
		std::fstream stud_bin("Merge.bin", std::ios::in | std::ios::out | std::ios::binary);
		checkOutputFile(stud_bin);
		makeMainBin(stud_bin, students, size_p);

		for (int32_t i = 0; i < size_p; ++i) {
			std::cout << "Group: " << students[i].group << '\n'
				<< "Record Book: " << students[i].recordBook << '\n'
				<< "Surname:     " << students[i].surname << '\n'
				<< "Name:        " << students[i].name << '\n'
				<< "Patronymic:  " << students[i].patronymic << '\n'
				<< "Grade MA:    " << students[i].gradeMA << '\n'
				<< "Grade GEO:   " << students[i].gradeGEO << '\n'
				<< "Grade PROG:  " << students[i].gradePROG << '\n'
				<< "-----------------------------\n";
		}

		std::fstream avg_bin("Average.bin", std::ios::in | std::ios::out | std::ios::binary);
		checkOutputFile(avg_bin);
		StudentWithAverage* avgList = new StudentWithAverage[size_p];
		fillStructuresFromAverageMarks(avg_bin, avgList, size_p);
		calculateAverageAndWrite(avg_bin, students, avgList, size_p);
		makeAverageBin(avg_bin, avgList, size_p);
		for (int32_t i = 0; i < size_p; ++i) {
			std::cout << "Record Book: " << avgList[i].recordBook << "\n"
				<< "Surname:     " << avgList[i].surname << "\n"
				<< "Name:        " << avgList[i].name << "\n"
				<< "Patronymic:  " << avgList[i].patronymic << "\n"
				<< "Grade PROG:  " << avgList[i].averageGrade << "\n"
				<< "-----------------------------\n";
		}

		avg_bin.close();

		delete[] avgList;
		delete[] students;
		delete[] marks;
	}
	catch (const std::exception& e) 
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}