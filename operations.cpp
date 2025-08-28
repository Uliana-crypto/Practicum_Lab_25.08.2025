#include "operations.h"

void checkFile(std::ifstream& file)
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

void checkOutputFile(std::fstream& fout)
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

int32_t countPeople(std::ifstream& fin)
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

void inputPeople(std::ifstream& fin, std::string* people, int32_t size)
{
	fin.clear();
	fin.seekg(0, std::ios::beg);
	for (int32_t i = 0; i < size; ++i)
	{
		getline(fin, people[i]);
	}
}

void fillBinary(std::fstream& bin, std::string* people, int32_t size)
{
	for (int32_t i = 0; i < size; ++i)
	{
		bin.write(reinterpret_cast<char*>(&people[i]), sizeof people[i]);
	}
}

void fillStructuresFromStudents(std::ifstream& fin, FullStudent* students, int32_t size)
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

void fillStructuresFromMarks(std::ifstream& fin, GradeRecord* students, int32_t size)
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

void mergeSurnamesMarks(FullStudent* students_a, GradeRecord* students_b, int32_t size_a, int32_t size_b)
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

void makeMainBin(std::fstream& bin, FullStudent* students, int32_t size)
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
		printStudentToConsole(students[i].group, students[i].recordBook, students[i].surname, students[i].name, students[i].patronymic, students[i].gradeMA, students[i].gradeGEO, students[i].gradePROG);

	}
}

void makeAverageBin(std::fstream& bin, StudentWithAverage* students, int32_t size)
{
	for (int32_t i = 0; i < size; ++i)
	{
		bin.write(reinterpret_cast<char*>(&students[i].group), sizeof students[i].group);
		bin.write(reinterpret_cast<char*>(&students[i].recordBook), sizeof students[i].recordBook);
		writeString(bin, students[i].surname);
		writeString(bin, students[i].name);
		writeString(bin, students[i].patronymic);
		bin.write(reinterpret_cast<char*>(&students[i].averageGrade), sizeof students[i].averageGrade);
		printAverageGradeToCons(students[i].recordBook, students[i].surname, students[i].name, students[i].patronymic, students[i].averageGrade);
	}
}

void fillStructuresFromAverageMarks(std::fstream& fin, StudentWithAverage* students, int32_t size)
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

void calculateAverageAndWrite(std::fstream& outBin, FullStudent* full, StudentWithAverage* avgList, int32_t size)
{

	for (int32_t i = 0; i < size; ++i)
	{
		avgList[i].group = full[i].group;
		avgList[i].recordBook = full[i].recordBook;
		avgList[i].surname = full[i].surname;
		avgList[i].name = full[i].name;
		avgList[i].patronymic = full[i].patronymic;
		avgList[i].averageGrade = (full[i].gradeMA + full[i].gradeGEO + full[i].gradePROG) / 3.0f;
	}
}

void writeString(std::fstream& bin, std::string& str)
{
	int32_t len = static_cast<int32_t>(str.size());
	bin.write(reinterpret_cast<char*>(&len), sizeof len);
	bin.write(str.c_str(), len);
}

void makeFailingBin(std::fstream& bin, FullStudent* students, int32_t size)
{
	for (int32_t i = 0; i < size; ++i)
	{
		if (students[i].gradeMA < 4 || students[i].gradeGEO < 4 || students[i].gradePROG < 4)
		{
			writeString(bin, students[i].surname);
			bin.write(reinterpret_cast<char*>(&students[i].group), sizeof students[i].group);
			bin.write(reinterpret_cast<char*>(&students[i].recordBook), sizeof students[i].recordBook);

			printStudentToConsole(students[i].surname, students[i].group, students[i].recordBook);

		}
	}
}
void printAverageGradeToCons(int32_t recordBook, std::string& surname, std::string& name, std::string& patronymic, float averageGrade)
{

	std::cout << "Record Book: " << recordBook << "\n"
		<< "Surname:     " << surname << "\n"
		<< "Name:        " << name << "\n"
		<< "Patronymic:  " << patronymic << "\n"
		<< "Grade PROG:  " << averageGrade << "\n"
		<< "-----------------------------\n";

}
void printStudentToConsole(std::string& surname, int32_t group, int32_t recordBook)
{
	std::cout << "Surname:     " << surname << "\n"
		<< "Group:       " << group << "\n"
		<< "Record Book: " << recordBook << "\n"
		<< "-----------------------------\n";
}
void printStudentToConsole(int32_t group, int32_t recordBook, std::string& surname, std::string& name, std::string& patronymic, int32_t gradeMA, int32_t gradeGEO, int32_t gradePROG)
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


bool compareFailing(FullStudent& a, FullStudent& b)
{
	if (a.group != b.group)
	{
		return a.group < b.group;
	}
	return a.surname < b.surname;
}

void merge(FullStudent* arr, int32_t left, int32_t mid, int32_t right, FullStudent* temp)
{
	int32_t i = left, j = mid, k = left;
	while (i < mid && j < right)
	{
		if (compareFailing(arr[i], arr[j]))
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

void mergeSort(FullStudent* arr, int32_t left, int32_t right, FullStudent* temp)
{
	if (right - left <= 1) return;
	int32_t mid = (left + right) / 2;
	mergeSort(arr, left, mid, temp);
	mergeSort(arr, mid, right, temp);
	merge(arr, left, mid, right, temp);
}

void writeSortedFailing(std::fstream& bin, FullStudent* failing, int32_t size)
{
	for (int32_t i = 0; i < size; ++i)
	{
		bin.write(reinterpret_cast<char*>(&failing[i].group), sizeof failing[i].group);
		writeString(bin, failing[i].surname);
		bin.write(reinterpret_cast<char*>(&failing[i].recordBook), sizeof failing[i].recordBook);
	}
	printFailingStudentsToConsole(failing, size);
}

int32_t extractFailingStudents(FullStudent* students, int32_t size, FullStudent* failing)
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

void printFailingStudentsToConsole(FullStudent* failing, int32_t count)
{
	for (int32_t i = 0; i < count; ++i) {
		std::cout << "Group: " << failing[i].group << '\n'
			<< "Surname: " << failing[i].surname << '\n'
			<< "recordBook: " << failing[i].recordBook << '\n'
			<< "-----------------------------\n";
	}
}