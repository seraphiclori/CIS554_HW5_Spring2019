#pragma once

//HW5 Due: April 7 (Sunday) at 11:59PM
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class node {
public:
	shared_ptr<node> east;
	shared_ptr<node> south;
	int value;
	node() {}
	node(int i) { value = i; }
};

class ring {
public:
	//Implement all functions described below
	//funciton operator[] can be invoked by other functions
	shared_ptr<node> head;
	int num_rows;
	int num_cols;
	ring(){}
	ring(int i, int j, bool flag);
	ring(vector<int> &V, int i, int j);
	ring(int i, int j);//constructor
					   //i rows and j cols
					   //values from 0 to i*j-1
	~ring();//destructor; do as little work as possible
	ring(const ring &r); //copy constructor
	ring(ring &&r); //move constructor
	void operator=(ring &&r);//R-value operator=
	void operator=(const ring &r); //L-value operator=
	ring(const initializer_list<int> &V);//see the explanation in main function
	int & operator[](int a);
	int & operator[](pair<int, int> p); //first is row number and second is col number
	void DelCol(int i);//delete col i of *this
	ring Threetimes();
	//return a ring with the same dimenstion as *this, and the value of every node is three times of that of *this.
};


///////////////////////////////////////////////////////////////////////////////////
//ring::ring(int i, int j) :ring() {
//	if (i <= 0 || j <= 0)
//		return;
//	num_rows = i;
//	num_cols = j;
//	int value = 0;
//	shared_ptr<node> tail, pre_row;
//	pre_row = nullptr;
//	for (int tmp_i = 0; tmp_i < i; ++tmp_i) {
//		for (int tmp_j = 0; tmp_j < j; ++tmp_j) {
//			shared_ptr<node> p = make_shared<node>(value);
//			if (!head) { head = tail = p; tail->east = p; }
//			else {
//				tail->east = p;
//				tail = p;
//				tail->east = head;
//			}
//			if (pre_row) {
//				pre_row->south = p;
//				pre_row = pre_row->east;
//			}
//			value++;
//		}
//		if (!pre_row) {
//			pre_row = head;
//		}
//	}
//	shared_ptr<node> h = head;
//	while (j - 1) {
//		pre_row->south = h->east;
//		pre_row = pre_row->east;
//		h = h->east;
//		--j;
//	}
//	pre_row->south = head;
//	h = nullptr;
//	pre_row = nullptr;
//	tail = nullptr;
//}
//ring::~ring() {
//	if (head == nullptr)
//		return;
//	int i = num_cols;
//	shared_ptr<node> tmp = head;
//	shared_ptr<node> tail = head;
//	while (i && tail) {
//		tmp = tail;
//		tail = tail->east;
//		tmp->east.reset();
//		tmp->south.reset();
//		i--;
//	}
//	tmp.reset();
//	tail.reset();
//}
//ring::ring(const ring&r) :ring() {
//	num_rows = r.num_rows;
//	num_cols = r.num_cols;
//	int num = num_rows * num_cols;
//	shared_ptr<node> tail, pre_row;
//	shared_ptr<node> tmp = r.head;
//	for (int tmp_i = 0; tmp_i < num_rows; ++tmp_i) {
//		for (int tmp_j = 0; tmp_j < num_cols; ++tmp_j) {
//			shared_ptr<node> p = make_shared<node>(tmp->value);
//			tmp = tmp->east;
//			if (!head) { head = tail = p; tail->east = head; }
//			else {
//				tail->east = p;
//				tail = p;
//				tail->east = head;
//			}
//			if (pre_row) {
//				pre_row->south = p;
//				pre_row = pre_row->east;
//			}
//		}
//		if (!pre_row) {
//			pre_row = head;
//		}
//	}
//	shared_ptr<node> h = head;
//	int i = num_cols;
//	while (i - 1) {
//		pre_row->south = h->east;
//		pre_row = pre_row->east;
//		h = h->east;
//		--i;
//	}
//	pre_row->south = head;
//	h = nullptr;
//	pre_row = nullptr;
//	tail = nullptr;
//}
//void ring::operator=(const ring &r) {
//	int i = num_cols;
//	shared_ptr<node> tmp1 = head;
//	shared_ptr<node> tmp2 = head;
//	while (i && tmp1) {
//		tmp2 = tmp1;
//		tmp1 = tmp1->east;
//		tmp2->east.reset();
//		tmp2->south.reset();
//		i--;
//	}
//	tmp1.reset();
//	tmp2.reset();
//	head = nullptr;
//	num_rows = r.num_rows;
//	num_cols = r.num_cols;
//	int num = num_rows * num_cols;
//	shared_ptr<node> tail, pre_row;
//	shared_ptr<node> tmp = r.head;
//	for (int tmp_i = 0; tmp_i < num_rows; ++tmp_i) {
//		for (int tmp_j = 0; tmp_j < num_cols; ++tmp_j) {
//			shared_ptr<node> p = make_shared<node>(tmp->value);
//			tmp = tmp->east;
//			if (!head) { head = tail = p; tail->east = head; }
//			else {
//				tail->east = p;
//				tail = p;
//				tail->east = head;
//			}
//			if (pre_row) {
//				pre_row->south = p;
//				pre_row = pre_row->east;
//			}
//		}
//		if (!pre_row) {
//			pre_row = head;
//		}
//	}
//	shared_ptr<node> h = head;
//	int t = num_cols;
//	while (t - 1) {
//		pre_row->south = h->east;
//		pre_row = pre_row->east;
//		h = h->east;
//		--t;
//	}
//	pre_row->south = head;
//}
//ring::ring(const initializer_list<int> &V) :ring() {
//
//	auto itr = V.begin();
//	num_rows = *itr;
//	itr++;
//	num_cols = *itr;
//	itr++;
//	shared_ptr<node> tail, pre_row;
//	for (int tmp_i = 0; tmp_i < num_rows; ++tmp_i) {
//		for (int tmp_j = 0; tmp_j < num_cols; ++tmp_j) {
//			shared_ptr<node> p;
//			if (itr != V.end()) {
//				p = make_shared<node>(*itr);
//				itr++;
//			}
//			else {
//				p = make_shared<node>(1);
//			}
//			if (!head) { head = tail = p; tail->east = head; }
//			else {
//				tail->east = p;
//				tail = p;
//				tail->east = head;
//			}
//			if (pre_row) {
//				pre_row->south = p;
//				pre_row = pre_row->east;
//			}
//		}
//		if (!pre_row) {
//			pre_row = head;
//		}
//	}
//	shared_ptr<node> h = head;
//	int i = num_cols;
//	while (i - 1) {
//		pre_row->south = h->east;
//		pre_row = pre_row->east;
//		h = h->east;
//		--i;
//	}
//	pre_row->south = head;
//	h = nullptr;
//	pre_row = nullptr;
//	tail = nullptr;
//}
//int & ring:: operator[](int a) {
//	shared_ptr<node> tmp = head;
//	if (a >= 0) {
//		for (int i = 0; i < a; ++i) {
//			tmp = tmp->east;
//		}
//		return tmp->value;
//	}
//	return tmp->value;
//}
//int & ring ::operator[](pair<int, int> p) {
//	int r = p.first;
//	int c = p.second;
//	shared_ptr<node> tmp = head;
//	if (r >= 0 && r < num_rows && c >= 0 && c < num_cols) {
//		for (int i = 0; i < r; ++i) {
//			tmp = tmp->south;
//		}
//		for (int i = 0; i < c; ++i) {
//			tmp = tmp->east;
//		}
//		return tmp->value;
//	}
//	return tmp->value;
//}
//void ring::DelCol(int i) {
//	if (head == nullptr)
//		return;
//	if (num_cols == 1 && i == 0) {
//		head->east.reset();
//		head->south.reset();
//		head.reset();
//		num_cols = num_cols - 1;
//		num_rows = 0;
//		return;
//	}
//	else if (i >= 0 && i < num_cols) {
//		shared_ptr<node> pre, current;
//		pre = head;
//		current = head->east;
//		if (current == head->south) current = head;
//		if (i == 0) i = num_cols;
//		for (int j = 1; j < i; ++j) {
//			pre = pre->east;
//			current = current->east;
//
//		}
//		if (i == num_cols) head = head->east;
//		shared_ptr<node> current_head = head;
//		for (int j = 0; j < num_rows; ++j) {
//			pre->east = pre->east->east;
//			if (j == num_rows - 1) {
//				pre->south = current_head;
//			}
//			pre = pre->south;
//
//		}
//		num_cols = num_cols - 1;
//	}
//	if (num_cols == 0) { num_rows = 0; }
//
//}
//
//ring ring::Threetimes() {
//	int num = num_rows * num_cols;
//	ring result;
//	result.num_cols = num_cols;
//	result.num_rows = num_rows;
//	shared_ptr<node> tail, pre_row;
//	shared_ptr<node> tmp = head;
//	for (int tmp_i = 0; tmp_i < num_rows; ++tmp_i) {
//		for (int tmp_j = 0; tmp_j < num_cols; ++tmp_j) {
//			shared_ptr<node> p = make_shared<node>(tmp->value * 3);
//			tmp = tmp->east;
//			if (!result.head) { result.head = tail = p; tail->east = head; }
//			else {
//				tail->east = p;
//				tail = p;
//				tail->east = result.head;
//			}
//			if (pre_row) {
//				pre_row->south = p;
//				pre_row = pre_row->east;
//			}
//		}
//		if (!pre_row) {
//			pre_row = result.head;
//		}
//	}
//	shared_ptr<node> h = result.head;
//	int i = result.num_rows;
//	while (i - 1) {
//		pre_row->south = h->east;
//		pre_row = pre_row->east;
//		h = h->east;
//		--i;
//	}
//	pre_row->south = result.head;
//	return result;
//}
//ring::ring(ring &&r) {
//	int i = num_cols;
//	shared_ptr<node> tmp1 = head;
//	shared_ptr<node> tmp2 = head;
//	while (i && tmp1) {
//		tmp2 = tmp1;
//		tmp1 = tmp1->east;
//		tmp2->east.reset();
//		tmp2->south.reset();
//		i--;
//	}
//	tmp1.reset();
//	tmp2.reset();
//	head = nullptr;
//	head = r.head;
//	num_rows = r.num_rows;
//	num_cols = r.num_cols;
//	r.head = nullptr;
//}
//void ring::operator=(ring &&r) {
//	int i = num_cols;
//	shared_ptr<node> tmp1 = head;
//	shared_ptr<node> tmp2 = head;
//	while (i && tmp1) {
//		tmp2 = tmp1;
//		tmp1 = tmp1->east;
//		tmp2->east.reset();
//		tmp2->south.reset();
//		i--;
//	}
//	tmp1.reset();
//	tmp2.reset();
//	head = nullptr;
//	head = r.head;
//	num_rows = r.num_rows;
//	num_cols = r.num_cols;
//	r.head = nullptr;
//}


