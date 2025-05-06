/*
You have a business with several offices; you want to lease phone lines to connect them up with each other; and the phone company charges different amounts of money to connect different pairs of cities. You want a set of lines that connects all your offices with minimum total cost. Solve the problem by suggesting appropriate data structures.
*/

#include<iostream>
using namespace std;

class tree
{
	int a[20][20],start,end,w,i,j,v,e,visited[20]={0};
public:
    void input()
    {
	cout<<"Enter the no. of branches: ";
	cin>>v;

	for(i=0;i<v;i++)
		for(j=0;j<v;j++)
			a[i][j]=999;

	cout<<"\nEnter the no. of connections/edges: ";
	cin>>e;

	for(i=0;i<e;i++)
	{
		cout<<"Enter the #NUMBER of start and end branches of connections:  "<<endl;
		cin>>start>>end;
		cout<<"Enter the phone company charges for this connection:  ";
		cin>>w;
		a[start-1][end-1]=a[end-1][start-1]=w;
	}
    }
    void display()
    {
	cout<<"\nAdjacency matrix:\n";
	for(i=0;i<v;i++)
	{
		cout<<endl;
		for(j=0;j<v;j++)
		{
			cout<<a[i][j]<<"   ";
		}
		cout<<endl;
	}
    }
    void minimum()
    {
	int p=0,q=0,total=0,min;
	visited[0]=1;
	for(int count=0;count<(v-1);count++)
	{
		min=999;
		for(i=0;i<v;i++)
		{
			if(visited[i]==1)
			{
				for(j=0;j<v;j++)
				{
					if(visited[j]!=1)
					{
						if(min > a[i][j])
						{
							min=a[i][j];
							p=i;
							q=j;
						}
					}
				}
			}
		}
		visited[p]=1;
		visited[q]=1;
		total=total+min;
		cout<<"Minimum cost connection is"<<(p+1)<<" -> "<<(q+1)<<"  with charge : "<<min<< endl;
	}
	cout<<"The minimum total cost of connections of all branches is: "<<total<<endl;
    }
};
int main()
{
	int ch;
	tree t;
	while(1)
	{
		cout<<"==========PRIM'S ALGORITHM================="<<endl;
		cout<<"\n1. INPUT\n \n2. DISPLAY\n \n3. MST\n"<<endl;
		cout<<"Enter your choice : ";
		cin>>ch;
	
	switch(ch)
	{	
	case 1: cout<<"*******INPUT YOUR VALUES*******"<<endl;	
		t.input();
		break;

	case 2: cout<<"*******DISPLAY THE MATRIX********"<<endl;
		t.display();
		break;

	case 3: cout<<"*********MST************"<<endl;
		t.minimum();
		break;
	case 4:
		exit(0);
	}
	
	}
	return 0;
}