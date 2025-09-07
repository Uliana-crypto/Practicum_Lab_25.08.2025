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
	if (counter == 0)
	{
		throw std::runtime_error("No lines were found");
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
		int32_t len = people[i].size();
		bin.write((char*)&len, sizeof(len));
		bin.write(people[i].c_str(), len);
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
	for (int32_t i{}; i < size; ++i)
	{
		line = students[i].name + ';';
		bin.write(line.c_str(), line.size());
		line = students[i].surname + ';';
		bin.write(line.c_str(), line.size());
		line = students[i].patronymic + ';';
		bin.write(line.c_str(), line.size());
		line = std::to_string(students[i].group) + ';';
		bin.write(line.c_str(), line.size());
		line = std::to_string(students[i].recordBook) + ';';
		bin.write(line.c_str(), line.size());
		line = std::to_string(students[i].gradeMA) + ';';
		bin.write(line.c_str(), line.size());
		line = std::to_string(students[i].gradeGEO) + ';';
		bin.write(line.c_str(), line.size());
		line = std::to_string(students[i].gradePROG) + '\n';
		bin.write(line.c_str(), line.size());
	}
}

void MakeAverageBin(std::fstream& bin, StudentWithAverage* students, int32_t size)
{
	bin.clear();
	bin.seekp(0, std::ios::beg);
	std::string line;
	for (int32_t i = 0; i < size; ++i)
	{
		line = std::to_string(students[i].group) + ';';
		bin.write(line.c_str(), line.size());
		line = std::to_string(students[i].recordBook) + ';';
		bin.write(line.c_str(), line.size());
		line = students[i].surname + ';';
		bin.write(line.c_str(), line.size());
		line = students[i].name + ';';
		bin.write(line.c_str(), line.size());
		line = students[i].patronymic + ';';
		bin.write(line.c_str(), line.size());
		line = std::to_string(students[i].averageGrade) + ';';
		bin.write(line.c_str(), line.size());
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
		avgList[i].averageGrade = (full[i].gradeMA + full[i].gradeGEO + full[i].gradePROG) / 3.0;
	}
}

void SuccessFul(std::fstream& bin, FullStudent* students, int32_t size)
{
	std::string line;
	bool found = false;
	std::cout << "List of excellent students, consisting of last name, group number, record book number\n";
	for (int32_t i = 0; i < size; ++i)
	{
		if (students[i].gradeMA > 8 && students[i].gradeGEO > 8 && students[i].gradePROG > 8)
		{
			found = true;
			line = students[i].surname + ';';
			bin.write(line.c_str(), line.size());
			line = students[i].group + ';';
			bin.write(line.c_str(), line.size());
			line = students[i].recordBook + ';';
			bin.write(line.c_str(), line.size());
			PrintStudentToConsole(students[i].surname, students[i].group, students[i].recordBook);

		}
	}
	if (!found)
	{
		std::cout << "No excellent students found\n";
	}
}

void MakeFailingBin(std::fstream& bin, FullStudent* students, int32_t size)
{
	std::string line;
	std::cout << "List of unsuccessful students, consisting of last name, group number, record book number\n";
	for (int32_t i = 0; i < size; ++i)
	{
		if (students[i].gradeMA < 4 || students[i].gradeGEO < 4 || students[i].gradePROG < 4)
		{
			line = students[i].surname + ';';
			bin.write(line.c_str(), line.size());
			line = students[i].group + ';';
			bin.write(line.c_str(), line.size());
			line = students[i].recordBook + ';';
			bin.write(line.c_str(), line.size());
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
	int32_t i = left;
	int32_t j = mid;
	int32_t k = left;
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

void MergeSort(FullStudent* arr, int32_t left, int32_t right, FullStudent* temp,
	bool (*compareFunc)(FullStudent&, FullStudent&))
{
	if (right - left <= 1)
	{
		return;
	}
	int32_t mid = (left + right) / 2;
	MergeSort(arr, left, mid, temp, compareFunc);
	MergeSort(arr, mid, right, temp, compareFunc);
	Merge(arr, left, mid, right, temp, compareFunc);
}

void WriteSortedFailing(std::fstream& bin, FullStudent* failing, int32_t size)
{
	std::string line;
	std::cout << "Sorted students\n";
	for (int32_t i = 0; i < size; ++i)
	{
		line = failing[i].group + ';';
		bin.write(line.c_str(), line.size());
		line = failing[i].surname + ';';
		bin.write(line.c_str(), line.size());
		line = failing[i].recordBook + ';';
		bin.write(line.c_str(), line.size());
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
	if (count == 0)
	{
		std::cout << "No failing students found\n";
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
	if (filteredSize == 0) {
		delete[] filtered;
		throw std::runtime_error("No students found in the specified group");
	}
	FullStudent* temp = new FullStudent[filteredSize];
	MergeSort(filtered, 0, filteredSize, temp, CompareAlphabetically);
	delete[] temp;

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
	if (filteredSize == 0) {
		delete[] filtered;
		throw std::runtime_error("No students found in the specified group");
	}

	FullStudent* temp = new FullStudent[filteredSize];
	MergeSort(filtered, 0, filteredSize, temp, CompareByAvg);
	delete[] temp;


	return filtered;
}

void BinToTxt(std::fstream& binFile, std::fstream& txtFile) {

	std::string line;
	while (std::getline(binFile, line)) {
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string name, surname, patronymic, group, recordBook, gradeMA, gradeGEO, gradePROG;
		std::getline(ss, name, ';');
		std::getline(ss, surname, ';');
		std::getline(ss, patronymic, ';');
		std::getline(ss, group, ';');
		std::getline(ss, recordBook, ';');
		std::getline(ss, gradeMA, ';');
		std::getline(ss, gradeGEO, ';');
		std::getline(ss, gradePROG, ';');

		txtFile << "Name: " << name << ", Surname: " << surname << ", Patronymic: " << patronymic
			<< ", Group: " << group << ", Record Book: " << recordBook
			<< ", Grades: MA=" << gradeMA << ", GEO=" << gradeGEO << ", PROG=" << gradePROG << "\n";
	}

	binFile.close();
	txtFile.close();
}

void PrintBinary(std::fstream& bin) {
	bin.seekg(0, std::ios::end);
	size_t arraySize = static_cast<size_t>(bin.tellg());
	bin.seekg(0, std::ios::beg);
	char* cText = new char[arraySize];
	bin.read(cText, arraySize);
	std::string binText{ cText, arraySize };
	delete[] cText;
	std::cout << binText << '\n';
}

void SortByAverage(FullStudent* arr, int32_t size) {
	std::sort(arr, arr + size, CompareByAvg);
}

void ValidateGrades(GradeRecord& student)
{
	if (student.gradeMA < 2 || student.gradeMA > 10 || student.gradeGEO < 2 || student.gradeGEO > 10 || student.gradePROG < 2 || student.gradePROG > 10)
	{
		throw std::runtime_error("Grades must be between 2 and 10.");
	}
}