#include<stdio.h>
#include<iostream>
using namespace std;
#define  MaxSize 100000
//ABC##DE#G##F###
//ABDH###E##CF##G##
typedef struct  node{
	char data;	//������
	struct node *lchild ,  *rchild;  //���Һ���ָ��
}BinTNode, *BinTree;    //���н������

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
	static char stack[1000];//���ڴ�ŴӸ���㵽��ǰ���Ķ�̬���µ�ջ
	stack[level++]=T->data;
	if(T->data==c)
	{
		flag=true;
		int i=0;
		printf("���ڵ㵽��ǰ����·��Ϊ:\n");
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
		printf("\n1.�����������洢�ṹ��\n");
		printf("2.������������������\n");
		printf("3.������������������\n");
		printf("4.��������ĺ��������\n");
		printf("5.��������Ĳ�α�����\n");
		printf("6.�����������·����\n");
		printf("0.�˳�ϵͳ��\n");
		printf("������ָ��:\n");
		scanf("%d",&order);
		switch(order)
		{
			case 1:
			{
				printf("�밴�����������������н���ֵ��һ���ַ����������������洢�ṹ��\n");
				CreateBinTree(T);
				printf("������������ϡ�\n");
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
				printf("��������Ҫ����һ����������ϵ�·����\n");
				cin>>data;
				SearchNode(T,data,0);
				if(!flag)
				{
					printf("�Բ���û���ҵ��ý���·����\n"); 
				}
				break;
			}
			case 0:
				return 0;

			default:
				printf("�Բ�������ָ����������,���������롣\n");
		}
	}
		return 0;
}


	
