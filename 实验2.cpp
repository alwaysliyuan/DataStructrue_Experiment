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
//返回模式T在主串S中第pos个字符开始第一次出现的位置。若不存在，则返回值为0
	int i=pos;
	int j=1;
	int flag=1;
	int cnt1=1;
	int cnt2=0;//统计每趟字符比较次数
	int cnt3=0;//字符串的全部比较次数
	printf("主串是:   ");
	for(int k=0;k<S.length;k++)
	{
		printf("%c ",S.ch[k]);
	 }
	while(i<=S.length &&j<=T.length)
	{
		if(flag)
		{
			printf("\n");
			printf("第%d趟匹配:",cnt1);
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
			printf("\t\t每一趟字符的比较次数为%d",cnt2);
		}
		cnt3+=cnt2;
	}
	printf("\n一共进行了%d次匹配,总共匹配了%d个字符\n",cnt1,cnt3);
	if(j>T.length)//匹配成功
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
	int flag=0;//还未成功完成一次匹配
	int cnt1=0;//匹配趟数
	int cnt2=0;//每一趟字符的匹配数
	int cnt3=0;//字符串的总共匹配次数
	int ii,jj;//记录未改变的 i,j
	printf("\n主串是:     ");
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
			printf("第%2d次匹配：",cnt1);
			if(cnt1==0)
			{
				for(int k=1;k<pos;k++)//前面的空格
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
				for(int k=1;k<2*(ii-jj);k++)//前面的空格
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
			printf("\t\t这一趟共匹配了%d个字符\n",cnt2);
			cnt3+=cnt2;
			cnt2=0;
		 }
	}
	printf("\n一共进行了%d次匹配,总共匹配了%d个字符\n",cnt1,cnt3);

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
	printf("模式串：    ");
	for(int k=0;k<T.length;k++)
	{
		printf("%c ",T.ch[k]);
	}
	printf("\n");
	printf("Next[j]：   ");
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
	printf("模式串：    ");
	for(int k=0;k<T.length;k++)
	{
		printf("%c ",T.ch[k]);
	}
	printf("\n");
	printf("NextVal[j]：");
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
		printf("\n\t\t1.输入主串、字串和匹配起始位置。\n");
		printf("\t\t2.朴素的模式匹配算法。\n");
		printf("\t\t3.KMP算法。\n");
		printf("\t\t4.KMP改进算法。\n");
		printf("\t\t0.退出管理系统。\n");
		printf("请输入指令：\n");
		scanf("%d",&order);
		switch(order)
		{
			case 0:
				return 0;

			case 1:
			{
				printf("请输入主串。\n");
				scanf("%s",S.ch);
				S.length=strlen(S.ch);
				while(S.length>200)
				{
					printf("对不起，主串的长度超过200，请重新输入主串。\n");
					scanf("%s",S.ch);
					S.length=strlen(S.ch);
				 }
				printf("请输入子串。\n");
				scanf("%s",T.ch);
				T.length=strlen(T.ch);
				while(T.length>200)
				{
					printf("对不起，子串的长度超过200，请重新输入子串。\n");
					scanf("%s",T.ch);
					S.length=strlen(T.ch);
				 }
				printf("请输入模式匹配位置。\n");
				scanf("%d",&pos);

				break;
			}
			case 2:
			{
				int ans=Index_BF(S,T,pos);
				if(!ans)
					printf("对不起，没有匹配成功\n");
				else
					printf("匹配成功的位置是%d\n\n",ans);
				break;
			}
			case 3:
			{
				get_next(T,next);
				int ans=Index_KMP(S,T,pos,next);
				if(!ans)
					printf("对不起，没有匹配成功\n");
				else
					printf("匹配成功的位置是%d\n\n",ans);
				break;
			}
			case 4:
			{
				get_nextval(T,nextval);
				int ans=Index_KMP(S,T,pos,nextval);
				if(!ans)
					printf("对不起，没有匹配成功\n");
				else
					printf("匹配成功的位置是%d\n\n",ans);
				break;
			}
			default:
					printf("对不起，您的指令输入错误，请重新输入。\n\n");
					break;
		 }
	}
	return 0; 
}
