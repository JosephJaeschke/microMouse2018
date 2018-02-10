#include "Stack.h"
#include <iostream>

using namespace std;

void moveOne()
{
	return;
}

void turnCW()
{
	return;
}

void turnCCW()
{
	return;
}

void setSpace(short r,short c)
{
	return;
}

int main()
{
	Stack s;
	Node n;
	n.x=3;
	Node m;
	m.x=4;
	s.push(n);
	s.push(m);
	Node b=s.pop();
	cout<<b.x<<endl;
	b=s.peek();
	cout<<b.x<<endl;
	Node o=s.pop();
	cout<<o.x<<endl;
	o.x=5;
	s.push(o);
	m=s.pop();
	cout<<m.x<<endl;
	return 0;
}
