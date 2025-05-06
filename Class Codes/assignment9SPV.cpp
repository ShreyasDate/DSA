/* A Dictionary stores keywords & its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword. */

#include<iostream>
#include<string>
using namespace std;
class dictionary;
class avlnode
{
	string keyword;
	string meaning;
	avlnode *left,*right;
	int bf;
public:
	avlnode()
	{
		keyword='\0';
		meaning='\0';
		left=right=NULL;
		bf=0;
	}
	avlnode(string k,string m)
	{
		keyword=k;
		meaning=m;
		left=right=NULL;
		bf=0;
	}
	
	void LLrotation(avlnode *a,avlnode *b)
	{
		cout<<"LL rotation"<<endl;
		a->left=b->right;
		b->right=a;
		a->bf=b->bf=0;
	}
	void RRrotation(avlnode *a,avlnode *b)
	{
		cout<<"RR rotation"<<endl;
		a->right=b->left;
		b->left=a;
		a->bf=b->bf=0;
	}

	void inorder(avlnode *root)
	{
		if(root)
		{
			inorder(root->left);
			cout<<root->keyword<<" "<<root->meaning<<endl;
			inorder(root->right);
		}
	}
	void descending(avlnode *root)
	{
		if(root)
		{
			descending(root->right);
			cout<<root->keyword<<" "<<root->meaning<<endl;
			descending(root->left);
		}
	}

	void update(avlnode *root,string key)
	{
		while(root!=NULL)
		{
			if (root->keyword == key)
			{
				cout<<"Enter new meaning of the word "<<root->keyword <<endl;
				cin>>root->meaning;
				return;
			}
			else if (key > root -> keyword)
				root = root->right;
			else
				root = root->left;
		}
		cout<<"\nWord not found";
	}

	avlnode* insert(avlnode *root, string key,string mean);
};

avlnode* avlnode::insert(avlnode *root, string key,string mean)
{
	if(!root)
	{
		//create new root
		root=new avlnode(key,mean);
		cout<<"ROOT CREATED \n";
		return root;
	}
	avlnode *a,*pa,*p,*pp;
	pa=NULL;
	p=a=root;
	pp=NULL;
	while(p)
	{
		//cout<<"In first while \n";
		if(p->bf)
		{
			a=p;
			pa=pp;
		}
		if(key<p->keyword)
		{
			pp=p;
			p=p->left;
		} //takes the left branch
		
		else if(key>p->keyword)
		{
			pp=p;
			p=p->right;
		} //right branch
		else
		{
			//p->meaning=mean;
			cout<<"Already exist \n";
			return root;
		}
	}
	//cout<<"Outside while \n";
	avlnode *y=new avlnode(key,mean);
	if(key<pp->keyword)
	{
		pp->left=y;
	}
	else
		pp->right=y;
		cout<<"KEY INSERTED \n";
	int d;
	avlnode *b,*c;
	b=c=NULL;
	if(key>a->keyword)
	{
		cout<<"KEY >A->KEYWORD \n";
		b=p=a->right;
		d=-1;
		cout<<" RIGHT HEAVY \n";
	}
	else
	{
		cout<<"KEY < A->KEYWORD \n";
		b=p=a->left;
		d=1;
		cout<<" LEFT HEAVY \n";
	}
	while(p!=y)
	{
		if(key>p->keyword)
		{
			p->bf=-1;
			p=p->right;
		}
		else
		{
			p->bf=1;
			p=p->left;
		}
	}
	cout<<" DONE ADJUSTING INTERMEDIATE NODES \n";
	if(!(a->bf)||!(a->bf+d))
	{
		a->bf+=d;
		return root;
	}
	if(d==1)
	{
		//left heavy
		if(b->bf==1)
		{
			LLrotation(a,b);
			/*a->left=b->right;
			b->right=a;
			a->bf=0;
			b->bf=0;*/
		}
		else //if(b->bf==-1)
		{
			cout<<"LR rotation"<<endl;
			c=b->right;
			b->right=c->left;
			a->left=c->right;
			c->left=b;
			c->right=a;
			switch(c->bf)
			{
			case 1:
			{
				a->bf=-1;
				b->bf=0;
				break;
			}
			case -1:
			{
				a->bf=0;
				b->bf=1;
				break;
			}
			case 0:
			{
				a->bf=0;
				b->bf=0;
				break;
			}
			}
			c->bf=0;
			b=c; //b is new root
		}
	}
	if(d==-1)
	{
		if(b->bf==-1)
		{
			RRrotation(a,b);
		}
		else// if(b->bf==1)
		{
			c=b->left;
			a->right=c->left;
			b->left=c->right;
			c->left=a;
			c->right=b;
			switch(c->bf)
			{
			case 1:
			{
				a->bf=0;
				b->bf=-1;
				break;
			}
			case -1:
			{
				a->bf=1;
				b->bf=0;
				break;
			}
			case 0:
			{
				a->bf=0;
				b->bf=0;
				break;
			}
			}
			c->bf=0;
			b=c; //b is new root
		}
		
	}
	
	if(!pa)
		root=b;
	else if(a==pa->left)
		pa->left=b;
	else
		pa->right=b;
	cout<<"AVL tree created!! \n";
	return root;
}
int main()
{
	int ch;
	string key,mean;
	avlnode *root= NULL,a;
	do
	{
		cout<<"\n\n ------- MENU ------ \n1.Insert \n2.Update \n3.Ascending \n4.Descending \n5.Quit \n";
		cout<<"\nEnter choice: ";
		cin>>ch;
		switch(ch)
		{
		case 1:
			cout<<"\nEnter keyword: ";
			cin>>key;
			cout<<"\nEnter meaning: ";
			cin>>mean;
			root=a.insert(root,key,mean);
			break;
		case 2:
			cout<<"\nEnter key whose meaning to update: ";
			cin>>key;
			a.update(root, key);
			break;
		case 3:
			cout<<"\nAscending Order\n";
			a.inorder(root);
			break;
		case 4:
			cout<<"\nDescending Order\n";
			a.descending(root);
			break;
		default:
			exit(0);
		}
	}while(ch!=6); 
	return 0;
}