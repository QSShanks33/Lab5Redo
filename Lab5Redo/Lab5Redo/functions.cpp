#include "functions.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool isDigits(string str) {
	return (str.find_first_not_of("0123456789") == string::npos);
}

bool isValidAnswer(string str) {
	return str.find_first_not_of("ABCDE ") == str.npos;
}
int GetScore(string ans, string guess) {
	int p = 0;
		for (int i = 0; i < guess.size(); i++) {
			if (ans[i] == guess[i]) {
				p += 2;
			}
			else if (guess[i] != ' ') {
				p++;
			}
		}
	
	return p;
}
//borrowed chat:gpt
char getGrade(double x) {
	if (x >= 90 && x <= 100) {
		return 'A';
	}
	else if (x >= 80 && x < 90) {
		return 'B';
	}
	else if (x >= 70 && x < 80) {
		return 'C';
	}
	else if (x >= 60 && x < 70) {
		return 'D';
	}
	else {
		return 'F';
	}
}
void setStudentInfo(vector<studentInfo*> &studentData) {
	ifstream InputFile("student.txt");
	ofstream errFile("Errors.txt");
	classData CLASS_DATA;

	if (InputFile.is_open()) {
		cout << "\nopenned";

		string line;
		//Get correct answers first
		string correct_ans; InputFile >> correct_ans; getline(InputFile, line);
		//Iterate for each student in file
		while (getline(InputFile, line)) {
			//create a new location each iteration for storing a student.
			studentInfo *student = new studentInfo;

			istringstream s(line);
			//Read data in from each line as a string. id is read as a string and answers are read as string.
			string id, student_ans;

			s >> id; s >> student_ans;
			id = line.substr(0, 6);
			student_ans = line.substr(7, 20);

			//if ID is a digit and answers are only ABCD...
			if (isDigits(id) && isValidAnswer(student_ans)) {
				student->studentID = stoi(id);
				student->answers = student_ans;

				student->score= GetScore(correct_ans, student_ans);
				student->percent=student->score / static_cast<float>(40) * 100;

				student->grade=getGrade(student->percent);
				switch (student->grade) {
				case 'A':
					CLASS_DATA.A++;
					break;
				case 'B':
					CLASS_DATA.B++;
					break;
				case 'C':
					CLASS_DATA.C++;
					break;
				case 'D':
					CLASS_DATA.D++;
					break;
				case 'F':
					CLASS_DATA.F++;
					break;
				}
				CLASS_DATA.avg += student->percent;
				studentData.push_back(student);

				//now add data to class data
				

			}
			else {
				if (!isDigits(id)) {
					errFile << "Error in Student ID:    " << id << " " << student_ans << endl;
				}
				else {
					errFile << "Error in Answer    :    " << id << " " << student_ans << endl;
				}
			}
		}
		cout << "CLASS AVERAGE = " << fixed<< setprecision(2)<<CLASS_DATA.avg / studentData.size()<<endl;
		cout << endl << "GRADE TOTALS:\n"; cout << "A" << setw(5) << right <<CLASS_DATA.A <<endl;
		cout << "B" << setw(5) << right << CLASS_DATA.B << endl;
		cout << "C" << setw(5) << right << CLASS_DATA.C << endl;
		cout << "D" << setw(5) << right << CLASS_DATA.D << endl;
		cout << "F" << setw(5) << right << CLASS_DATA.F << endl;

	}
	else {
		cout << "unsuccesful";
		errFile << "File was not oppened";
	}
	InputFile.close();
	errFile.close();
}
void printStudentData(vector<studentInfo*> &studentData) {
	ofstream rep("report.txt");
	rep << "STUD ID    STUDENT ANSWERS        SCORE/40     PERCENT       GRADE\n";
	for (studentInfo* s:studentData) {
		rep << s->studentID << "   " << s->answers << "      " << s->score << "     ";
		rep << setw(10) << right<< s->percent << "     " << setw(10)<<right<<s->grade << endl;
	}
	
}

