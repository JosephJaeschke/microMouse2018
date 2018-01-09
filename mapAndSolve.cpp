#include <iostream>
#include <cmath>
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

void printWalls(short r,short c)
{
	cout<<"---"<<endl;
	cout<<"up:"<<grid[r][c].up<<endl;
	cout<<"right:"<<grid[r][c].right<<endl;
	cout<<"down:"<<grid[r][c].down<<endl;
	cout<<"left:"<<grid[r][c].left<<endl;
}

void init()
{
	for(short i=0;i<16;i++)
	{
		for(short j=0;j<16;j++)
		{
			grid[i][j].x=j;
			grid[i][j].y=i;
		}
	}
	//add testing maze (hopefully not manually)
	grid[0][0].up=1;
	grid[0][0].left=1;
	grid[0][0].right=1;
	grid[0][1].left=1;
	grid[0][1].right=1;
	grid[0][2].left=1;
	grid[0][2].right=1;
	grid[0][3].left=1;
	grid[0][3].down=1;
	grid[1][3].right=1;
	grid[1][3].down=1;
	grid[1][2].left=1;
	grid[1][2].right=1;
	grid[1][1].left=1;
	grid[1][1].right=1;
	grid[1][0].left=1;
	grid[1][0].up=1;
	grid[1][0].right=1;
	for(short i=0;i<4;i++)
	{
		for(short j=0;j<2;j++)
		{
	//		cout<<"("<<j<<","<<i<<")"<<endl;
	//		printWalls(j,i);
		}
	}
}

void setSpace(short row,short col)
{
	//SENSOR STUFF
	return;
}

void dfsR(short c,short r)
{
	cout<<"***dfsR***"<<endl;
	cout<<"("<<r<<","<<c<<")"<<endl;
	bool b=grid[r][c].up;
	grid[r][c].visited=1;
	setSpace(r,c);
	printWalls(r,c);
	if(grid[r][c].up==0&&grid[r-1][c].visited==0)
	{
		cout<<"*move up"<<endl;
		moveUp();
		facing='u';
		dfsR(r-1,c);
		moveDown();
		facing='d';
	}
	if(grid[r][c].right==0&&grid[r][c+1].visited==0)
	{
		cout<<"*move right"<<endl;
		moveRight();
		facing='r';
		dfsR(r,c+1);
		moveLeft();
		facing='l';
	}
	if(grid[r][c].down==0&&grid[r+1][c].visited==0)
	{
		cout<<"*move down"<<endl;
		moveDown();
		facing='d';
		dfsR(r+1,c);
		moveUp();
		facing='u';
	}
	if(grid[r][c].left==0&&grid[r][c-1].visited==0)
	{
		cout<<"*move left"<<endl;
		moveLeft();
		facing='l';
		dfsR(r,c-1);
		moveRight();
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

Node astar()
{
	cout<<"-astar-"<<endl;
	Node end;
	grid[0][0].g=0;
	Heap fringe;
	fringe.push(grid[0][0]);
	while(fringe.empty()!=true)
	{
		Node n=fringe.pop();
		if((n.x==7&&n.y==7)||(n.x==7&&n.y==8)||(n.x==8&&n.y==7)||(n.x==8&&n.y==8))
		{
			//found path
			return n;
		}
		grid[n.x][n.y].visited=1;
		for(short i=-1;i<2;i++)
		{
			for(short j=-1;j<2;j++)
			{
				if(i-j!=1||i-j!=-1)
				{
					continue;
				}
				if(n.x+i>0&&n.y+j>0&&n.x+i<16&&n.y+j<16&&grid[n.x+i][n.y+j].visited==0)
				{
					if(!fringe.contains(n.x+i,n.y+j))
					{
						grid[n.x+i][n.y+j].g=32767;
						grid[n.x+i][n.y+j].py=-1;
						grid[n.x+i][n.y+j].px=-1;
					}
					//update vertex
					if(grid[n.x][n.y].g+1<grid[n.x+i][n.y+j].g)
					{
						grid[n.x+i][n.y+j].g=grid[n.x][n.y].g+1;
						grid[n.x+i][n.y+j].h=abs(n.x+i-7.5)+abs(n.y+j-7.5);
						grid[n.x+i][n.y+j].px=n.x;
						grid[n.x+i][n.y+j].py=n.y;
						if(fringe.contains(n.x+i,n.y+j))
						{
							fringe.remove(n.x+i,n.y+j);
						}
						fringe.push(grid[n.x+i][n.y+j]);
					}
				}
			}
		}
	}
	return end;	
}

char* buildPath(Node end)
{

	
}

int main()
{
	init();
	dfsR(0,0);
//	astar();
	return 0;	
}

