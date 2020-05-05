#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>

//����ͷ�������ṹ
typedef struct HNode
	{
		char	roomN[7];	//�ͷ�����
		float   Price;		//��׼�۸�
		float   PriceL;	//��ס�۸�(Ĭ��ֵ=��׼�۸�*80%)
		int	    Beds;		//��λ��Beds
		char	State[5];	//��ס״̬(ֵ��"����"��"��ס"��"Ԥ��"��Ĭ��ֵΪ"����")
		struct HNode  *next;	//ָ����
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
		printf("���������ļ�û���ҵ�\n");
	}
	while(!feof(fp))
	{
		p=(HLink)malloc(sizeof(HNode));
		fscanf(fp,"%8s %f %d",p->roomN,&p->Price,&p->Beds);
		p->PriceL=0.8*p->Price;
		strcpy(p->State,"����");
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
		printf("����Ϊ�ա�\n");
		return;
	}
	printf("\n�ͷ�����������£�\n");
	printf("�ͷ�����  ��׼�۸�  ��ס�۸�  ��λ��  ��ס״̬\n");
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
			printf("�ÿͷ��ľ�����Ϣ���£�\n");
			printf("�ͷ�����  ��׼�۸�  ��ס�۸�  ��λ��  ��ס״̬\n");
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
		if(strcmp(p->State,"��ס"))
		{
			p->PriceL*=1.2;
		 } 
		 p=p->next;
	}
}

HLink FirstH(HLink &H)
{
	float MaxPriceL=0;
	HLink p=H->next;//�����Ľ��
	HLink pre=H;//��¼��������ǰ�����
	HLink pmax;//��¼���ֵ��Ҫ��յĽ��
	HLink q;//��¼���ֵ��ǰ�����
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
	for(int i=0;i<k;i++)//һֱ�ҵ���k����� 
	{
		if(!p1)
		{
			printf("�Բ��𣬸�����û��k����㡣\n");
			return;
		}
		p1=p1->next; 
	}
	 while(p1)
	 {
	 	p1=p1->next;
	 	p2=p2->next;//��p1����βʱ��p2Ϊ������k����� 
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

	HLink mid=p2;//�ҵ����м�Ľ�� 
	p2=p2->next;
	HLink q=p2->next;
	p2->next=NULL; 
	while(q->next)//tΪ�� 
	{
		HLink t=q->next;//������ʱ���
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
	HLink q=(HLink)malloc(sizeof(HNode));//q���½��Ľ�� 
	q->next=NULL;
	q->Beds=beds;
	printf("����������Ҫ�����Ŀͷ������ƣ�\n");
	scanf("%s",q->roomN);
	printf("����������Ҫ�����ͷ��ı�׼�۸�Ϊ��\n");
	scanf("%f",&q->Price); 
	q->PriceL=q->Price*0.8;
	printf("��������¿ͷ�����ס״̬����ס�����С�Ԥ����\n");
	scanf("%s",q->State); 
	
	//����ָ�Ϊ2������
	//H1����beds,H2С�ڵ���beds
	HLink H1,H2; 
	HLink p1,p2;
	H1=H;
	H2=q;
	p1=H1,p2=H2;
	
	//��ʼ���� 
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
		printf("\n\n\t\t\t��ӭ����ͷ���Ϣ����ϵͳ��\n");
		printf("\t  *****************************************************\n");
		printf("\t\t  1.�鿴���пͷ�����Ϣ��\n");
		printf("\t\t  2.��ѯ�ض��ͷ����ƵĿͷ���\n");
		printf("\t\t  3.���Ŀͷ���ס״̬��\n");
		printf("\t\t  4.����δ��ס�ͷ��Ӽ۰ٷ�֮20��\n");
		printf("\t\t  5.������ס�۸���ߵĿͷ�����ո���Ϣ��\n");
		printf("\t\t  6.����k���ͷ���Ϣ�Ƶ���һ����\n");
		printf("\t\t  7.���м�λ���Ժ�Ŀͷ���Ϣ���á�\n");
		printf("\t\t  8.���տͷ�(��ס�۸񣬿ͷ�����)��������\n");
		printf("\t\t  9.�����µĿͷ���Ϣ��\n");
		printf("\t\t  0.�˳�ϵͳ��\n");
		printf("\t  ******************************************************\n");
		printf("����������ָ�\n");
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
					printf("��������Ҫ���ҵĿͷ�����:\n");
					scanf("%s",roomN);
					int pos=Find(H,roomN);
					if(pos>=1)
						printf("�ÿͷ���λ�����Ϊ%d\n",pos);
					else
						printf("�Բ���û���ҵ��ÿͷ���Ϣ��\n");
					break;
				}
			case 3:
				{
					printf("��������Ҫ���ĵ���ס�ͷ���Ϣ�Ĵ�λ����\n");
					scanf("%d",&beds);
					printf("����������Ҫ���ĳ�ʲô��ס״̬:\n");
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
					printf("��ס�۸���ߵĿͷ��ľ�����Ϣ���£�\n");
					printf("�ͷ�����  ��׼�۸�  ��ס�۸�  ��λ��  ��ס״̬\n");
					printf("%-11s%-10.1f%-11.1f%-8d%-8s\n",p->roomN,p->Price,p->PriceL,p->Beds,p->State);
					Exp(H);
					break;
				}
			case 6:
				{
					int k;
					printf("����������Ҫ�ѿͷ������ڼ�����Ϣ�Ƶ���һ����Ϣ��\n");
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
					printf("����������Ҫ����һ����λ��Ϊ���ٵĿͷ���Ϣ��\n");
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
					printf("�Բ����������ָ���������������롣\n");
					break;
				}
			}
		}	
	return 0;
}
