#include<iostream>
#include<fstream>
#include<string>
using namespace std;


struct tree
{
	string tg;
	struct tree *next,*father,*son;
};

struct stack
{
	struct tree *p;
	struct stack *snext;
}*s=NULL;


int empty()
{
	return s==NULL;
}

void push(struct tree *temp)
{
	if(s==NULL)
	{
		s=new stack;
		s->snext=NULL;
		s->p=temp;
	}
	else
	{
		stack *stemp=new stack;
		*stemp=*s;
		s->snext=stemp;
		s->p=temp;
	}
}

struct tree * pop()
{
	stack *stemp;
	stemp=s;
	s=s->snext;
	return stemp->p;
}

string top()
{
	return s->p->tg;
}

void pretrav(struct tree * temp)
{
	if(temp==NULL)
	{
		return ;
	}
	cout<<temp->tg<<endl;
	pretrav(temp->next);
	pretrav(temp->son);
}

int main()
{
	string t,ex;
	char fname[100];
	cin>>fname;
	ifstream f(fname);
	tree *root=NULL,*temp,*temp1,*temp3;
	if(!f.is_open())
	{
		cout<<"there was an error in opening the file"<<endl;
		cout<<"this error is unrecoverable exiting....."<<endl;
	}
	else
	{
		cout<<"alright here we go!!"<<endl;
	}
	while(getline(f,t))
	{
		for(int i=0;i<t.length();i++)
		{
			if(t[i]=='<' && t[i+1]!='!')
			{
				int f=1;
				int k=++i;
				int j=0;
				while(t[i]!='>' && t[i]!=' ')
				{
					j++;
					i++;
				}
				ex=t.substr(k,j);
				if(ex[0]=='/')
				{
					ex=ex.substr(1);
					if(ex==top())
					{
						temp=pop();
						temp1=temp1->father;
						continue;
					}
					else
					{
						f=0;
					}
				}
				temp=new tree;
				temp->son=NULL;
				temp->father=NULL;
				temp->next=NULL;
				temp->tg=ex;
				if(root==NULL)
				{
					root=temp;
					temp1=root;
					push(temp);
				}
				else
				{
					if(temp1->son==NULL)
					{
						temp1->son=temp;
					}
					else
					{
						temp3=temp1->son;
						while(temp3->next!=NULL)
						{
							temp3=temp3->next;
						}
						temp3->next=temp;
					}
					temp->father=temp1;
					temp1=temp;
					if(f)
					{
						push(temp);
					}
				}
			}
		}
	}
	pretrav(root);
	return 0;
}
