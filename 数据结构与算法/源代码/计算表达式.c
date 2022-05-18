#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define  maxlen 100
typedef struct STACK_CHAR
{
	int charnum;
	char element[maxlen];
} STACK_CHAR;
STACK_CHAR ops;
typedef struct STACK_NUM
{
	int numsnum;
	double element[maxlen];
} STACK_NUM;
STACK_NUM nums;
char mid[100], end[100];//存放中缀算术表达式和后缀表达式
//函数功能：置操作符栈为空
void emptySTACK_CHAR(STACK_CHAR *ch);
//函数功能：置操作数栈为空
void emptySTACK_NUM(STACK_NUM *num);
//函数功能：判断操作符栈是否为空
int isemptySTACK_CHAR(STACK_CHAR ch);
//函数功能：判断操作数栈是否为空
int isemptySTACK_NUM(STACK_NUM num);
//函数功能：得到当前操作符栈栈顶元素
char gettopChar(STACK_CHAR ch);
//函数功能：得到当前操作数栈栈顶元素
double gettopNum(STACK_NUM num);
//函数功能：弹出操作符栈栈顶元素
void popSTACK_CHAR(STACK_CHAR *ch);
//函数功能：弹出操作数栈栈顶元素
void popSTACK_NUM(STACK_NUM *num);
//函数功能：往操作符栈压入一个操作符
void pushSTACK_CHAR(STACK_CHAR *ch, char x);
//函数功能：往操作数栈压入一个操作数
void pushSTACK_NUM(STACK_NUM *num, double x);
//函数功能：进行优先级查表
int pre_judge(char x);
//函数功能：中缀表达式转后缀表达式
void midtoend(int n);
//函数功能：计算后缀表达式的值（实数方式）
double calculate(int n);
int main()
{
	int i,n;
	emptySTACK_CHAR(&ops);
	emptySTACK_NUM(&nums);
	printf("请输入指令(0或1):");
	scanf("%d",&n);
	while(n==1) {
	printf("你输入的中缀表达式为：\n");
	scanf("%s",mid);
	midtoend(maxlen);
	printf("转换之后的后缀表达式为：\n");
	for (i = 0; end[i] != '\0'; i++)
	{
		if (end[i] == '$')//把作为负号标记的$恢复为负号
			printf("-");
		else
			printf("%c", end[i]);
	}
	printf("\n");
	printf("后缀表达式的计算结果为：%g\n", calculate(maxlen));
	printf("请输入指令(0或1)");
	scanf("%d",&n);
	};
	return 0;
}
void emptySTACK_CHAR(STACK_CHAR *ch)
{
	ch->charnum = maxlen;
	return;
}
void emptySTACK_NUM(STACK_NUM *num)
{
	num->numsnum = maxlen;
	return;
}
int isemptySTACK_CHAR(STACK_CHAR ch)
{
	if (ch.charnum == maxlen)
		return 1;
	return 0;
}
int isemptySTACK_NUM(STACK_NUM num)
{
	if (num.numsnum == maxlen)
		return 1;
	return 0;
}
char gettopChar(STACK_CHAR ch)
{
	if (isemptySTACK_CHAR(ch))
		return '\0';
	return ch.element[ch.charnum];
}
double gettopNum(STACK_NUM num)
{
	if (isemptySTACK_NUM(num))
		return 0;
	return num.element[num.numsnum];
}
void popSTACK_CHAR(STACK_CHAR *ch)
{
	int i;
	if (isemptySTACK_CHAR(*ch))
	{
		printf("当前操作符栈为空！\n");
	}
	else
	{
		ch->charnum += 1;
		printf("操作符栈中的元素有：");
		for (i = ch->charnum; i <= maxlen - 1; i++)
		{
			printf(" %c ", ch->element[i]);
		}
		printf("\n");
	}
	return;
}
void popSTACK_NUM(STACK_NUM *num)
{
	int i;
	if (isemptySTACK_NUM(*num))
	{
		printf("当前操作数栈为空！\n");
	}
	else
	{
		num->numsnum += 1;
		printf("操作数栈中的元素有：");
		for (i = num->numsnum; i <= maxlen - 1; i++)
		{
			printf(" %g ", num->element[i]);
		}
		printf("\n");
	}
	return;
}
void pushSTACK_CHAR(STACK_CHAR *ch, char x)
{
	int i;
	if (ch->charnum == 0)
	{
		printf("当前操作符栈已满！\n");
		return;
	}
	else
	{
		ch->charnum -= 1;
		ch->element[ch->charnum] = x;
		printf("操作符栈中的元素有：");
		for (i = ch->charnum; i <= maxlen - 1; i++)
		{
			printf(" %c ", ch->element[i]);
		}
		printf("\n");
	}
	return;
}
void pushSTACK_NUM(STACK_NUM *num, double x)
{
	int i;
	if (num->numsnum == 0)
	{
		printf("当前操作数栈已满！\n");
		return;
	}
	else
	{
		num->numsnum -= 1;
		num->element[num->numsnum] = x;
		printf("操作数栈中的元素有：");
		for (i = num->numsnum; i <= maxlen - 1; i++)
		{
			printf(" %g ", num->element[i]);
		}
		printf("\n");
	}
	return;
}
int pre_judge(char x)//相当于查优先级表
{
	int pre = 0;
	switch (x)
	{
	case'(':pre = 1;//括号优先级
		break;
	case')':pre = 1;
		break;
	case'+':pre = 2;//加减优先级
		break;
	case'-':pre = 2;
		break;
	case'*':pre = 3;//乘除优先级
		break;
	case'/':pre = 3;
		break;
    case'%':pre = 3;
        break;
	default:
		break;
	}
	return pre;
}
void midtoend(int n)
{
	int endnum = 0, i, isminus = 0;
	if (mid[0] == '-')//判断首位的负号（不能做减号处理）
	{
		end[0] = '$';//记负号为$
		isminus = 1;//从第一项（负号之后）开始向后扫描
		endnum++;
	}
	for (i = isminus; mid[i] != '\0'; i++)
	{
		if (isdigit(mid[i]) && !isdigit(mid[i + 1]) && mid[i + 1] != '.')//当前字符是数字的最后一位
		{
			end[endnum] = mid[i];
			endnum++;
			end[endnum] = ' ';
			endnum++;
		}
		else if ((isdigit(mid[i]) && (isdigit(mid[i + 1]) || mid[i + 1] == '.')) || mid[i] == '.')//当前字符是数字的中间某位
		{
			end[endnum] = mid[i];
			endnum++;
		}
		else if (mid[i - 1] == '(' && mid[i] == '-')//处理左括号右边的负号
		{
			end[endnum] = '$';
			endnum++;
		}
		else if (mid[i - 1] != '(' && (mid[i] == '+' || mid[i] == '-' || mid[i] == '*' || mid[i] == '/' || mid[i] == '%'))//处理运算符
		{
			while (isemptySTACK_CHAR(ops) == 0)
			{
				//若栈顶操作符优先级高，则将栈顶操作符依次退栈并输出，直到满足要求为止
				if (pre_judge(gettopChar(ops)) >= pre_judge(mid[i]))
				{
					end[endnum] = gettopChar(ops);
					popSTACK_CHAR(&ops);
					endnum++;
					end[endnum] = ' ';
					endnum++;
				}
				else break;
			}
			pushSTACK_CHAR(&ops, mid[i]);//到满足要求后，运算符压入栈
		}
		else if (mid[i] == '(')//遇到“（”进栈
			pushSTACK_CHAR(&ops, mid[i]);
		else if (mid[i] == ')')//当遇到“）”时，退栈输出直到“（”为止
		{
			while (true)
			{
				if (gettopChar(ops) == '(')
				{
					popSTACK_CHAR(&ops);
					break;
				}
				else
				{
					end[endnum] = gettopChar(ops);
					popSTACK_CHAR(&ops);
					endnum++;
					end[endnum] = ' ';
					endnum++;
				}
			}
		}
		else continue;
	}
	while (isemptySTACK_CHAR(ops) == 0)
	{
		end[endnum] = gettopChar(ops);
		popSTACK_CHAR(&ops);
		endnum++;
		end[endnum] = ' ';
		endnum++;
	}
	end[endnum] = '\0';
	return;
}
double calculate(int n)
{
	double temp1, temp2, numdou;
	int i, j=0, k, l, isminus = 0;
	char numchar[100];
	for (i = 0; end[i] != '\0'; i++)
	{
		if (end[i] == '$')//扫过被标记的负号
		{
			isminus = 1;
			j = i + 1;
		}
		if (end[i] == ' '&&isdigit(end[i - 1]))//截取字符串中的数字并通过atof函数转成double类型
		{
			for (k = j, l = 0; k <= i; k++, l++)
				numchar[l] = end[k];
			numdou = atof(numchar);
			if (isminus == 1)
			{
				numdou = -numdou;
				isminus = 0;
			}
			pushSTACK_NUM(&nums, numdou);
			memset(numchar, '\0', sizeof(numchar));
			numdou = 0;
		}
		else if (((end[i - 1] == ' ' || end[i - 1] == '$')&&isdigit(end[i])) || (i==0 && isdigit(end[i]))) //碰到了数字的第一位
			j = i;
		else if (end[i] == '+' || end[i] == '-' || end[i] == '*' || end[i] == '/'|| end[i] == '%')
		{
			temp1 = gettopNum(nums);
			popSTACK_NUM(&nums);
			temp2 = gettopNum(nums);
			popSTACK_NUM(&nums);
			switch (end[i])
			{
			case'+':
				temp2 += temp1;
				break;
			case'-':
				temp2 -= temp1;
				break;
			case'*':
				temp2 *= temp1;
				break;
			case'/':
				temp2 /= temp1;
				break;
            case'%':
				while(temp2>temp1)
                {
                    temp2 -= temp1;
                }
				break;
			default:
				break;
			}
			pushSTACK_NUM(&nums, temp2);
		}
		else continue;
	}
	return gettopNum(nums);
}
