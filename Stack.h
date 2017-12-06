#include "Node.h"

class Stack
{
	public:
	Stack()
	{
		top=0;
		maxelem=100;
	}
	void push(Node t)
	{
		if(top==maxelem)
		{
			return;
		}
		s[top]=t;
		top++;
	}
	Node pop()
        {
		if (top==0)
		{
			Node a;
			a.err=1;
			return a;
		}
		s[--top].err=0;
		return s[top];
	}
	bool empty()
	{
		return top==0;  
	}
	private:
	Node s[100];
	short top;
	short maxelem;
};

