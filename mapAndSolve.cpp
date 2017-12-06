#include <iostream>
#include "Stack.h"
#include "Heap.h"
#include "Node.h"

using namespace std;

Node grid[16][16]={};
char facing='u'; //facing up default
//up=u,right=r,down=d,left=l

void moveUp()
{
	return;
}

void moveRight()
{
	return;
}

void moveDown()
{
	return;
}

void moveLeft()
{
	return;
}

void init()
{
	for(short i=0;i<16;i++)
	{
		for(short j=0;j<16;j++)
		{
			grid[i][j].x=i;
			grid[i][j].y=j;
		}
	}
}

void setSpace(char row,char col)
{
	//SENSOR STUFF
	return;
}

void dfsR(short r,short c)
{
	grid[r][c].visited=1;
	//setMapSpace(r,c);
	if(grid[r][c].up==0&&grid[r-1][c].visited==0)
	{
			//moveUp()
			facing='u';
			dfsR(r-1,c);
			//moveDown();
			facing='d';
	}
	if(grid[r][c].right==0&&grid[r][c+1].visited==0)
	{
		//moveRight();
		facing='r';
		dfsR(r,c+1);
		//moveLeft();
		facing='l';
	}
	if(grid[r][c].down==0&&grid[r+1][c].visited==0)
	{
		//moveDown()
		facing='d';
		dfsR(r+1,c);
		//moveUp()
		facing='u';
	}
	if(grid[r][c].left==0&&grid[r][c-1].visited==0)
	{
		//moveLeft()
		facing='l';
		dfsR(r,c-1);
		//moveRight();
		facing='r';
	}

}

/*
list nodes_to_visit = {root};
while( nodes_to_visit isn't empty ) {
	  currentnode = nodes_to_visit.take_first();
	    nodes_to_visit.prepend( currentnode.children );
	      //do something
}

void dfs()
{
	Stack s;
	grid[0][0].visited=1;
	s.push(grid[0][1]);
	s.push(grid[1][0]);
	short xold=0;
	short yold=0;
	while(s.empty()!=true)
	{
		Node curr=s.pop();
		


	
	}
	return;
}
*/

char* astar()
{
	char* path;
	grid[0][0].g=0;
	Heap fringe;
	fringe.push(grid[0][0]);
	while(fringe.empty()!=true)
	{
		Node n=fringe.pop();
		if((n.x==7&&n.y==7)||(n.x==7&&n.y==8)||(n.x==8&&n.y==7)||(n.x==8&&n.y==8))
		{
			//found path
		}
		grid[n.x][n.y].visited=1;
		//for each neighbor
		if(n.x-1>0&&grid[n.x-1][n.y].visited==0)
		{
			if(!fringe.contains(n.x-1,n.y))
			{
				grid[n.x-1][n.y].g=32767;
				grid[n.x-1][n.y].py=-1;
				grid[n.x-1][n.y].px=-1;
			}
			//update vertex
			if(grid[n.x][n.y].g+1<grid[n.x-1][n.y].g)
			{
				grid[n.x-1][n.y].g=grid[n.x][n.y].g+1;
				grid[n.x-1][n.y].px=n.x;
				grid[n.x-1][n.y].py=n.y;
				if(fringe.contains(n.x-1,n.y))
				{
					//not finished
					return path;
				}
			}
		}
	}
	return path;	
}

int main()
{
	Stack stack;	
	grid[0][1].visited=26;
	stack.push(grid[0][1]);
	Node p=stack.pop();
	cout<<"poped vis: "<<p.visited<<endl;
	cout<<"poped err: "<<p.err<<endl;
	p=stack.pop();
	cout<<"poped vis: "<<p.visited<<endl;
	cout<<"poped err: "<<p.err<<endl;
	//int b=stack.size();
	//cout<<"size: "<<b<<endl;
	//dfs(1,1);
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
	//		cout<<"UP: "<<grid[i][j]<<endl;
		}
	}
	return 0;	
}

