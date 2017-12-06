#include "Node.h"

using namespace std;

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
			cout<<"its full"<<endl;
			return;
		}
		s[top].visited=t.visited;
		s[top].up=t.up;
		s[top].right=t.right;
		s[top].down=t.down;
		s[top].left=t.left;
		s[top].err=0;
		top++;
	}
	Node pop()
        {
		if (top==0)
		{
			cout<<"no pop"<<endl;
			Node a;
			a.err=1;
			return a;
		}
		s[--top].err=0;
		return s[top];
	}
//	int size()
//	{
//		if (top==0)
//		{
//			return 0;
//		}
//		return top;
//	}
	bool empty()
	{
		return top==0;  
	}
	private:
	Node s[100];
	short top;
	short maxelem;
};

