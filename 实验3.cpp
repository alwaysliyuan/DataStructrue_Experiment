#include<stdio.h>
#include<iostream>
using namespace std;
#define  MaxSize 100000
//ABC##DE#G##F###
//ABDH###E##CF##G##
typedef struct  node{
	char data;	//数据域
	struct node *lchild ,  *rchild;  //左右孩子指针
}BinTNode, *BinTree;    //树中结点类型

typedef struct 
{
	BinTree *base;
	int front;
	int rear;
}Queue;

bool flag=false;

void CreateBinTree(BinTree &T);
void PreOrderTraverse(BinTree T);
void InOrderTraverse(BinTree T);
void PostOrderTraverse(BinTree T);
void LevelOrderTraverse(BinTree T);
void SearchNode(BinTree T,char c,int level); 

void CreateBinTree(BinTree &T)
{
	char ch;
	cin>>ch;
	if(ch=='#')
	{
		T=NULL;
	}
	else
	{
		T=new BinTNode;
		T->data=ch;
		CreateBinTree(T->lchild);
		CreateBinTree(T->rchild);
	}
}

void PreOrderTraverse(BinTree T)
{
	if(T)
	{
		cout<<T->data;
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild); 
	}
}


void InOrderTraverse(BinTree T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		cout<<T->data;
		InOrderTraverse(T->rchild); 
	}
 } 
 
 void PostOrderTraverse(BinTree T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout<<T->data; 
	}
 }
 
 
 void LevelOrderTraverse(BinTree T)
 {
 	Queue Q;
 	Q.base= new BinTree[MaxSize];
 	if(!Q.base) exit(0);
 	Q.front=Q.rear=0;
 	
 	if(T)
 	{
 		Q.base[Q.rear++]=T;
 		while(Q.front<Q.rear)
		{
 			if(Q.base[Q.front])
 			{
 				Q.base[Q.rear++]=Q.base[Q.front]->lchild;
 				Q.base[Q.rear++]=Q.base[Q.front]->rchild;
 				printf("%c ",Q.base[Q.front]->data);	
 				
			 }
			 Q.front++;
		}	
	 }
 }



void SearchNode(BinTree T,char c,int level)
{
	if(T==NULL) return ;
	static char stack[1000];//用于存放从根结点到当前结点的动态更新的栈
	stack[level++]=T->data;
	if(T->data==c)
	{
		flag=true;
		int i=0;
		printf("根节点到当前结点的路径为:\n");
		while(i<level-1)
		{
			cout<<stack[i++]<<"->";
		}
		cout<<stack[i]<<endl;
		return ;
	}
	 SearchNode(T->lchild,c,level);
	 SearchNode(T->rchild,c,level);
	
}



int main()
{
	int order;
	BinTree T;
	while(1)
	{
		printf("\n1.建立二叉树存储结构。\n");
		printf("2.求二叉树的先序遍历。\n");
		printf("3.求二叉树的中序遍历。\n");
		printf("4.求二叉树的后序遍历。\n");
		printf("5.求二叉树的层次遍历。\n");
		printf("6.求出给定结点的路径。\n");
		printf("0.退出系统。\n");
		printf("请输入指令:\n");
		scanf("%d",&order);
		switch(order)
		{
			case 1:
			{
				printf("请按先序次序输入二叉树中结点的值（一个字符），创建二叉树存储结构。\n");
				CreateBinTree(T);
				printf("二叉树建立完毕。\n");
				break;
			}

			case 2:
			{
				PreOrderTraverse(T);
				printf("\n");
				break;
			}
			case 3:
			{
				InOrderTraverse(T);
				printf("\n");
				break;
			}
			case 4:
			{
				PostOrderTraverse(T);
				printf("\n");
				break;
			}
			case 5:
				LevelOrderTraverse(T);
				printf("\n");
				break;

			case 6:
			{
				flag=false;
				char data;
				printf("请问您想要找哪一个结点在树上的路径？\n");
				cin>>data;
				SearchNode(T,data,0);
				if(!flag)
				{
					printf("对不起，没有找到该结点的路径。\n"); 
				}
				break;
			}
			case 0:
				return 0;

			default:
				printf("对不起，您的指令输入有误,请重新输入。\n");
		}
	}
		return 0;
}


	
