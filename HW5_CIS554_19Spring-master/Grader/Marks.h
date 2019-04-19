#pragma once
//////////////////////////////////////////////////////////////
// CIS 554 Grading for HW1                                  //
// Spring 2019                                              //
// Cheng Wang - cwang76@syr.edu                             //
//////////////////////////////////////////////////////////////

#pragma once
#include "pch.h"

class Marks {
public:
	static int marks;
	static std::string errorInfo;
	static std::string deductMark(int num) {
		std::string result = "\n Deduct " + std::to_string(num) + " marks... \n";
		std::cout << "\x1B[36m" + result + "\033[0m\t";
		marks -= num;
		return "";
	}

	static std::string gatherErrorInfo(std::string error, int marks) {
		errorInfo = errorInfo + "> " + error + " -" + std::to_string(marks) + "\n";
		return "";
	}
};

