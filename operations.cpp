#include "operations.h"

void CheckFile(std::ifstream& file)
{
	if (!file.good())
	{
		throw std::runtime_error("File does not exist");
	}
	if (!file)
	{
		throw std::runtime_error("The file does not open");
	}
	if (file.peek() == EOF)
	{
		throw std::runtime_error("File is empty");
	}
}

void CheckOutputFile(std::fstream& fout)
{
	if (!fout.good())
	{
		throw std::runtime_error("File does not exist\n");
	}
	if (!fout)
	{
		throw std::runtime_error("The file does not open\n");
	}
}

int32_t CountPeople(std::ifstream& fin)
{
	fin.clear();
	fin.seekg(0, std::ios::beg);
	std::string tmp;
	int32_t counter{};
	while (getline(fin, tmp))
	{
		++counter;
	}
	return counter;
}

void InputPeople(std::ifstream& fin, std::string* people, int32_t size)
{
	fin.clear();
	fin.seekg(0, std::ios::beg);
	for (int32_t i = 0; i < size; ++i)
	{
		getline(fin, people[i]);
	}
}

void FillBinary(std::fstream& bin, std::string* people, int32_t size)
{
	for (int32_t i = 0; i < size; ++i)
	{
		bin.write(reinterpret_cast<char*>(&people[i]), sizeof people[i]);
	}
}

void FillStructuresFromStudents(std::ifstream& fin, FullStudent* students, int32_t size)
{
	fin.clear();
	fin.seekg(0, std::ios::beg);
	for (int32_t i = 0; i < size; ++i)
	{
		fin >> students[i].recordBook;
		fin.ignore();
		getline(fin, students[i].surname, ';');
		getline(fin, students[i].name, ';');
		getline(fin, students[i].patronymic);
	}
}

void FillStructuresFromMarks(std::ifstream& fin, GradeRecord* students, int32_t size)
{
	fin.clear();
	fin.seekg(0, std::ios::beg);
	std::string line;
	for (int32_t i{}; i < size; i++)
	{
		fin >> students[i].group;
		fin.ignore();
		fin >> students[i].recordBook;
		fin.ignore();
		getline(fin, line, ';');
		fin >> students[i].gradeMA;
		fin.ignore();
		getline(fin, line, ';');
		fin >> students[i].gradeGEO;
		fin.ignore();
		getline(fin, line, ';');
		fin >> students[i].gradePROG;
		fin.ignore();
	}
}

void MergeSurnamesMarks(FullStudent* students_a, GradeRecord* students_b, int32_t size_a, int32_t size_b)
{
	for (int32_t i = 0; i < size_a; ++i)
	{
		for (int32_t k = 0; k < size_b; ++k)
		{
			if (students_a[i].recordBook == students_b[k].recordBook)
			{
				students_a[i].group = students_b[k].group;
				students_a[i].gradeMA = students_b[k].gradeMA;
				students_a[i].gradeGEO = students_b[k].gradeGEO;
				students_a[i].gradePROG = students_b[k].gradePROG;
			}
		}
	}
}

void MakeBin(std::fstream& bin, FullStudent* students, int32_t size)
{
	std::string line;
	for (int32_t i = 0; i < size; ++i)
	{
		line = std::to_string(students[i].group);
		bin.write(reinterpret_cast<char*>(&line), sizeof line);
		line = std::to_string(students[i].recordBook);
		bin.write(reinterpret_cast<char*>(&line), sizeof line);
		line = students[i].surname;
		bin.write(reinterpret_cast<char*>(&line), sizeof line);
		line = students[i].name;
		bin.write(reinterpret_cast<char*>(&line), sizeof line);
		line = students[i].patronymic;
		bin.write(reinterpret_cast<char*>(&line), sizeof line);
		line = std::to_string(students[i].gradeMA);
		bin.write(reinterpret_cast<char*>(&line), sizeof line);
		line = std::to_string(students[i].gradeGEO);
		bin.write(reinterpret_cast<char*>(&line), sizeof line);
		line = std::to_string(students[i].gradePROG);
		bin.write(reinterpret_cast<char*>(&line), sizeof line);
	}
}

void MakeAverageBin(std::fstream& bin, StudentWithAverage* students, int32_t size)
{
	for (int32_t i = 0; i < size; ++i)
	{
		bin.write(reinterpret_cast<char*>(&students[i].group), sizeof students[i].group);
		bin.write(reinterpret_cast<char*>(&students[i].recordBook), sizeof students[i].recordBook);
		WriteString(bin, students[i].surname);
		WriteString(bin, students[i].name);
		WriteString(bin, students[i].patronymic);
		bin.write(reinterpret_cast<char*>(&students[i].averageGrade), sizeof students[i].averageGrade);
		PrintAverageGradeToCons(students[i].recordBook, students[i].surname, students[i].name, students[i].patronymic, students[i].averageGrade);
	}
}

void FillStructuresFromAverageMarks(std::fstream& fin, StudentWithAverage* students, int32_t size)
{
	fin.clear();
	fin.seekg(0, std::ios::beg);
	std::string line;
	for (int32_t i = 0; i < size; ++i)
	{
		fin >> students[i].group;
		fin.ignore();
		getline(fin, line, ';');
		fin >> students[i].recordBook;
		fin.ignore();
		getline(fin, line, ';');
		fin >> students[i].surname;
		fin.ignore();
		getline(fin, line, ';');
		fin >> students[i].name;
		fin.ignore();
		getline(fin, line, ';');
		fin >> students[i].patronymic;
		fin.ignore();
		getline(fin, line, ';');
		fin >> students[i].averageGrade;
		fin.ignore();
	}
}

void CalculateAverageAndWrite(std::fstream& outBin, FullStudent* full, StudentWithAverage* avgList, int32_t size)
{

	for (int32_t i = 0; i < size; ++i)
	{
		avgList[i].group = full[i].group;
		avgList[i].recordBook = full[i].recordBook;
		avgList[i].surname = full[i].surname;
		avgList[i].name = full[i].name;
		avgList[i].patronymic = full[i].patronymic;
		avgList[i].averageGrade = (full[i].gradeMA + full[i].gradeGEO + full[i].gradePROG) / 3;
	}
}

void WriteString(std::fstream& bin, std::string& str)
{
	int32_t len = static_cast<int32_t>(str.size());
	bin.write(reinterpret_cast<char*>(&len), sizeof len);
	bin.write(str.c_str(), len);
}

void SuccessFul(std::fstream& bin, FullStudent* students, int32_t size)
{
	std::cout << "List of excellent students, consisting of last name, group number, record book number\n";
	for (int32_t i = 0; i < size; ++i)
	{
		if (students[i].gradeMA > 8 && students[i].gradeGEO > 8 && students[i].gradePROG > 8)
		{
			WriteString(bin, students[i].surname);
			bin.write(reinterpret_cast<char*>(&students[i].group), sizeof students[i].group);
			bin.write(reinterpret_cast<char*>(&students[i].recordBook), sizeof students[i].recordBook);

			PrintStudentToConsole(students[i].surname, students[i].group, students[i].recordBook);

		}
	}
}

void MakeFailingBin(std::fstream& bin, FullStudent* students, int32_t size)
{
	std::cout << "List of unsuccessful students, consisting of last name, group number, record book number\n";
	for (int32_t i = 0; i < size; ++i)
	{
		if (students[i].gradeMA < 4 || students[i].gradeGEO < 4 || students[i].gradePROG < 4)
		{
			WriteString(bin, students[i].surname);
			bin.write(reinterpret_cast<char*>(&students[i].group), sizeof students[i].group);
			bin.write(reinterpret_cast<char*>(&students[i].recordBook), sizeof students[i].recordBook);

			PrintStudentToConsole(students[i].surname, students[i].group, students[i].recordBook);

		}
	}
}
void PrintAverageGradeToCons(int32_t recordBook, std::string& surname, std::string& name, std::string& patronymic, double averageGrade)
{

	std::cout << "Record Book: " << recordBook << "\n"
		<< "Surname:     " << surname << "\n"
		<< "Name:        " << name << "\n"
		<< "Patronymic:  " << patronymic << "\n"
		<< "Grade PROG:  " << averageGrade << "\n"
		<< "-----------------------------\n";

}
void PrintStudentToConsole(std::string& surname, int32_t group, int32_t recordBook)
{
	std::cout << "Surname:     " << surname << "\n"
		<< "Group:       " << group << "\n"
		<< "Record Book: " << recordBook << "\n"
		<< "-----------------------------\n";
}
void PrintStudentToConsole(int32_t group, int32_t recordBook, std::string& surname, std::string& name, std::string& patronymic, int32_t gradeMA, int32_t gradeGEO, int32_t gradePROG)
{
	std::cout << "Group: " << group << '\n'
		<< "Record Book: " << recordBook << '\n'
		<< "Surname:     " << surname << '\n'
		<< "Name:        " << name << '\n'
		<< "Patronymic:  " << patronymic << '\n'
		<< "Grade MA:    " << gradeMA << '\n'
		<< "Grade GEO:   " << gradeGEO << '\n'
		<< "Grade PROG:  " << gradePROG << '\n'
		<< "-----------------------------\n";
}


bool CompareFailing(FullStudent& a, FullStudent& b)
{
	if (a.group != b.group)
	{
		return a.group < b.group;
	}
	return a.surname < b.surname;
}

bool CompareByAvg(FullStudent& a, FullStudent& b)
{
	double avg_a{ (a.gradeMA + a.gradeGEO + a.gradePROG) / 3.0 };
	double avg_b{ (b.gradeMA + b.gradeGEO + b.gradePROG) / 3.0 };

	return avg_a > avg_b;
}

void Merge(FullStudent* arr, int32_t left, int32_t mid, int32_t right, FullStudent* temp, bool (*compareFunc)(FullStudent&, FullStudent&))
{
	int32_t i = left, j = mid, k = left;
	while (i < mid && j < right)
	{
		if (compareFunc(arr[i], arr[j]))
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}
	while (i < mid)
	{
		temp[k++] = arr[i++];
	}
	while (j < right)
	{
		temp[k++] = arr[j++];
	}
	for (int32_t l = left; l < right; ++l)
	{
		arr[l] = temp[l];
	}
}

void MergeSort(FullStudent* arr, int32_t left, int32_t right, FullStudent* temp, bool (*compareFunc)(FullStudent&, FullStudent&))
{
	if (right - left <= 1) return;
	int32_t mid = (left + right) / 2;
	MergeSort(arr, left, mid, temp, compareFunc);
	MergeSort(arr, mid, right, temp, compareFunc);
	Merge(arr, left, mid, right, temp, compareFunc);
}

void WriteSortedFailing(std::fstream& bin, FullStudent* failing, int32_t size)
{
	std::cout << "Sorted students\n";
	for (int32_t i = 0; i < size; ++i)
	{
		bin.write(reinterpret_cast<char*>(&failing[i].group), sizeof failing[i].group);
		WriteString(bin, failing[i].surname);
		bin.write(reinterpret_cast<char*>(&failing[i].recordBook), sizeof failing[i].recordBook);
	}
	PrintFailingStudentsToConsole(failing, size);
}

int32_t ExtractFailingStudents(FullStudent* students, int32_t size, FullStudent* failing)
{
	int32_t count = 0;
	for (int32_t i = 0; i < size; ++i)
	{
		if (students[i].gradeMA < 4 || students[i].gradeGEO < 4 || students[i].gradePROG < 4)
		{
			failing[count++] = students[i];
		}
	}
	return count;
}

void PrintFailingStudentsToConsole(FullStudent* failing, int32_t count)
{
	for (int32_t i = 0; i < count; ++i) {
		std::cout << "Group: " << failing[i].group << '\n'
			<< "Surname: " << failing[i].surname << '\n'
			<< "recordBook: " << failing[i].recordBook << '\n'
			<< "-----------------------------\n";
	}
}

bool CompareAlphabetically(FullStudent& a, FullStudent& b)
{
	if (a.surname != b.surname)
	{
		return a.surname < b.surname;
	}
	return a.name < b.name;
}

void PrintGradeSheet(FullStudent* students, int32_t size, int32_t targetGroup)
{
	std::cout << "Grade report for group " << targetGroup << " (sorted alphabetically):\n";
	for (int32_t i = 0; i < size; ++i)
	{
		std::cout << "Surname: " << students[i].surname << ", Name: " << students[i].name << ", Patronymic: " << students[i].patronymic
			<< ", Group: " << students[i].group << ", Grades: MA=" << students[i].gradeMA
			<< ", GEO=" << students[i].gradeGEO << ", PROG=" << students[i].gradePROG << std::endl;
	}
}

void PrintAvgGrade(FullStudent* students, int32_t size, int32_t targetGroup) {
	std::cout << "Grade report for group " << targetGroup << " (sorted by avg up-down):\n";
	for (int32_t i = 0; i < size; ++i) {
		double avg{ (students[i].gradeMA + students[i].gradeGEO + students[i].gradePROG) / 3.0 };
		std::cout << "Surname: " << students[i].surname << ", Name: " << students[i].name << ", Patronymic: " << students[i].patronymic
			<< ", Group: " << students[i].group << ", AVG: " << avg << std::endl;
	}
}

FullStudent* GenerateGroupGradeSheet(FullStudent* students, int32_t totalSize, int32_t targetGroup, int32_t& filteredSize) {
	FullStudent* filtered = new FullStudent[totalSize];
	filteredSize = 0;

	for (int32_t i = 0; i < totalSize; ++i)
	{
		if (students[i].group == targetGroup)
		{
			filtered[filteredSize++] = students[i];
		}
	}

	if (filteredSize > 0) {
		FullStudent* temp = new FullStudent[filteredSize];
		MergeSort(filtered, 0, filteredSize, temp, CompareAlphabetically);
		delete[] temp;
	}

	return filtered;
}

FullStudent* GenerateGroupGradeAvg(FullStudent* students, int32_t totalSize, int32_t targetGroup, int32_t& filteredSize) {
	FullStudent* filtered = new FullStudent[totalSize];
	filteredSize = 0;

	for (int32_t i = 0; i < totalSize; ++i) {
		if (students[i].group == targetGroup) {
			filtered[filteredSize++] = students[i];
		}
	}

	if (filteredSize > 0) {
		FullStudent* temp = new FullStudent[filteredSize];
		MergeSort(filtered, 0, filteredSize, temp, CompareByAvg);
		delete[] temp;
	}

	return filtered;
}

int32_t CountGroup(std::ifstream& fin, int32_t size_p) {
	int32_t* groups = new int32_t[size_p];
	int32_t count = 0;

	std::string str;
	fin.clear();
	fin.seekg(0, std::ios::beg);

	while (std::getline(fin, str)) {
		std::istringstream iss(str);
		std::string groupStr;

		if (std::getline(iss, groupStr, ';')) {
			int32_t group = std::stoi(groupStr);

			bool noyes = false;
			for (int32_t i = 0; i < count; ++i) {
				if (groups[i] == group) {
					noyes = true;
					break;
				}
			}

			if (!noyes && count < size_p) {
				groups[count++] = group;
			}
		}
	}

	delete[] groups;
	return count;
}

void GoodStud(FullStudent* student, int32_t size) {
	bool find{ false };
	std::fstream out("GoodStudents.bin", std::ios::out, std::ios::binary);
	for (int32_t i{}; i < size; ++i) {
		if (student[i].gradeMA > 7 && student[i].gradeGEO > 7 && student[i].gradePROG > 7) {
			find = true;
			WriteString(out, student[i].surname);
			out.write(reinterpret_cast<char*>(&student[i].group), sizeof(student[i].group));
			out.write(reinterpret_cast<char*>(&student[i].recordBook), sizeof(student[i].recordBook));
			std::cout << "\nList of the greatests students:\nSurname: " << student[i].surname << "; Group: "
				<< student[i].group << "; ID: " << student[i].recordBook << ".\n";
		}
	}
	if (!find) {
		std::cout << "No greatest students..." << std::endl;
	}
}

void BinToTxt(const std::string& binFile, const std::string& txtFile) {
	std::ifstream fin(binFile, std::ios::binary);
	CheckFile(fin);

	std::fstream fout(txtFile);
	CheckOutputFile(fout);

	while (fin.peek() != EOF) {
		FullStudent s;

		fin.read(reinterpret_cast<char*>(&s.group), sizeof(s.group));
		fin.read(reinterpret_cast<char*>(&s.recordBook), sizeof(s.recordBook));

		int32_t temp{};
		fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		s.surname.resize(temp);
		fin.read(&s.surname[0], temp);
		fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		s.name.resize(temp);
		fin.read(&s.name[0], temp);
		fin.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		s.patronymic.resize(temp);
		fin.read(&s.patronymic[0], temp);
		fin.read(reinterpret_cast<char*>(&s.gradeMA), sizeof(s.gradeMA));
		fin.read(reinterpret_cast<char*>(&s.gradeGEO), sizeof(s.gradeGEO));
		fin.read(reinterpret_cast<char*>(&s.gradePROG), sizeof(s.gradePROG));

		fout << s.group << ";" << s.recordBook << ";" << s.surname << ";"
			<< s.name << ";" << s.patronymic << ";" << s.gradeMA << ";"
			<< s.gradeGEO << ";" << s.gradePROG << std::endl;
	}

	fin.close();
	fout.close();
}
