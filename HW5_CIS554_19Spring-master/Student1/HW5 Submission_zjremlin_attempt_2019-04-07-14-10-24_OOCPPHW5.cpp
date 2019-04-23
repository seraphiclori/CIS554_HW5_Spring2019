// OOCPPHW5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
//HW5 Due: April 7 (Sunday) at 11:59PM
#include <iostream>
#include <memory>
//#include "MemChecker.h"

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
	ring() {}
	ring(int i, int j);//constructor
					   //i rows and j cols
					   //values from 0 to i*j-1
					//See the photo for ring structures.

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

//overload operator<<
ostream & operator<< (ostream & out, const ring & r)
{
	//out << "Printing R: {" << endl;
	int count = 0, i=0;
	shared_ptr <node> temp = r.head;
	//out << endl << "(Row " << i << ")  ";
	while (temp->east != r.head)
	{
		out << temp->value << "  ";
		temp = temp->east;
		count++;
		if (count == r.num_cols)
		{
			i++;
			out << endl;
			//out << endl<< "(Row "<<i<<")  ";
			count = 0;
		}
	}

	out << temp->value<< endl<<endl ;
	/*
	count=i = 0;
	temp = r.head;
	out << endl << "(Col "<<i<<")  ";
	while (temp->south != r.head)
	{
		out << temp->value << "      ";
		temp = temp->south;
		count++;
		if (count == r.num_rows)
		{
			i++;
			out << endl<<"(Col "<<i << ")  ";
			count = 0;
		}
	}
	out << temp->value << endl<<"}" ;
	

	*/
	return out;
}
int main() {
	
	ring R1(4, 6);//24 numbers from 0 to 23 will be initialized to nodes.

	cout << R1 << endl;
	R1[14] = 1000;
	R1[{2, 4}] = 2000;
	cout << R1[14] << " " << R1[{2, 4}] << endl;
	R1.DelCol(3);
	cout << R1 << endl;
	R1.DelCol(4);
	cout << R1 << endl;
	R1.DelCol(0);
	cout << R1 << endl;
	shared_ptr<ring> p1 = make_shared<ring>(3, 5);
	cout << *p1 << endl;
	p1.reset();
	ring R2 = { 3, 5, 10,20,30,40,50, 100, 200, 300, 400, 500, 1000, 2000, 3000, 4000, 5000 };//
	 //first two numbers are num_rows and num_cols; followed by values of nodes of ring
	cout << R2 << endl;
	ring R3(R2);
	cout << R3 << endl;
	ring R4;
	R4 = R3;
	cout << R4 << endl;
	ring R5;
	R5 = R4.Threetimes();
	cout << R5 << endl;

	getchar();
	getchar();
	return 0;
}

ring::ring(int i, int j):num_rows(i), num_cols(j)
{
	if ((i == 0) || (j == 0))
		return;
	head = make_shared<node>(0);
	shared_ptr<node> temp = head;
	for ( int a =1; a < (num_rows*num_cols);a++)
	{
		temp->east = make_shared<node>(a);
		temp = temp->east;
	}
	temp->east = head;
	temp->south = head;
	temp = head;
	shared_ptr<node> t1 = head;

	for (int p = 0; p < ((num_rows - 1)*num_cols);p++)
	{
		for (int l = 0; l < (num_cols); l++)
		{
			t1 = t1->east;
		}
		temp->south = t1;
		temp = temp->east;
		t1 = temp;
	}
	for (int p = 1; p < (num_cols); p++)
	{
		for (int l = 0; l < (num_cols+1); l++)
		{
			t1 = t1->east;
		}
		temp->south = t1;
		temp = temp->east;
		t1 = temp;
	}
	
}

ring::~ring()
{
	//cout << "At beginnging" << endl;
	if (head == nullptr)
		return;
	auto temp = head;

	while (temp->east != head)
	{
		//cout << "in loop" << endl;
		temp->south.reset();
		temp = temp->east;
	}
	//cout << "out of loop" << endl;
	temp->east.reset();
	temp->south.reset();
	temp.reset();
	head.reset();
	//cout << "At end " << endl;
}

ring::
ring(const ring & r): ring (r.num_rows, r.num_cols)
{
	auto temp = r.head;
	int counter = 0;
	while (temp->east != r.head)
	{
		this->operator[](counter) = temp->value;
		temp = temp->east;
		counter++;
	}
	this->operator[](counter) = temp->value;
}

ring::ring(ring && r) 
{
	//cout << "in move" << endl;
	this->num_cols = r.num_cols;
	this->num_rows = r.num_rows;
	this->head = r.head;
	r.head = nullptr;
}

void ring::operator=(ring && r)
{
	//cout << "in r operator" << endl;
	this->num_cols = r.num_cols;
	this->num_rows = r.num_rows;
	this->head = r.head;
	r.head = nullptr;
}

void ring::operator=(const ring & r)
{

	if (head != nullptr)
	{
		auto temp1 = head;
		while (temp1->east != head)
		{
			temp1->south.reset();
			temp1 = temp1->east;
		}
		temp1->east.reset();
		temp1->south.reset();
		temp1.reset();
		head.reset();
	}

	//following is the same code as the constructor 
	num_rows = r.num_rows;
	num_cols = r.num_cols;
	if ((num_rows == 0) || (num_cols == 0))
		return;
	head = make_shared<node>(0);
	shared_ptr<node> temp = head;
	for (int a = 1; a < (num_rows*num_cols); a++)
	{
		temp->east = make_shared<node>(a);
		temp = temp->east;
	}
	temp->east = head;
	temp->south = head;
	temp = head;
	shared_ptr<node> t1 = head;

	for (int p = 0; p < ((num_rows - 1)*num_cols); p++)
	{
		for (int l = 0; l < (num_cols); l++)
		{
			t1 = t1->east;
		}
		temp->south = t1;
		temp = temp->east;
		t1 = temp;
	}
	for (int p = 1; p < (num_cols); p++)
	{
		for (int l = 0; l < (num_cols + 1); l++)
		{
			t1 = t1->east;
		}
		temp->south = t1;
		temp = temp->east;
		t1 = temp;
	}

}

ring::ring(const initializer_list<int>& V):ring (*V.begin(),*(V.begin()+1)) //Professor said this was okay 
{
	auto it = V.begin()+2;
	int counter = 0;
	while (it != V.end())
	{
		this->operator[](counter) = *it;
		it++;
		counter++;
	}
}

int & ring::operator[](int a)
{
	// TODO: insert return statement here
	auto temp = head;
	//if ((a >= (num_rows*num_cols))|| (a<0))  //said this would not happen so i guess I dont need it
	//	return *new int(-1); // not sure if this is the correct fail return 

	for (int i = 0; i < a; i++)
	{
		temp = temp->east;
	}
	return temp ->value;
}

int & ring::operator[](pair<int, int> p)
{
	if ((p.first >=num_rows)||(p.second>=num_cols))
		return *(new int(-1));
	if ((p.first<0)||(p.second<0))
		return *(new int(-1));
	auto temp = head;
	for (int i = 0; i < p.first; i++)
		temp = temp->east;
	for (int i = 0; i < p.second; i++)
		temp = temp->south;
	return temp->value;

}

void ring::DelCol(int i)
{
	if (i >= num_cols)
		return;
	if (i < 0)
		return;
	if (i == 0)
		i = num_cols;
	auto temp = head;
	for (int j = 0; j < (i - 1); j++)
		temp = temp->east;
	for (int j = 0; j < (num_rows-1); j++)
	{
		temp->east = temp->east->east;
		temp = temp->south;
	}
	if (i ==num_cols)
		temp->south = temp->east->east;
	else
		temp->south = temp->east->south;
	temp->east = temp->east->east;
	
	if (i == num_cols)
		head = head->east;

	num_cols--;
}

ring ring::Threetimes()
{
	if ((num_cols == 0) || (num_rows == 0))
		return move(ring (0,0)); //an empty matrix times 3 is still empty
	ring temp(*this);
	for (int i = 0; i < (temp.num_cols*temp.num_rows); i++)
	{
		temp[i] = temp[i] * 3;
	}
	return move(temp);
}
