#include "pch.h"
#include "../Tester/HW5.h"
#include "Marks.h"
#include <vector>

int amount = 0;

void* operator new(std::size_t sz) {
	amount++;
	return std::malloc(sz);
}

void operator delete(void* ptr) noexcept {
	amount--;
	std::free(ptr);
	ptr = nullptr;
}

bool checkByRow(ring& r, std::vector<int>& v)
{
	shared_ptr<node> p = r.head;
	for (int i : v)
	{
		if (!p)
			return false;
		if (p->value != i)
			return false;
		p = p->east;
	}
	return p == r.head;
}

bool checkByColumn(ring& r, int i,int j)
{
	shared_ptr<node> slow = r.head;
	shared_ptr<node> fast = slow;
	for (int x = 0; x < j; x++)
		fast = fast->east;
	int index = 0;
	while (index < i*j - 1)
	{
		if (fast == r.head)
			fast = fast->east;
		if (slow->south != fast)
			return false;
		slow = slow->east;
		fast = fast->east;
		index++;
	}
	return slow->south == r.head;
}

TEST(TestConstructor, normal) {
	ring testRing(3,5);
	std::string errorMsg = "Constructor Failed";
	int mark = 5;
	std::vector<int> v1;
	for (int i = 0; i < 15; i++)
		v1.push_back(i);
	ASSERT_TRUE(checkByRow(testRing,v1) && checkByColumn(testRing, 3, 5)) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
	errorMsg = "Check the ring by Column Failed";
	mark = 1;
	errorMsg = "Construct Ring with one element Failed";
	ring oneEleRing(1, 1);
	ASSERT_TRUE(oneEleRing.head->east == oneEleRing.head && oneEleRing.head-> south== oneEleRing.head) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(TestConstructor, initialier_list)
{
	ring testRing = { 3, 3, 10,20,30,40,50, 60,70,80,90 };
	std::string errorMsg = "Constructed by initializer list failed";
	std::vector<int> v1 = { 10,20,30,40,50, 60,70,80,90 };
	int mark = 4;
	ASSERT_TRUE(checkByRow(testRing,v1) && checkByColumn(testRing,3,3)) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}


TEST(TestCopyConstructor, copy_constructor)
{
	std::vector<int> v = { -10,20,-30,40 };
	ring oriRing(v, 2, 2);
	ring copyRing(oriRing);
	std::string errorMsg = "Copy constructor failed";
	int mark = 2;
	ASSERT_TRUE(checkByRow(copyRing,v) && checkByColumn(copyRing,2,2) && oriRing.head != copyRing.head) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(TestLdata, L_Value_operator)
{
	amount = 0;
	ring testRing1(2,2,true);
	vector<int> v = { 10,20,30,40};
	ring testRing2(v, 2, 2);
	int before = amount;
	testRing1 = testRing2;
	int after = amount;
	std::string errorMsg = "L Value operator = failed";
	int mark = 4;
	ASSERT_TRUE(checkByRow(testRing1, v) && checkByColumn(testRing1, 2, 2) && testRing1.head != testRing2.head) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
	errorMsg = "L Value operator= Memory leak";
	mark = 1;
	ASSERT_TRUE(after - before == 0) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(TestMoveConstructor, move_constructor)
{
	std::vector<int> v = { -1,2,-3,4 };
	ring origRing = ring(v, 2, 2);
	shared_ptr<node> p = origRing.head;
	ring testRing(std::move(origRing));
	std::string errorMsg = "Move constructor failed";
	int mark = 3;
	ASSERT_TRUE(checkByRow(testRing, v) && checkByColumn(testRing, 2, 2) && p == testRing.head) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(TestRdata, R_Value_operator)
{
	std::vector<int> v = { -1,2,-3,4 };
	amount = 0;
	ring origRing = ring(v, 2, 2);
	int before = amount;
	ring testRing(2, 2);
	shared_ptr<node> p = origRing.head;
	testRing = move(origRing);
	int after = amount;
	std::string errorMsg = "R Value operator = failed";
	int mark = 3;
	ASSERT_TRUE(checkByRow(testRing, v) && checkByColumn(testRing, 2, 2) && p == testRing.head) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
	errorMsg = "R Value operator= Memory leak";
	mark = 1;
	ASSERT_TRUE(after - before == 0) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(TestIndex, normal)
{
	ring testRing(std::vector<int>({ 10,20,30,40,50, 60,70,80,90 }), 3, 3);
	std::string errorMsg = "Accessed by one index failed";
	int mark = 3;
	EXPECT_TRUE(testRing[3] == 40 && testRing[8] == 90) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
	errorMsg = "Accessed by row and column index failed";
	EXPECT_TRUE((testRing[{0, 0}] == 10) && (testRing[{2, 1}] == 80)) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(Threetimes, normal)
{
	ring testRing(2,2,true);
	std::vector<int> v = { 0,3,6,9};
	std::string errorMsg = "Three Times failed";
	int mark = 2;
	ring threeTime = testRing.Threetimes();
	shared_ptr<node> p = testRing.head;
	EXPECT_TRUE(checkByRow(threeTime, v) && checkByColumn(threeTime, 2, 2) && testRing.head != threeTime.head) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(DelCol, first_line)
{
	std::vector<int> v = {1,2,4,5,7,8 };
	amount = 0;
	ring testRing = ring(3, 3,true);
	int before = amount;
	testRing.DelCol(0);
	int after = amount;
	std::string errorMsg = "Delete first column failed";
	int mark = 2;
	ASSERT_TRUE(checkByRow(testRing, v) && checkByColumn(testRing, 3, 2) && testRing.num_cols == 2 && testRing.num_rows==3) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
	errorMsg = "Delete first column: Memory leak";
	mark = 1;
	ASSERT_TRUE(before - after == 3) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(DelCol, last_line)
{
	std::vector<int> v = { 0,1,3,4,6,7 };
	amount = 0;
	ring testRing = ring(3, 3, true);
	int before = amount;
	testRing.DelCol(2);
	int after = amount;
	std::string errorMsg = "Delete last column failed";
	int mark = 2;
	ASSERT_TRUE(checkByRow(testRing, v) && checkByColumn(testRing, 3, 2) && testRing.num_cols == 2 && testRing.num_rows == 3) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
	errorMsg = "Delete last column: Memory leak";
	mark = 1;
	ASSERT_TRUE(before - after == 3) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(DelCol, mid_line)
{
	std::vector<int> v = { 0,2,3,5,6,8 };
	amount = 0;
	ring testRing = ring(3, 3, true);
	int before = amount;
	testRing.DelCol(1);
	int after = amount;
	std::string errorMsg = "Delete midium column failed";
	int mark = 2;
	ASSERT_TRUE(checkByRow(testRing, v) && checkByColumn(testRing, 3, 2) && testRing.num_cols == 2 && testRing.num_rows == 3) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
	errorMsg = "Delete midium column: Memory leak";
	mark = 1;
	ASSERT_TRUE(before - after == 3) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(DelCol, oneColRing)
{
	amount = 0;
	ring testRing = ring(3, 1, true);
	int before = amount;
	testRing.DelCol(0);
	int after = amount;
	std::string errorMsg = "Delete one column ring failed";
	int mark = 2;
	ASSERT_TRUE(!testRing.head && testRing.num_cols == 0 && testRing.num_rows == 0) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
	errorMsg = "Delete one column ring: Memory leak";
	mark = 1;
	ASSERT_TRUE(before - after == 3) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}

TEST(Destructor, normal)
{
	amount = 0;
	{
		ring testRing = ring(5,5, true);
	}
	int result = amount;
	int mark = 3;
	std::string errorMsg = "Destructor a ring: Memory leak";
	ASSERT_TRUE(result == 0) << errorMsg << Marks::deductMark(mark)
		<< Marks::gatherErrorInfo(errorMsg, mark);
}