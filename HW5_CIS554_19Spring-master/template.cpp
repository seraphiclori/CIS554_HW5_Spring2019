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
