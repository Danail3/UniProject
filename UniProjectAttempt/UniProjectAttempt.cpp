/**
*
* Solution to course project # <номер на вариант>
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Danail Todorov Todorov
* @idnumber 0MI0600241
* @compiler VC
*
* <Main File>
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

const int CAPACITY = 1024;
const int MAX_SIZE = 1024;
const int MAX_STUDENTS = 10;
const int MAX_CAPACITY = 50;


struct Subject
{
	char name[50];
	double grade;
};

struct Student
{
	int group;
	char firstName[50];
	char secName[50];
	char thirdName[50];
	char facultyNum[50];
	Subject sub[10];
};

Student studentsGroup1[MAX_STUDENTS];
Student studentsGroup2[MAX_STUDENTS];
Student studentsGroup3[MAX_STUDENTS];
Student studentsGroup4[MAX_STUDENTS];
Student studentsGroup5[MAX_STUDENTS];
Student studentsGroup6[MAX_STUDENTS];
Student studentsGroup7[MAX_STUDENTS];
Student studentsGroup8[MAX_STUDENTS];
Student sortedStudents[MAX_SIZE];

void isOpen(fstream& Document)
{
	if (!Document.is_open())
	{
		cout << " Error!" << endl;
		return;
	}
}

int numberOfLetters(char* arr1)
{
	int counter = 0;
	for (int i = 0; arr1[i] != '\0'; i++)
	{
		counter++;
	}
	return counter;
}

int validationForName(char* name)
{
	int lengthOfName = numberOfLetters(name);
	for (int i = 0; i < lengthOfName; i++)
	{
		if ((name[i] < 65 || name[i] > 122) || (name[i] > 90 && name[i] < 97))
		{
			cout << " The name must contain only letters!" << endl;
			return 0;
		}
	}
	return 1;
}

int validationForFacultyNum(char* facultyNum)
{
	int lengthFacultyNum = numberOfLetters(facultyNum);
	if (lengthFacultyNum != 10)
	{
		cout << " The faculty number must contain 10 characters" << endl;
		return 0;
	}
	for (int i = 0; i < lengthFacultyNum; i++)
	{
		if (facultyNum[i] < 48 || (facultyNum[i] > 57 && facultyNum[i] < 65) || (facultyNum[i] > 90 && facultyNum[i] < 97) || facultyNum[i] > 122)
		{
			cout << " The faculty number must not contain speacial symbols!" << endl;
			return 0;
		}
	}
	return 1;
}

//Funciton to check all validations
void validation(int (*func) (char*), char* myArr)
{
	while (func(myArr) == 0)
	{
		cout << " Try again: ";
		cin.getline(myArr, MAX_SIZE);
	}
}

void validationForSubjects(char* numberOfSubjectsChar, int& numberOfSubjectsInt)
{
	int lengthOfSubChar = numberOfLetters(numberOfSubjectsChar);
	numberOfSubjectsInt = atoi(numberOfSubjectsChar);
	while ((numberOfSubjectsInt < 1 || numberOfSubjectsInt > 10) || lengthOfSubChar != 1 || (lengthOfSubChar == 2 && numberOfSubjectsInt != 10))
	{
		cout << " You can enter between 1 and 10 subjects!" << endl;
		cout << " How many subjects do you want to add? - ";
		cin >> numberOfSubjectsChar;
		cin.ignore();
		numberOfSubjectsInt = atoi(numberOfSubjectsChar);
		lengthOfSubChar = numberOfLetters(numberOfSubjectsChar);
	}
}

int lengthBeforeDot(string grade)
{
	int lengthGrade = grade.length();
	int counter = 0;
	for (int i = 0; i < lengthGrade; i++)
	{
		if (grade[i] == '.' || grade[i] == ',')
		{
			break;
		}
		counter++;
	}
	return counter;
}

bool isValidDecimal(int lengthOfGrade, string grade)
{
	for (int i = 0; i < lengthOfGrade; i++)
	{
		if (i == 0 && (grade[i] < '2' || grade[i] > '6'))
		{
			return false;
		}
		else if (i == 1 && (grade[i] != '.' && grade[i] != ','))
		{
			return false;
		}
		else if (i > 1 && grade[i] < '0' || grade[i] > '9')
		{
			return false;
		}
	}
	return true;
}

void validationForGrade(string grade, double& normalGrade)
{
	int lengthOfGrade = grade.length();
	bool isValidDec = isValidDecimal(lengthOfGrade, grade);
	int lengthBeforeTheDot = lengthBeforeDot(grade);
	while (!isValidDec)
	{
		cout << " The grade must not contain special symbols or characters or it must be between 2 and 6!" << endl;
		cout << " Grade: ";
		getline(cin, grade);
		lengthOfGrade = grade.length();
		lengthBeforeTheDot = lengthBeforeDot(grade);
		isValidDec = isValidDecimal(lengthOfGrade, grade);
	}
	normalGrade = stod(grade);
}

void fillStudent(Student& stud, int group, int& numberOfSubjects)
{
	char numberOfSubjectsChar[10]{};
	stud.group = group;
	cout << " First Name: ";
	cin.getline(stud.firstName, MAX_SIZE);
	validation(validationForName, stud.firstName);

	cout << " Second Name: ";
	cin.getline(stud.secName, MAX_SIZE);

	validation(validationForName, stud.secName);

	cout << " Third Name: ";
	cin.getline(stud.thirdName, MAX_SIZE);

	validation(validationForName, stud.thirdName);

	cout << " Faculty Number: ";
	cin.getline(stud.facultyNum, MAX_SIZE);

	validation(validationForFacultyNum, stud.facultyNum);

	cout << " How many subjects do you want to add? - ";
	cin >> numberOfSubjectsChar;
	cin.ignore();

	validationForSubjects(numberOfSubjectsChar, numberOfSubjects);
	for (int i = 0; i < numberOfSubjects; i++)
	{
		string grade = "";
		cout << " Subject " + to_string(i + 1) + ":" << endl;
		cout << " Subject: ";
		cin.getline(stud.sub[i].name, MAX_SIZE);
		cout << " Grade: ";
		getline(cin, grade);
		validationForGrade(grade, stud.sub[i].grade);
		cout << endl;
	}
}

void inputStud(Student* stud, int indexStudent, int& group, int& numberOfSubjects)
{
	fillStudent(stud[indexStudent], group, numberOfSubjects);
	cout << endl;
}

//getting the array for the current student group
Student* getDocument(int group)
{
	if (group == 1)
	{
		return studentsGroup1;
	}
	else if (group == 2)
	{
		return studentsGroup2;
	}
	else if (group == 3)
	{
		return studentsGroup3;
	}
	else if (group == 4)
	{
		return studentsGroup4;
	}
	else if (group == 5)
	{
		return studentsGroup5;
	}
	else if (group == 6)
	{
		return studentsGroup6;
	}
	else if (group == 7)
	{
		return studentsGroup7;
	}
	else if (group == 8)
	{
		return studentsGroup8;
	}
	return studentsGroup1;
}

void directlyWritten(fstream& document, int index, Student* stud, int numberOfSubjects = 0)
{
	if (document.is_open())
	{
		document << stud[index].group << ' '
			<< stud[index].firstName << ' '
			<< stud[index].secName << ' '
			<< stud[index].thirdName << ' '
			<< stud[index].facultyNum << ' ';
		for (int j = 0; stud[index].sub[j].name[0] != '\0'; j++)
		{
			if (stud[index].sub[j].name[0] != '\0')
			{
				document << stud[index].sub[j].name << ' ' << stud[index].sub[j].grade;
				numberOfSubjects++;
			}
			if (stud[index].sub[j + 1].name[0] != '\0')
			{
				document << ' ';
			}
			if (stud[index].sub[j + 1].name[0] == '\0')
			{
				document << endl;
				break;
			}
		}
	}
}

void writeIntoFile(Student* stud, int index, int group, bool append = true, int numberOfSubjects = 0)
{
	string path = "";
	path = "Group_" + to_string(group) + ".txt";
	fstream currentDocument;
	if (append)
	{
		if (group == 0)
		{
			currentDocument.open("Sorted_Combined.txt", ios::out | ios::app);
		}
		else
		{
			currentDocument.open(path, ios::out | ios::app);
		}
	}
	else
	{
		if (group == 0)
		{
			currentDocument.open("Sorted_Combined.txt", ios::out);
		}
		else
		{
			currentDocument.open(path, ios::out);
		}
	}

	directlyWritten(currentDocument, index, stud, numberOfSubjects);
	currentDocument.close();
}

void readFromFile(int group = 0)
{
	string path = "";
	path = "Group_" + to_string(group) + ".txt";
	fstream currentDocument;
	if (group == 0)
	{
		currentDocument.open("Sorted_Combined.txt", ios::in);
	}
	else
	{
		currentDocument.open(path, ios::in);
	}
	if (currentDocument.is_open())
	{
		string line;
		while (getline(currentDocument, line))
		{
			cout << " " << line << endl;
		}
		currentDocument.close();
	}
	else
	{
		isOpen(currentDocument);
	}

}

int returnBiggerNumber(int num1, int num2)
{
	if (num1 > num2)
	{
		return num1;
	}
	return num2;
}

bool isTheFirstBigger(double num1, double num2)
{
	if (num1 > num2)
	{
		return true;
	}
	return false;
}

void copyTwoStrings(char* first, char* second)
{
	for (int i = 0; second[i] != '\0'; i++)
	{
		first[i] = second[i];
	}
}

void fillArrayWithZeros(char* myArr)
{
	for (int i = 0; myArr[i] != '\0'; i++)
	{
		myArr[i] = '\0';
	}
}

void WriteTheDataIntoTheStudent(char* getInfoArr, int& indexStart, string line, int& indexReading, char* whichOneToFill)
{
	for (int i = indexReading + 2; line[i] != ' '; i++)
	{
		getInfoArr[indexStart] = line[i];
		indexStart++;
		indexReading = i;
	}
	copyTwoStrings(whichOneToFill, getInfoArr);
	fillArrayWithZeros(getInfoArr);
	indexStart = 0;
}

//Save already written data into the arrays of structures
void saveTheDataFromTheFiles(Student* stud, int group)
{
	string path = "";
	path = "Group_" + to_string(group) + ".txt";
	fstream currentDocument;
	currentDocument.open(path, ios::in);

	if (currentDocument.is_open())
	{
		string line;
		int indexStudent = 0;
		while (getline(currentDocument, line))
		{
			int lengthOfLine = size(line);
			line[lengthOfLine] = '\0';

			stud[indexStudent].group = line[0] - '0';
			char getInformationArr[CAPACITY]{};
			int indexToStartPuttingInfo = 0;
			int indexToStartReadingFrom = 0;
			WriteTheDataIntoTheStudent(getInformationArr, indexToStartPuttingInfo, line, indexToStartReadingFrom, stud[indexStudent].firstName);
			WriteTheDataIntoTheStudent(getInformationArr, indexToStartPuttingInfo, line, indexToStartReadingFrom, stud[indexStudent].secName);
			WriteTheDataIntoTheStudent(getInformationArr, indexToStartPuttingInfo, line, indexToStartReadingFrom, stud[indexStudent].thirdName);
			WriteTheDataIntoTheStudent(getInformationArr, indexToStartPuttingInfo, line, indexToStartReadingFrom, stud[indexStudent].facultyNum);
			int indexForSubjects = 0;
			while (line[indexToStartReadingFrom + 1] != '\0')
			{
				WriteTheDataIntoTheStudent(getInformationArr, indexToStartPuttingInfo, line, indexToStartReadingFrom, stud[indexStudent].sub[indexForSubjects].name);
				for (int i = indexToStartReadingFrom + 2; line[i] != ' ' && line[i] != '\0'; i++)
				{
					getInformationArr[indexToStartPuttingInfo] = line[i];
					indexToStartPuttingInfo++;
					indexToStartReadingFrom = i;
				}
				stud[indexStudent].sub[indexForSubjects].grade = stod(getInformationArr);
				indexForSubjects++;
				fillArrayWithZeros(getInformationArr);
				indexToStartPuttingInfo = 0;
			}
			indexStudent++;
		}
		currentDocument.close();
	}
}

//Counting how many students are already written in the file
int howManyStudentsInFile(Student* stud)
{
	int counter = 0;
	for (int i = 0; stud[i].group != 0; i++)
	{
		counter++;
	}
	return counter;
}

//Compare whether two arrays are the same
bool areTheCharArraysTheSame(char* arr1, char* arr2)
{
	int lengthFirstArr = numberOfLetters(arr1);
	int lengthSecondArr = numberOfLetters(arr2);
	int biggerNum = returnBiggerNumber(lengthFirstArr, lengthSecondArr);
	if (lengthFirstArr != lengthSecondArr)
	{
		return false;
	}
	for (int i = 0; i < biggerNum; i++)
	{
		if (arr1[i] != arr2[i])
		{
			return false;
		}
	}
	return true;
}

void saveTheDataToEverygroup()
{
	saveTheDataFromTheFiles(studentsGroup1, 1);
	saveTheDataFromTheFiles(studentsGroup2, 2);
	saveTheDataFromTheFiles(studentsGroup3, 3);
	saveTheDataFromTheFiles(studentsGroup4, 4);
	saveTheDataFromTheFiles(studentsGroup5, 5);
	saveTheDataFromTheFiles(studentsGroup6, 6);
	saveTheDataFromTheFiles(studentsGroup7, 7);
	saveTheDataFromTheFiles(studentsGroup8, 8);
}

void copyStructs(Student* first, Student* second)
{
	for (int i = 0; i < 10; i++)
	{
		first[i].group = second[i].group;
		copyTwoStrings(first[i].firstName, second[i].firstName);
		copyTwoStrings(first[i].secName, second[i].secName);
		copyTwoStrings(first[i].thirdName, second[i].thirdName);
		copyTwoStrings(first[i].facultyNum, second[i].facultyNum);
		for (int j = 0; second[i].sub[j].grade != 0; j++)
		{
			copyTwoStrings(first[i].sub->name, second[i].sub->name);
			first[i].sub->grade = second[i].sub->grade;
		}
	}
}

void deleteFromFile(Student* stud, int group, char* facultyNum)//tva mi raboti samo za edna grupa
{
	string path = "";
	path = "Group_" + to_string(group) + ".txt";
	fstream currentDocument;
	currentDocument.open(path, ios::out | ios::in);
	isOpen(currentDocument);

	int counterForStudents = howManyStudentsInFile(stud);
	Student newArray[10]{};
	int index = 0;
	bool isTheFirstStudent = true;
	for (int i = 0; i < counterForStudents; i++)
	{
		if (areTheCharArraysTheSame(stud[i].facultyNum, facultyNum))
		{
			continue;
		}
		if (isTheFirstStudent)
		{
			newArray[index] = stud[i];
			index++;
			writeIntoFile(stud, i, group, false);
			isTheFirstStudent = false;

		}
		else
		{
			newArray[index] = stud[i];
			index++;
			writeIntoFile(stud, i, group);
		}
	}
	copyStructs(stud, newArray);
	currentDocument.close();
}

bool isTheFirstFacultyNumBigger(char* firstArr, char* secArr)
{
	int lengthFirst = numberOfLetters(firstArr);
	int lengthSecond = numberOfLetters(secArr);
	int biggerNum = returnBiggerNumber(lengthFirst, lengthSecond);
	for (int i = 0; i < biggerNum; i++)
	{
		if (firstArr[i] > secArr[i])
		{
			return true;
		}
		else if (firstArr[i] < secArr[i])
		{
			return false;
		}
	}
	return false;
}

void swapStudents(Student& stud1, Student& stud2)
{
	Student temp = stud1;
	stud1 = stud2;
	stud2 = temp;
}

//Tell whether it should open the file with ios::app or without
void whereToWrite(int numberOfStudentsInFile, bool isTheFirstStudent, int group, Student* stud)
{
	for (int j = 0; j < numberOfStudentsInFile; j++)
	{
		if (isTheFirstStudent)
		{
			writeIntoFile(stud, j, group, false);
			isTheFirstStudent = false;
		}
		else
		{
			writeIntoFile(stud, j, group);
		}
	}
}

void SortingStudents(bool ascending, int i, int numberStudents, Student* studentArr)
{
	for (int j = i + 1; j < numberStudents; j++)
	{
		if (ascending)
		{
			if (isTheFirstFacultyNumBigger(studentArr[i].facultyNum, studentArr[j].facultyNum))
			{
				swapStudents(studentArr[i], studentArr[j]);
			}
		}
		else
		{
			if (!isTheFirstFacultyNumBigger(studentArr[i].facultyNum, studentArr[j].facultyNum))
			{
				swapStudents(studentArr[i], studentArr[j]);
			}
		}

	}
}

void sortArraysFacultyNum(Student* stud, int group = 0, bool ascending = true)
{
	bool isTheFirstStudent = true;
	int numberOfStudentsInFile = howManyStudentsInFile(stud);
	for (int i = 0; i < numberOfStudentsInFile - 1; i++)
	{
		SortingStudents(ascending, i, numberOfStudentsInFile, stud);
	}
	whereToWrite(numberOfStudentsInFile, isTheFirstStudent, group, stud);
}

void putSomegroupsInOneFile(int* groupArr, int numberOfgroups)
{
	fstream combinedFile;
	fstream currentDocument;
	int index = 0;
	combinedFile.open("Sorted_Combined.txt", ios::out);
	for (int i = 0; i < numberOfgroups; i++)
	{
		string path = "";
		path = "Group_" + to_string(groupArr[i]) + ".txt";
		currentDocument.open(path, ios::in);
		isOpen(currentDocument);

		Student* document = getDocument(groupArr[i]);
		int numberOfStudents = howManyStudentsInFile(document);
		for (int i = 0; i < numberOfStudents; i++)
		{
			sortedStudents[index] = document[i];
			index++;
		}
	}
	combinedFile.close();
	currentDocument.close();
}

void sortMoregroupsFacultyNum(bool ascending = true)
{
	fstream combinedFile;
	combinedFile.open("Sorted_Combined.txt", ios::out);
	int index = 0;
	int totalNumberOfStudents = howManyStudentsInFile(sortedStudents);
	for (int i = 0; i < totalNumberOfStudents - 1; i++)
	{
		SortingStudents(ascending, i, totalNumberOfStudents, sortedStudents);
	}
	for (int i = 0; i < totalNumberOfStudents; i++)
	{
		directlyWritten(combinedFile, i, sortedStudents);
	}
	combinedFile.close();
}

double calculateAverageGrade(Student& students)
{
	double sumGrades = 0;
	int numberOfGrades = 0;
	for (int j = 0; students.sub[j].grade != 0; j++)
	{
		sumGrades += (students.sub[j].grade);
		numberOfGrades++;
	}
	return sumGrades / numberOfGrades;
}

void sortArraysAverageGrade(Student* stud, int group = 0, bool ascending = true)
{
	bool isTheFirstStudent = true;
	int numberOfStudentsInFile = howManyStudentsInFile(stud);
	for (int i = 0; i < numberOfStudentsInFile - 1; i++)
	{
		double averageGradeFirst = calculateAverageGrade(stud[i]);
		for (int j = i + 1; j < numberOfStudentsInFile; j++)
		{
			double averageGradeSecond = calculateAverageGrade(stud[j]);
			if (ascending)
			{
				if (isTheFirstBigger(averageGradeFirst, averageGradeSecond))
				{
					swapStudents(stud[i], stud[j]);
				}
			}
			else
			{
				if (!isTheFirstBigger(averageGradeFirst, averageGradeSecond))
				{
					swapStudents(stud[i], stud[j]);
				}
			}
		}
	}
	whereToWrite(numberOfStudentsInFile, isTheFirstStudent, group, stud);
}

void validationForGroup(char* groupChar, int& validatedInt)
{
	int lengthOfChar = numberOfLetters(groupChar);
	while ((groupChar[0] < '1' || groupChar[0] > '8') || lengthOfChar != 1)
	{
		cout << " The group must be between 1 and 8." << endl;
		cout << " Group: ";
		cin >> groupChar;
		cin.ignore();
		lengthOfChar = numberOfLetters(groupChar);
	}
	validatedInt = stoi(groupChar);
}

void validationForMethodAndCriteria(char* optionArr, int& option)
{
	int lengthOfArr = numberOfLetters(optionArr);
	option = atoi(optionArr);
	while ((option != 1 && option != 2) || lengthOfArr != 1)
	{
		cout << " The number must be 1 or 2. Try again! - ";
		cin >> optionArr;
		cin.ignore();
		lengthOfArr = numberOfLetters(optionArr);
		option = atoi(optionArr);
	}
}

void validateMenuOption(char* numberOfStudentsChar, int& numberOfStudentsInt)
{
	int lengthOfChar = numberOfLetters(numberOfStudentsChar);

	while (numberOfStudentsInt < 1 || lengthOfChar != 1)
	{
		cout << " How many students do you want to add? - ";
		cin >> numberOfStudentsChar;
		cin.ignore();
		numberOfStudentsInt = atoi(numberOfStudentsChar);
		lengthOfChar = numberOfLetters(numberOfStudentsChar);
	}
}

void SuccessfulExit()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	cout << " Successfully sorted!" << endl;
	Sleep(1000);
	system("cls");
}

void wayOfSorting(char* charArr, int& option1, int& option2)
{
	cout << " How do you want to sort it?" << endl;
	cout << " Option 1 - Faculty number" << endl;
	cout << " Option 2 - Average grade" << endl;
	cout << " ";
	cin.getline(charArr, CAPACITY * 5);
	validationForMethodAndCriteria(charArr, option1);
	cout << " In which order do you want to sort?" << endl;
	cout << " Option 1 - Ascending" << endl;
	cout << " Option 2 - Descending" << endl;
	cout << " ";
	cin.getline(charArr, CAPACITY * 5);
	validationForMethodAndCriteria(charArr, option2);
}

void optionsAG(int& optionFNorAG, int& optionAorD, Student* arrStudents, int validatedInt)
{
	if (optionFNorAG == 2 && optionAorD == 2)
	{
		sortArraysAverageGrade(arrStudents, validatedInt, false);
	}
	else if (optionFNorAG == 2 && optionAorD == 1)
	{
		sortArraysAverageGrade(arrStudents, validatedInt);
	}
}

void mainMenu()
{
	cout << " ========================================" << endl;
	cout << "              Choose an option           " << endl;
	cout << " ========================================" << endl;
	cout << " 1 - Enter Student Information" << endl;
	cout << " 2 - Delete student" << endl;
	cout << " 3 - Display a group of students" << endl;
	cout << " 4 - Sort a current group" << endl;
	cout << " 5 - Sort more than one groups" << endl;
	cout << " 6 - Exit" << endl;
	cout << " ========================================" << endl;
}

void validatingKey(int& key, char* validationChar)
{
	int lenghtOfKey = 0;
	while ((key < 1 || key > 6) || lenghtOfKey != 1)
	{
		cout << " The number must be between 1 and 6" << endl;
		cout << " ";
		cin.getline(validationChar, CAPACITY);
		lenghtOfKey = numberOfLetters(validationChar);
		key = atoi(validationChar);
	}
}

void SleepAndDelete()
{
	Sleep(1000);
	system("cls");
}

void InputStudentInformation(char* charValidation, Student* studentArr, int& numStud, int& validatedInt, string studOrder, int& numberOfSubjects)
{
	validateMenuOption(charValidation, numStud);
	cout << endl;
	for (int i = 0; i < numStud; i++)
	{
		studOrder = " Student " + to_string(i + 1) + ":";
		cout << studOrder << endl;
		cout << endl;
		cout << " Group: ";
		cin.getline(charValidation, CAPACITY);
		validationForGroup(charValidation, validatedInt);
		studentArr = getDocument(validatedInt);
		int totalStudentsInFile = howManyStudentsInFile(studentArr);
		inputStud(studentArr, totalStudentsInFile, validatedInt, numberOfSubjects);
		writeIntoFile(studentArr, totalStudentsInFile, validatedInt, numberOfSubjects);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	cout << " Students added successfully!" << endl;
	SleepAndDelete();
}

void DeleteStudent(char* CharArrForValidation, int& validatedInt, Student* arrStudents)
{
	cout << " From which group do you want to remove the student? - ";
	cin.getline(CharArrForValidation, CAPACITY);
	validationForGroup(CharArrForValidation, validatedInt);
	arrStudents = getDocument(validatedInt);
	cout << " Faculty number: ";
	cin.getline(CharArrForValidation, MAX_SIZE);
	deleteFromFile(arrStudents, validatedInt, CharArrForValidation);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	cout << " The student is deleted successfully!";
	SleepAndDelete();

}

void DisplayGroup(char* CharArrForValidation, int& validatedInt)
{
	cout << " Which group do you want to see? - ";
	cin.getline(CharArrForValidation, CAPACITY);
	validationForGroup(CharArrForValidation, validatedInt);
	readFromFile(validatedInt);
	cout << " ";
	system("pause");
	system("cls");
}

void SortOneGroup(char* CharArrForValidation, int& validatedInt, int& optionFNorAG, int& optionAorD, Student* arrStudents)
{
	cout << " Which group do you want to sort? - ";
	cin.getline(CharArrForValidation, CAPACITY);
	validationForGroup(CharArrForValidation, validatedInt);
	wayOfSorting(CharArrForValidation, optionFNorAG, optionAorD);
	arrStudents = getDocument(validatedInt);
	optionsAG(optionFNorAG, optionAorD, arrStudents, validatedInt);
	if (optionFNorAG == 1 && optionAorD == 1)
	{
		sortArraysFacultyNum(arrStudents, validatedInt);

	}
	else if (optionFNorAG == 1 && optionAorD == 2)
	{
		sortArraysFacultyNum(arrStudents, validatedInt, false);
	}
	SuccessfulExit();
}

void SortSeveralGroups(char* CharArrForValidation, int& validatedInt, int* arrayWithgroups, int& optionFNorAG, int& optionAorD)
{
	cout << " How many groups do you want to sort? - ";
	cin.getline(CharArrForValidation, CAPACITY);
	validationForGroup(CharArrForValidation, validatedInt);
	for (int i = 0; i < validatedInt; i++)
	{
		cout << " Group: ";
		cin.getline(CharArrForValidation, CAPACITY);
		validationForGroup(CharArrForValidation, arrayWithgroups[i]);
	}
	putSomegroupsInOneFile(arrayWithgroups, validatedInt);
	wayOfSorting(CharArrForValidation, optionFNorAG, optionAorD);
	optionsAG(optionFNorAG, optionAorD, sortedStudents, 0);
	if (optionFNorAG == 1 && optionAorD == 1)
	{
		sortMoregroupsFacultyNum();
	}
	else if (optionFNorAG == 1 && optionAorD == 2)
	{
		sortMoregroupsFacultyNum(false);
	}
	readFromFile();
	cout << " ";
	system("pause");
	system("cls");
}

void ExitTheProgram()
{
	system("cls");
	cout << endl;
	cout << " Thank you for using our platform!";
	cout << endl;
	Sleep(2000);
	exit(0);
}

int main()
{
	saveTheDataToEverygroup();
	int key = 0;
	char keyChar[MAX_CAPACITY]{};
	char CharArrForValidation[MAX_CAPACITY]{};
	int numberOfStudentsInt = 0, numberOfSubjects = 0;
	Student* arrStudents = {};
	int optionFNorAG = 0, optionAorD = 0, validatedInt = 0;
	string numberStud = "";
	int arrayWithgroups[MAX_CAPACITY]{};

	while (key != 6)
	{
		system("Color 07");
		fillArrayWithZeros(CharArrForValidation);
		mainMenu();
		validatingKey(key, CharArrForValidation);

		switch (key)
		{
		case 1:
			InputStudentInformation(CharArrForValidation, arrStudents, numberOfStudentsInt, validatedInt, numberStud, numberOfSubjects);
			break;
		case 2:
			DeleteStudent(CharArrForValidation, validatedInt, arrStudents);
			break;
		case 3:
			DisplayGroup(CharArrForValidation, validatedInt);
			break;
		case 4:
			SortOneGroup(CharArrForValidation, validatedInt, optionFNorAG, optionAorD, arrStudents);
			break;
		case 5:
			SortSeveralGroups(CharArrForValidation, validatedInt, arrayWithgroups, optionFNorAG, optionAorD);
			break;

		case 6:
			ExitTheProgram();
			break;
		default:
			break;
		}
	}
}
