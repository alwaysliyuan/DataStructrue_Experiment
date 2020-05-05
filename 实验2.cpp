#include<stdio.h>
//ebababababcaababababcabadaaaac
 //babababcabad
#include<string.h>

typedef struct {
	int length;
	char ch[200];
}SString;

	SString S,T;
	
int Index_BF(SString S,SString T,int pos);
int Index_KMP(SString S,SString T,int pos,int next[]);
void get_next(SString T,int next[]);
void get_nextval(SString T,int nextval[]);


int Index_BF(SString S,SString T,int pos){
//����ģʽT������S�е�pos���ַ���ʼ��һ�γ��ֵ�λ�á��������ڣ��򷵻�ֵΪ0
	int i=pos;
	int j=1;
	int flag=1;
	int cnt1=1;
	int cnt2=0;//ͳ��ÿ���ַ��Ƚϴ���
	int cnt3=0;//�ַ�����ȫ���Ƚϴ���
	printf("������:   ");
	for(int k=0;k<S.length;k++)
	{
		printf("%c ",S.ch[k]);
	 }
	while(i<=S.length &&j<=T.length)
	{
		if(flag)
		{
			printf("\n");
			printf("��%d��ƥ��:",cnt1);
			for(int k=1;k<i;k++)
			{
				printf("  ");
			}
			flag=0;
			cnt2=0;
		}
		cnt2++;
		printf("%c ",T.ch[j-1]);
		if(S.ch[i-1]==T.ch[j-1])
		{
			++i;
			++j;
		}
		else
		{
			cnt1++;
			flag=1;
			i=i-j+2;
			j=1;
		}
		if(flag ||j>T.length)
		{
			printf("\t\tÿһ���ַ��ıȽϴ���Ϊ%d",cnt2);
		}
		cnt3+=cnt2;
	}
	printf("\nһ��������%d��ƥ��,�ܹ�ƥ����%d���ַ�\n",cnt1,cnt3);
	if(j>T.length)//ƥ��ɹ�
	{
		return i-T.length;
	}
	else
		return 0;
	}

int Index_KMP(SString S,SString T,int pos,int next[])
{
	int i=pos;
	int j=1;
	int flag=0;//��δ�ɹ����һ��ƥ��
	int cnt1=0;//ƥ������
	int cnt2=0;//ÿһ���ַ���ƥ����
	int cnt3=0;//�ַ������ܹ�ƥ�����
	int ii,jj;//��¼δ�ı�� i,j
	printf("\n������:     ");
	for(int k=0;k<S.length;k++)
		printf("%c ",S.ch[k]);
	printf("\n");

	while(i<=S.length &&j<=T.length)
	{
		cnt2++;
		if(j==0|| S.ch[i-1]==T.ch[j-1])
		{
			if(j==0)
			{
				cnt2--;
			 }
			++i;
			++j;
			if(j>T.length)
			{
				flag=1;
				cnt1++;
				jj=j-1;
				ii=i-1;
			}
		}
		else
		{
			flag=1;
			cnt1++;
			ii=i;
			jj=j;
			j=next[j];
		}
		if(flag)
		{
			flag=0;
			printf("��%2d��ƥ�䣺",cnt1);
			if(cnt1==0)
			{
				for(int k=1;k<pos;k++)//ǰ��Ŀո�
				{
					printf("  ");
				}
				for( k=0;k<jj;k++)
				{
					printf("%c ",T.ch[k]);
				}
			}
			else
			{
				for(int k=1;k<2*(ii-jj);k++)//ǰ��Ŀո�
				{
				printf(" ");
				}
				if(jj>cnt2)
					printf("(");
				else
					printf(" ");
				for( k=0;k<jj;k++)
				{
					printf("%c%c",T.ch[k],k==(jj-cnt2-1)?')':' ');
				}
			}
			printf("\t\t��һ�˹�ƥ����%d���ַ�\n",cnt2);
			cnt3+=cnt2;
			cnt2=0;
		 }
	}
	printf("\nһ��������%d��ƥ��,�ܹ�ƥ����%d���ַ�\n",cnt1,cnt3);

	if(j>T.length)
	{
		return i-T.length;
	}
	else
		return 0;
}

void get_next(SString T,int next[])
{
	int i=1;
	next[1]=0;
	int j=0;
	while(i<T.length)
	{
		if(j==0 || T.ch[i-1]==T.ch[j-1])
		{
			++i;
			++j;
			next[i]=j;
		}
		else
		{
			j=next[j];
		}
	}
	printf("ģʽ����    ");
	for(int k=0;k<T.length;k++)
	{
		printf("%c ",T.ch[k]);
	}
	printf("\n");
	printf("Next[j]��   ");
	for(k=1;k<=T.length;k++)
	{
		printf("%d ",next[k]);
	}
	printf("\n");
}



void get_nextval(SString T,int nextval[])
{
	int i=1,j=0;
	nextval[1]=0;
	while(i<T.length)
	{
		if(j==0 ||T.ch[i-1]==T.ch[j-1])
		{
			++i;
			++j;
			if(T.ch[i-1]!=T.ch[j-1])
				nextval[i]=j;
			else
				nextval[i]=nextval[j];
		}
		else
		{
			j=nextval[j];
		}
	}
	printf("ģʽ����    ");
	for(int k=0;k<T.length;k++)
	{
		printf("%c ",T.ch[k]);
	}
	printf("\n");
	printf("NextVal[j]��");
	for( k=1;k<=T.length;k++)
	{
		printf("%d ",nextval[k]);
	}
	printf("\n");
 }


int main()
{
	int order;
	int pos;
	int next[201];
	int nextval[201];
	while(1)
	{
		printf("\n\t\t1.�����������ִ���ƥ����ʼλ�á�\n");
		printf("\t\t2.���ص�ģʽƥ���㷨��\n");
		printf("\t\t3.KMP�㷨��\n");
		printf("\t\t4.KMP�Ľ��㷨��\n");
		printf("\t\t0.�˳�����ϵͳ��\n");
		printf("������ָ�\n");
		scanf("%d",&order);
		switch(order)
		{
			case 0:
				return 0;

			case 1:
			{
				printf("������������\n");
				scanf("%s",S.ch);
				S.length=strlen(S.ch);
				while(S.length>200)
				{
					printf("�Բ��������ĳ��ȳ���200������������������\n");
					scanf("%s",S.ch);
					S.length=strlen(S.ch);
				 }
				printf("�������Ӵ���\n");
				scanf("%s",T.ch);
				T.length=strlen(T.ch);
				while(T.length>200)
				{
					printf("�Բ����Ӵ��ĳ��ȳ���200�������������Ӵ���\n");
					scanf("%s",T.ch);
					S.length=strlen(T.ch);
				 }
				printf("������ģʽƥ��λ�á�\n");
				scanf("%d",&pos);

				break;
			}
			case 2:
			{
				int ans=Index_BF(S,T,pos);
				if(!ans)
					printf("�Բ���û��ƥ��ɹ�\n");
				else
					printf("ƥ��ɹ���λ����%d\n\n",ans);
				break;
			}
			case 3:
			{
				get_next(T,next);
				int ans=Index_KMP(S,T,pos,next);
				if(!ans)
					printf("�Բ���û��ƥ��ɹ�\n");
				else
					printf("ƥ��ɹ���λ����%d\n\n",ans);
				break;
			}
			case 4:
			{
				get_nextval(T,nextval);
				int ans=Index_KMP(S,T,pos,nextval);
				if(!ans)
					printf("�Բ���û��ƥ��ɹ�\n");
				else
					printf("ƥ��ɹ���λ����%d\n\n",ans);
				break;
			}
			default:
					printf("�Բ�������ָ������������������롣\n\n");
					break;
		 }
	}
	return 0; 
}
