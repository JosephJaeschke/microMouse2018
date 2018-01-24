#include "Stack.h"
#include "Heap.h"
#include "Node.h"

using namespace std;

Node grid[16][16]={};
char facing='u'; //facing up default

void moveOne();
void turnCW();
void turnCCW();
void setSpace(short row,short col);

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
	moveOne();
	facing='u';
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
	moveOne();
	facing='r';
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
	moveOne();
	facing='d';
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
	moveOne();
	facing='l';
	return;
}

/*
void printWalls(short r,short c)
{
	cout<<"---"<<endl;
	cout<<"up:"<<grid[r][c].up<<endl;
	cout<<"right:"<<grid[r][c].right<<endl;
	cout<<"down:"<<grid[r][c].down<<endl;
	cout<<"left:"<<grid[r][c].left<<endl;
}
*/

void inity()
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
			grid[i][j].px=0;
			grid[i][j].py=0;
		}
	}
}

void dfsR(short r,short c)
{
	grid[r][c].visited=1;
	setSpace(r,c);
	//printWalls(r,c);
	if(grid[r][c].up==0&&grid[r][c-1].visited==0)
	{
		moveUp();
		dfsR(r,c-1);
		moveDown();
	}
	if(grid[r][c].right==0&&grid[r+1][c].visited==0)
	{
		moveRight();
		dfsR(r+1,c);
		moveLeft();
	}
	if(grid[r][c].down==0&&grid[r][c+1].visited==0)
	{
		moveDown();
		dfsR(r,c+1);
		moveUp();
	}
	if(grid[r][c].left==0&&grid[r-1][c].visited==0)
	{
		moveLeft();
		dfsR(r-1,c);
		moveRight();
	}
}

void dfs()
{
	Stack s;
	Stack his;
	Node curr;
	s.push(grid[0][0]);
	while(s.empty()!=true)
	{
		curr=s.pop();
//		cout<<"curr: ("<<curr.x<<","<<curr.y<<")"<<endl;
		if(curr.x-grid[curr.x][curr.y].px==-1&&grid[curr.x][curr.y].visited!=1)
		{
			moveLeft();
		}
		else if(curr.x-grid[curr.x][curr.y].px==1&&grid[curr.x][curr.y].visited!=1)
		{
			moveRight();
		}
		else if(curr.y-grid[curr.x][curr.y].py==1&&grid[curr.x][curr.y].visited!=1)
		{
			moveDown();
		}
		else if(curr.y-grid[curr.x][curr.y].py==-1&&grid[curr.x][curr.y].visited!=1)
		{
			moveUp();
		}
		setSpace(curr.x,curr.y);
		grid[curr.x][curr.y].visited=1;
		short count=0;
		if(curr.x<16&&curr.x>=0&&curr.y-1<16&&curr.y-1>=0&&grid[curr.x][curr.y-1].visited==0&&grid[curr.x][curr.y].up==0)
		{
//			cout<<"pushed ("<<curr.x<<","<<curr.y-1<<")"<<endl;
			s.push(grid[curr.x][curr.y-1]);
			grid[curr.x][curr.y-1].px=curr.x;
			grid[curr.x][curr.y-1].py=curr.y;
			count++;
		}
		if(curr.x+1<16&&curr.x+1>=0&&curr.y<16&&curr.y>=0&&grid[curr.x+1][curr.y].visited==0&&grid[curr.x][curr.y].right==0)
		{
//			cout<<"pushed ("<<curr.x+1<<","<<curr.y<<")"<<endl;
			s.push(grid[curr.x+1][curr.y]);
			grid[curr.x+1][curr.y].px=curr.x;
			grid[curr.x+1][curr.y].py=curr.y;
			count++;
		}
		if(curr.x<16&&curr.x>=0&&curr.y+1<16&&curr.y+1>=0&&grid[curr.x][curr.y+1].visited==0&&grid[curr.x][curr.y].down==0)
		{
//			cout<<"pushed ("<<curr.x<<","<<curr.y+1<<")"<<endl;
			s.push(grid[curr.x][curr.y+1]);
			grid[curr.x][curr.y+1].px=curr.x;
			grid[curr.x][curr.y+1].py=curr.y;
			count++;
		}
		if(curr.x-1<16&&curr.x-1>=0&&curr.y<16&&curr.y>=0&&grid[curr.x-1][curr.y].visited==0&&grid[curr.x][curr.y].left==0)
		{
//			cout<<"pushed ("<<curr.x-1<<","<<curr.y<<")"<<endl;
			s.push(grid[curr.x-1][curr.y]);
			grid[curr.x-1][curr.y].px=curr.x;
			grid[curr.x-1][curr.y].py=curr.y;
			count++;
		}
		if(count==0&&s.empty()==0) //dead end, retrace steps
		{
			Node stop=s.peek();
			stop=grid[grid[stop.x][stop.y].px][grid[stop.x][stop.y].py];
			Node temp=curr;
//			grid[stop.x][stop.y].visited=1;
//			cout<<"stop: ("<<stop.x<<","<<stop.y<<")"<<endl;
			//curr=his.pop();
			while(!(temp.x==grid[stop.x][stop.y].x&&temp.y==grid[stop.x][stop.y].y))
			{
				if(temp.x<0||temp.y<0||temp.y>15||temp.x>15)
				{
					break;
				}
//				cout<<"curr: ("<<temp.x<<","<<temp.y<<")"<<endl;
				if(temp.x-grid[temp.x][temp.y].px==-1)
				{
					moveRight();
				}
				else if(temp.x-grid[temp.x][temp.y].px==1)
				{
					moveLeft();
				}
				else if(temp.y-grid[temp.x][temp.y].py==1)
				{
					moveUp();
				}
				else if(temp.y-grid[temp.x][temp.y].py==-1)
				{
					moveDown();
				}
				temp=his.pop();
			}
//			cout<<"end curr: ("<<curr.x<<","<<curr.y<<")"<<endl;
		}
		his.push(curr);
	}
	/*
	cout<<"end1?"<<endl;
	//end so go back to start
//	cout<<"==="<<endl;
	while(curr.x!=0||curr.y!=0)
	{
		cout<<"curr: ("<<curr.x<<","<<curr.y<<")"<<endl;
		if(curr.x-grid[curr.x][curr.y].px==-1)
		{
			cout<<"^move Right"<<endl;
			moveRight();
		}
		else if(curr.x-grid[curr.x][curr.y].px==1)
		{
			cout<<"^move Left"<<endl;
			moveLeft();
		}
		else if(curr.y-grid[curr.x][curr.y].py==1)
		{
			cout<<"^move Up"<<endl;
			moveUp();
		}
		else if(curr.y-grid[curr.x][curr.y].py==-1)
		{
			cout<<"^move Down"<<endl;
			moveDown();
		}
		curr=grid[grid[curr.x][curr.y].px][grid[curr.x][curr.y].py];
	}
	*/
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
//		cout<<"("<<n.x<<","<<n.y<<")"<<endl;
		if(/*(n.x==7&&n.y==7)||(n.x==7&&n.y==8)||(n.x==8&&n.y==7)||(n.x==8&&n.y==8)*/n.x==1&&n.y==2)
		{
			//found path
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
//				cout<<"-("<<n.x+i<<","<<n.y+j<<")"<<endl;
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
	return end;	
}

void buildPath(Node end)
{
	Node n=end;
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
