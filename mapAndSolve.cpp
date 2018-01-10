#include <iostream>
#include "Stack.h"
#include "Heap.h"
#include "Node.h"

using namespace std;

Node grid[16][16]={};
char facing='u'; //facing up default

void move()
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
void setSpace(short row,short col)
{
	return;
}

short abs(short num)
{
	if(num<0)
	{
		return -1*num;
	}
	return num;
}

void moveUp()
{
	if(facing=='r')
	{
		turnCW();
	}
	else if(facing=='d')
	{
		turnCW();
		turnCW();
	}
	else if(facing=='l')
	{
		turnCCW();
	}
	move();
	return;
}

void moveRight()
{
	if(facing=='u')
	{
		turnCW();
	}
	else if(facing=='d')
	{
		turnCCW();
	}
	else if(facing=='l')
	{
		turnCW();
		turnCW();
	}
	move();
	return;
}

void moveDown()
{
	if(facing=='u')
	{
		turnCW();
		turnCW();
	}
	else if(facing=='r')
	{
		turnCW();
	}
	else if(facing=='l')
	{
		turnCCW();
	}
	move();
	return;
}

void moveLeft()
{
	if(facing=='u')
	{
		turnCCW();
	}
	else if(facing=='r')
	{
		turnCW();
		turnCW();
	}
	else if(facing=='d')
	{
		turnCW();
	}
	move();
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
			grid[i][j].x=i;
			grid[i][j].y=j;
		}
	}
	//add testing maze (hopefully not manually)
	/*
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
	*/
	
	grid[0][0].up=1;
	grid[0][0].right=1;
	grid[0][0].left=1;
	grid[0][1].left=1;
	grid[0][2].down=1;
	grid[0][2].left=1;
	grid[1][0].up=1;
	grid[1][0].right=1;
	grid[1][0].left=1;
	grid[1][1].down=1;
	grid[1][2].up=1;
	grid[1][2].down=1;
	grid[2][0].up=1;
	grid[2][0].right=1;
	grid[2][0].left=1;
	grid[2][1].right=1;
	grid[2][2].right=1;
	grid[2][2].down=1;
}

void reset()
{
	for(short i=0;i<16;i++)
	{
		for(short j=0;j<16;j++)
		{
			grid[i][j].visited=0;
		}
	}
}

void dfsR(short r,short c)
{
	cout<<"("<<r<<","<<c<<")"<<endl;
	grid[r][c].visited=1;
	setSpace(r,c);
	//printWalls(r,c);
	if(grid[r][c].up==0&&grid[r][c-1].visited==0)
	{
		cout<<"*move up"<<endl;
		moveUp();
		facing='u';
		dfsR(r,c-1);
		moveDown();
		facing='d';
	}
	if(grid[r][c].right==0&&grid[r+1][c].visited==0)
	{
		cout<<"*move right"<<endl;
		moveRight();
		facing='r';
		dfsR(r+1,c);
		moveLeft();
		facing='l';
	}
	if(grid[r][c].down==0&&grid[r][c+1].visited==0)
	{
		cout<<"*move down"<<endl;
		moveDown();
		facing='d';
		dfsR(r,c+1);
		moveUp();
		facing='u';
	}
	if(grid[r][c].left==0&&grid[r-1][c].visited==0)
	{
		cout<<"*move left"<<endl;
		moveLeft();
		facing='l';
		dfsR(r-1,c);
		moveRight();
		facing='r';
	}
}

void dfs()
{
	Stack s;
	grid[0][0].visited=1;
	s.push(grid[0][1]);
	s.push(grid[1][0]);
	while(s.empty()!=true)
	{
		Node curr=s.pop();
		if(curr.x+1<16&&curr.x+1>=0&&curr.y<16&&curr.y>=0&&grid[curr.x+1][curr.y].visited==0)
		{
			s.push(grid[curr.x+1][curr.y]);
			grid[curr.x+1][curr.y].visited=1;
			grid[curr.x+1][curr.y].px=curr.x;
			grid[curr.x+1][curr.y].py=curr.y;
		}
		if(curr.x<16&&curr.x>=0&&curr.y+1<16&&curr.y+1>=0&&grid[curr.x][curr.y+1].visited==0)
		{
			s.push(grid[curr.x][curr.y+1]);
			grid[curr.x][curr.y+1].visited=1;
			grid[curr.x][curr.y+1].px=curr.x;
			grid[curr.x][curr.y+1].py=curr.y;
		}
		if(curr.x<16&&curr.x>=0&&curr.y-1<16&&curr.y-1>=0&&grid[curr.x][curr.y-1].visited==0)
		{
			s.push(grid[curr.x][curr.y-1]);
			grid[curr.x][curr.y-1].visited=1;
			grid[curr.x][curr.y-1].px=curr.x;
			grid[curr.x][curr.y-1].py=curr.y;
		}
		if(curr.x-1<16&&curr.x-1>=0&&curr.y<16&&curr.y>=0&&grid[curr.x-1][curr.y].visited==0)
		{
			s.push(grid[curr.x-1][curr.y]);
			grid[curr.x-1][curr.y].visited=1;
			grid[curr.x-1][curr.y].px=curr.x;
			grid[curr.x-1][curr.y].py=curr.y;
		}
	}
	return;
}

Node astar()
{
	Node end;
	grid[0][0].g=0;
	Heap fringe;
	fringe.push(grid[0][0]);
	while(fringe.empty()!=true)
	{
		Node n=fringe.pop();
		cout<<"("<<n.x<<","<<n.y<<")"<<endl;
		if(/*(n.x==7&&n.y==7)||(n.x==7&&n.y==8)||(n.x==8&&n.y==7)||(n.x==8&&n.y==8)*/n.x==1&&n.y==2)
		{
			//found path
			cout<<"FOUND PATH!!!"<<endl;
			return n;
		}
		grid[n.x][n.y].visited=1;
		for(short i=-1;i<2;i++)
		{
			for(short j=-1;j<2;j++)
			{
				if(i+j==-2||i+j==0||i+j==2||(i==0&&j==0))
				{
					continue;
				}
				cout<<"-("<<n.x+i<<","<<n.y+j<<")"<<endl;
				if(n.x+i>=0&&n.y+j>=0&&n.x+i<16&&n.y+j<16&&grid[n.x+i][n.y+j].visited==0)
				{
					if(i==0&&j==-1&&grid[n.x][n.y].up==1)
					{
						continue;
					}
					else if(i==1&&j==0&&grid[n.x][n.y].right==1)
					{
						continue;
					}
					else if(i==0&&j==1&&grid[n.x][n.y].down==1)
					{
						continue;
					}
					else if(i==-1&&j==0&&grid[n.x][n.y].left==1)
					{
						continue;
					}
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
/*THIS LINE HAS HEURISTIC*/			grid[n.x+i][n.y+j].h=abs(n.x+i-1)+abs(n.y+j-2);
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
	cout<<"no path..."<<endl;
	return end;	
}

void buildPath(Node end)
{
	Node n=end;
	cout<<"___PATH___"<<endl;
	char path[100];
	short i;
	for(i=0;n.x!=0||n.y!=0;i++)
	{
		if(n.x-n.px==-1&&n.y-n.py==0)
		{
			path[i]='l';
		}
		else if(n.x-n.px==0&&n.y-n.py==-1)
		{
			path[i]='u';
		}
		else if(n.x-n.px==0&&n.y-n.py==1)
		{
			path[i]='d';
		}
		else if(n.x-n.px==1&&n.y-n.py==0)
		{
			path[i]='r';
		}
		cout<<"("<<n.x<<","<<n.y<<")"<<endl;
		n=grid[n.px][n.py];
	}
	short j,temp;
	for (j=0;j<i/2;++j)
	{
		temp=path[i-j-1];
		path[i-j-1]=path[j];
		path[j]=temp;
	}
	for (j=0;j<i;++j)
	{
		cout<<"move "<<path[j]<<endl;
		if(path[j]=='u')
		{
			moveUp();
		}
		else if(path[j]=='r')
		{
			moveRight();
		}
		else if(path[j]=='d')
		{
			moveDown();
		}
		else if(path[j]=='l')
		{
			moveLeft();
		}
	}
}

int main()
{
	init();
	cout<<"***dfs***"<<endl;
	dfs();
	reset();
	cout<<"***astar***"<<endl;
	buildPath(astar());
	return 0;	
}
