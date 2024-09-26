//header 
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
struct classData {
	int A=0;
	int B = 0;
	int C = 0;
	int D = 0;
	int F = 0;
	float avg=0.0f;
};
struct studentInfo {
	int studentID;
	string answers;
	int score;
	float percent;
	char grade;
};
void setStudentInfo(vector<studentInfo*>& studentData);
void printStudentData(vector<studentInfo*>& studentData);