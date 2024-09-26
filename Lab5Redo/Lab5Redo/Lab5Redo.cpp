// CS201L-Lab5-Pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "functions.h"
#include <vector>

int main()
{
    vector<studentInfo*> studentsData;
    cout << "CS201l-LAB5: GRADING PROGRAM USING POINTERS\n";
    setStudentInfo(studentsData);
    printStudentData(studentsData);
}

