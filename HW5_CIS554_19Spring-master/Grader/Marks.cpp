#include "pch.h"
#include "Marks.h"

int Marks::marks = 40;
std::string Marks::errorInfo = "\n";

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();

	std::string finalMark = "\n The Final Mark is " + std::to_string(Marks::marks);

	std::cout << "\x1B[36m" + finalMark + "\033[0m\t";

	std::cout << Marks::errorInfo;

	getchar();
	getchar();
	return result;
}