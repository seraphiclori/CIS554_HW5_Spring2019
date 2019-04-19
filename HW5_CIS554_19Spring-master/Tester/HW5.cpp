//HW5 Due: April 7 (Sunday) at 11:59PM
// Xiao Xiong 
// NetID: xxiong02  
// SUID: 207923300
#include <iostream>
#include "pch.h"
#include "HW5.h"

ring::ring(int i, int j, bool flag) 
{
	num_rows = i;
	num_cols = j;
	if (i <= 0 || j <= 0)
		return;
	head = make_shared<node>(node(0));
	int index = 1;
	shared_ptr<node> p = head;
	while (index < i*j)
	{
		p->east = make_shared<node>(node(index++));
		p = p->east;
	}
	p->east = head;
	p = head;
	shared_ptr<node> fast = head;
	for (int x = 0; x < j; x++)
		fast = fast->east;
	index = 0;
	while (index < i*j-1)
	{
		if (fast == head)
			fast = fast->east;
		p->south = fast;
		p = p->east;
		fast = fast->east;
		index++;
	}
	p->south = head;
}

ring::ring(vector<int> &V, int i, int j) :ring(i,j)
{
	shared_ptr<node> p = head;
	auto it = V.begin();
	while (it != V.end())
	{
		p->value = *it;
		it++;
		p = p->east;
	}
}


/////////////////////////////////////////////////////////////////////
// Student's Solution

ring::ring(int i, int j) {
	num_rows = i;
	num_cols = j;
	if (i > 0 && j > 0) {
		//constructing nodes and horizental links
		int col = 0, row = 0, val =0;
		shared_ptr<node> left, up, right, ptr, ptr2;
		for (col = 0; col < i*j; col++) {
			ptr = make_shared<node>(*(new node(val++)));
			if (col == 0) {
				left = ptr;
				head = ptr;
			}
			else {
				left->east = ptr;
				left = ptr;
			}
		}
		left->east = head;
		left->south = head;
		// constructing the vertical links
		up = head;
		ptr2 = head;
		for (col = 0; col < j; col++)  ptr2 = ptr2->east;
		for (row = 1; row < i; row++) {	
			for (col = 0; col < j; col++) {
				up->south = ptr2;
				if (row != i - 1 || col != j - 1) ptr2 = ptr2->east;
				up = up->east;
			}
		}		
		// link last row to the first row vertically 
		for (int col = 1; col < j; col++) {
			right = head->east;
			up->south = right;
			right = right->east;
			up = up->east;
		}
	}
}
ring::~ring() {
	if (num_cols > 0 && num_rows > 0) {
		if (num_cols == 1 || num_rows == 1) {
			head->east.reset();
			head->south.reset();
			head.reset();
		}
		else {
			shared_ptr<node> tmp;
			if (num_rows > num_cols) {
				tmp = head->east;
				for (int i = 0; i < num_cols; i++) {
					head->east.reset();
					head->south.reset();
					head = tmp;
					tmp = tmp->east;
				}
			}
			else {
				tmp = head->south;
				for (int i = 0; i < num_rows; i++) {
					head->east.reset();
					head->south.reset();
					head = tmp;
					tmp = tmp->south;
				}
			}
			if(!tmp) tmp.reset();
			head.reset();
		}
	}
}
ring::ring(const ring &r) : ring(){
	num_rows = r.num_rows;
	num_cols = r.num_cols;
	if (num_rows > 0 && num_cols > 0) {
		//constructing nodes and horizental links
		int col = 0, row = 0, val = 0;
		shared_ptr<node> left, up, right, ptr, ptr2, tmp = r.head;
		for (col = 0; col < num_rows * num_cols; col++) {
			ptr = make_shared<node>(*(new node(tmp->value)));
			if (col == 0) {
				left = ptr;
				head = ptr;
			}
			else {
				left->east = ptr;
				left = ptr;
			}
			tmp = tmp->east;
		}
		left->east = head;
		left->south = head;
		//constructing the vertical links
		up = head;
		ptr2 = head;
		for (col = 0; col < num_cols; col++)  ptr2 = ptr2->east;
		for (row = 1; row < num_rows; row++) {
			for (col = 0; col < num_cols; col++) {
				up->south = ptr2;
				 
				if (row != num_rows - 1 || col != num_cols - 1) ptr2 = ptr2->east;
				up = up->east;
			}
		}
		// link last row to the first row vertically
		for (int col = 1; col < num_cols; col++) {
			right = head->east;
			up->south = right;
			right = right->east;
			up = up->east;
		}
	}
}
ring::ring(ring &&r) : ring() {
	num_rows = r.num_rows;
	num_cols = r.num_cols;
	head = r.head;
	r.num_rows = 0;
	r.num_cols = 0;
	r.head.reset();
}
void ring::operator=(ring &&r) {
	num_rows = r.num_rows;
	num_cols = r.num_cols;
	head = r.head;
	r.num_rows = 0;
	r.num_cols = 0;
	r.head.reset();
}
void ring::operator=(const ring &r) { 
	num_rows = r.num_rows;
	num_cols = r.num_cols;
	if (num_rows > 0 && num_cols > 0) {
		//constructing nodes and horizental links
		int col = 0, row = 0, val = 0;
		shared_ptr<node> left, up, right, ptr, ptr2, tmp = r.head;
		for (col = 0; col < num_rows * num_cols; col++) {
			ptr = make_shared<node>(*(new node(tmp->value)));
			if (col == 0) {
				left = ptr;
				head = ptr;
			}
			else {
				left->east = ptr;
				left = ptr;
			}
			tmp = tmp->east;
		}
		left->east = head;
		left->south = head;
		//constructing the vertical links
		up = head;
		ptr2 = head;
		for (col = 0; col < num_cols; col++)  ptr2 = ptr2->east;
		for (row = 1; row < num_rows; row++) {
			for (col = 0; col < num_cols; col++) {
				up->south = ptr2;

				if (row != num_rows - 1 || col != num_cols - 1) ptr2 = ptr2->east;
				up = up->east;
			}
		}
		// link last row to the first row vertically
		for (int col = 1; col < num_cols; col++) {
			right = head->east;
			up->south = right;
			right = right->east;
			up = up->east;
		}
	}
}
ring::ring(const initializer_list<int> &V):ring() {
	auto it = V.begin();
	if (it != V.end()) num_rows = *it;
	it++;
	if (it != V.end()) num_cols = *it;
	it++;
	// constructing the ring
	if (num_rows > 0 && num_cols > 0) {

		int col = 0, row = 0, val = 0;
		shared_ptr<node> left, up, right, ptr, ptr2;
		for (col = 0; col < num_rows *num_cols; col++) {
			ptr = make_shared<node>(*(new node(val++)));
			if (col == 0) {
				left = ptr;
				head = ptr;
			}
			else {
				left->east = ptr;
				left = ptr;
			}
		}
		left->east = head;
		left->south = head;

		up = head;
		ptr2 = head;
		for (col = 0; col < num_cols; col++)  ptr2 = ptr2->east;
		for (row = 1; row < num_rows; row++) {
			for (col = 0; col < num_cols; col++) {
				up->south = ptr2;
				if (row != num_rows - 1 || col != num_cols - 1) ptr2 = ptr2->east;
				up = up->east;
			}
		}

		for (int col = 1; col < num_cols; col++) {
			right = head->east;
			up->south = right;
			right = right->east;
			up = up->east;
		}
		// assign numbers into the nodes
		left = head;
		while (it != V.end()) {
			left->value = *it;
			it++;
			left = left->east;
		}

	}
}
int & ring::operator[](int a) {
	shared_ptr<node> target = head;	
	int row = a / num_cols, col = a % num_cols;
	int i = 0;
	while (i<row) {
		target = target->south;
		i++;
	}
	i = 0;
	while (i< col) {
		target = target->east;
		i++;
	}
	return target->value;
}
int & ring::operator[](pair<int, int> p) {
	int i = (p.first + 1) * (p.second + 1) - 1;
	return (*this)[i];
}
void ring::DelCol(int i) {
	if (i < 0 || i >= num_cols) return;
	if (num_cols > 0 && num_rows > 0) {
		shared_ptr<node> left = head, up, down;
		if (i == 0 && num_cols == 1) {
			head->east.reset();
			head->south.reset();
			this->head.reset();
		}
		int leftInx;
		if (num_rows == 1) {
			leftInx = i == 0 ? num_cols - 1 : i - 1;
			for (int j = 0; j < leftInx; j++) left = left->east;
			left->east = left->east->east;
			left->south = left->east->east;
			if (i == 0) head = left->east;
		}
		if (num_rows > 1) {
			leftInx = i == 0 ? num_cols - 1 : i - 1;
			for (int j = 0; j < leftInx; j++) left = left->east;
			down = i == 0 ? head->east : left->east->east;;
			for (int j = 0; j < num_rows - 1; j++) {
				left->east = left->east->east;
				left = left->south;
			}
			left->east = left->east->east;
			left->south = down;
			if (i == 0) head = down;
		}
		(this->num_cols)--;
	}
}
ring ring::Threetimes() {
	int max = num_cols * num_rows;
	ring tmpRing(num_rows, num_cols);
	shared_ptr<node> ptr = tmpRing.head;
	if ( max != 0) {
		int idx =0;
		while (idx < max) {
			int n = (*this)[idx];
			ptr->value = n*3;
			ptr = ptr->east;
			idx++;
		}
	}
	return tmpRing;
}
