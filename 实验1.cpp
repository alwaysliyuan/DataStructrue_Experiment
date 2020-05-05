#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>

//定义客房链表结点结构
typedef struct HNode
	{
		char	roomN[7];	//客房名称
		float   Price;		//标准价格
		float   PriceL;	//入住价格(默认值=标准价格*80%)
		int	    Beds;		//床位数Beds
		char	State[5];	//入住状态(值域："空闲"、"入住"、"预订"，默认值为"空闲")
		struct HNode  *next;	//指针域
	}Hotel, *HLink;

void Build(HLink &H)
{
	HLink rear,p;
	FILE *fp;
	fp=fopen("indata.txt","r");
	H=(HLink)malloc(sizeof(HNode));
	rear=H;
	if(!fp)
	{
		printf("数据输入文件没有找到\n");
	}
	while(!feof(fp))
	{
		p=(HLink)malloc(sizeof(HNode));
		fscanf(fp,"%8s %f %d",p->roomN,&p->Price,&p->Beds);
		p->PriceL=0.8*p->Price;
		strcpy(p->State,"空闲");
		rear->next=p;
		rear=p;
	}
	rear->next=NULL;
	fclose(fp);
}

void Exp(HLink H)
{
	HLink p;
	p=H->next;
	if(!p)
	{
		printf("数据为空。\n");
		return;
	}
	printf("\n客房数据输出如下：\n");
	printf("客房名称  标准价格  入住价格  床位数  入住状态\n");
	while(p)
	{
		printf("%-11s%-10.1f%-11.1f%-8d%-8s\n",p->roomN,p->Price,p->PriceL,p->Beds,p->State);
		p=p->next;
	}
}

int Find(HLink &H, char *roomN)
{
	HLink p=H->next;
	int num=0;
	while(p)
	{
		num++;
		if(!strcmp(roomN,p->roomN))
		{
			printf("该客房的具体信息如下：\n");
			printf("客房名称  标准价格  入住价格  床位数  入住状态\n");
			printf("%-11s%-10.1f%-11.1f%-8d%-8s\n",p->roomN,p->Price,p->PriceL,p->Beds,p->State);
			return num;
		}
		p=p->next;
	}
	return 0;
}

void updateH(HLink &H, int beds, char *state)
{
	HLink p=H->next;
	while(p)
	{
		if(p->Beds==beds)
		{
			strcpy(p->State,state);
		}
		p=p->next;
	}
}

void Add(HLink &H)
{
	HLink p=H->next;
	while(p)
	{
		if(strcmp(p->State,"入住"))
		{
			p->PriceL*=1.2;
		 } 
		 p=p->next;
	}
}

HLink FirstH(HLink &H)
{
	float MaxPriceL=0;
	HLink p=H->next;//遍历的结点
	HLink pre=H;//记录遍历结点的前驱结点
	HLink pmax;//记录最大值，要清空的结点
	HLink q;//记录最大值的前驱结点
	while(p)
	{
		if(p->PriceL>=MaxPriceL)
		{
			q=pre;
			pmax=p;
		}
		p=p->next;
		pre=pre->next;
	}
	q->next=pmax->next;
	return pmax;	
}

void MoveK1(HLink &H, int k)
{
	HLink p1=H->next;
	HLink p2=H->next;
	HLink pre=H;
	for(int i=0;i<k;i++)//一直找到第k个结点 
	{
		if(!p1)
		{
			printf("对不起，该链表没有k个结点。\n");
			return;
		}
		p1=p1->next; 
	}
	 while(p1)
	 {
	 	p1=p1->next;
	 	p2=p2->next;//当p1到表尾时，p2为倒数第k个结点 
	 	pre=pre->next;
	 }
	 pre->next=p2->next;
	 p2->next=H->next;
	 H->next=p2;
}

void ReverseN2(HLink &H)
{
	HLink p1=H;
	HLink p2=H;
	
	while(p1)
	{
		if(p1->next)
		{
			p1=p1->next->next;
			p2=p2->next;
		}
		else
		{
			p1=p1->next;
		}
	 } 

	HLink mid=p2;//找到了中间的结点 
	p2=p2->next;
	HLink q=p2->next;
	p2->next=NULL; 
	while(q->next)//t为空 
	{
		HLink t=q->next;//保存临时结点
		q->next=p2;
		p2=q;
		q=t; 
	 }
	 q->next=p2; 
	 mid->next=q;
}



void SortPriceL(HLink &H)
{
	HLink q=H;
	HLink p=q->next->next;
	q->next->next=NULL;
	while(p)
	{ 
		while((q->next)&&p->PriceL>q->next->PriceL||( (q->next)&&p->PriceL==q->next->PriceL && strcmp(p->roomN,q->next->roomN)>0))
			q=q->next;
		HLink s=p->next;
		p->next=q->next;
		q->next=p;
		p=s;
		q=H;
		
	}

}
void upBed(HLink &H,int beds)
{
	HLink p;
	HLink q=(HLink)malloc(sizeof(HNode));//q是新建的结点 
	q->next=NULL;
	q->Beds=beds;
	printf("请输入您想要创建的客房的名称？\n");
	scanf("%s",q->roomN);
	printf("请输入您想要创建客房的标准价格为？\n");
	scanf("%f",&q->Price); 
	q->PriceL=q->Price*0.8;
	printf("请输入该新客房的入住状态（入住、空闲、预定）\n");
	scanf("%s",q->State); 
	
	//下面分割为2个链表
	//H1大于beds,H2小于等于beds
	HLink H1,H2; 
	HLink p1,p2;
	H1=H;
	H2=q;
	p1=H1,p2=H2;
	
	//开始遍历 
	p=H->next;
	while(p)
	{
		if(p->Beds>beds)
		{
			p1->next=p;
			p=p->next;
			p1=p1->next; 
			p1->next=NULL;
		}
	 	else
	 	{
			p2->next=p;
			p=p->next;
			p2=p2->next; 
			p2->next=NULL;
		 }
	}
	
	p1->next=H2;
	H=H1;	

}

	 


int main()
{
	HLink H;
	Build(H);
	int order;
	int beds;
	char state[5];
	while(1)
	{
		printf("\n\n\t\t\t欢迎进入客房信息管理系统。\n");
		printf("\t  *****************************************************\n");
		printf("\t\t  1.查看所有客房的信息。\n");
		printf("\t\t  2.查询特定客房名称的客房。\n");
		printf("\t\t  3.更改客房入住状态。\n");
		printf("\t\t  4.所有未入住客房加价百分之20。\n");
		printf("\t\t  5.查找入住价格最高的客房并清空该信息。\n");
		printf("\t\t  6.将第k个客房信息移到第一个。\n");
		printf("\t\t  7.将中间位置以后的客房信息倒置。\n");
		printf("\t\t  8.按照客房(入住价格，客房名称)升序排序。\n");
		printf("\t\t  9.创建新的客房信息。\n");
		printf("\t\t  0.退出系统。\n");
		printf("\t  ******************************************************\n");
		printf("请输入您的指令：\n");
		scanf("%d",&order);
		switch(order)
		{
			case 1:
				{
					Exp(H);
					break;
				}
			case 2:
				{
					char roomN[7];
					printf("请输入您要查找的客房名称:\n");
					scanf("%s",roomN);
					int pos=Find(H,roomN);
					if(pos>=1)
						printf("该客房的位置序号为%d\n",pos);
					else
						printf("对不起，没有找到该客房信息。\n");
					break;
				}
			case 3:
				{
					printf("请输入您要更改的入住客房信息的床位数。\n");
					scanf("%d",&beds);
					printf("请输入您想要更改成什么入住状态:\n");
					scanf("%s",state);
					updateH(H,beds,state);
					Exp(H);
					break;
				}
			case 4:
				{
					Add(H);
					Exp(H);
					break;
				}
			case 5:
				{
					HLink p=FirstH(H);
					printf("入住价格最高的客房的具体信息如下：\n");
					printf("客房名称  标准价格  入住价格  床位数  入住状态\n");
					printf("%-11s%-10.1f%-11.1f%-8d%-8s\n",p->roomN,p->Price,p->PriceL,p->Beds,p->State);
					Exp(H);
					break;
				}
			case 6:
				{
					int k;
					printf("请输入您想要把客房倒数第几个信息移到第一个信息：\n");
					scanf("%d",&k);
					MoveK1(H,k);
					Exp(H);
					break;
				}
			case 7:
				{
					ReverseN2(H);
					Exp(H);
					break;
				}
			case 8:
				{
					SortPriceL(H);
					HLink p=H->next;
					Exp(H);
					break;
				}
			case 9:
				{
					printf("请输入您想要增加一个床位数为多少的客房信息？\n");
					scanf("%d",&beds);
					upBed(H,beds); 
					Exp(H);
					break;
				}
			case 0:
				{
					exit(0);
			 	} 
			default:
				{
					printf("对不起，您输入的指令有误，请重新输入。\n");
					break;
				}
			}
		}	
	return 0;
}
