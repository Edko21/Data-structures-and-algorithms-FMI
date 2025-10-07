#pragma once
#include <string>

struct Student {
	std::string name;
	int grade;
};

void countSortGrades(Student* arr, size_t len) {
	const size_t GRADES_VALUES_COUNT = 5;

	size_t* countArr = new size_t[GRADES_VALUES_COUNT]{ 0 }; 

	for (int i = 0; i < len; i++)
		countArr[arr[i].grade - 2]++;

	for (int i = 1; i < GRADES_VALUES_COUNT; i++)
		countArr[i] += countArr[i - 1];

	Student* result = new Student[len];
	for (int i = len - 1; i >= 0; i--)
	{
		Student& currentStudent = arr[i];
		size_t index = --countArr[currentStudent.grade - 2];
		result[index] = currentStudent;
	}

	for (int i = 0; i < len; i++)
		arr[i] = result[i];
	delete[] result;
	delete[] countArr;
}
