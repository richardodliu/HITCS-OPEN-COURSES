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
char mid[100], end[100];//�����׺�������ʽ�ͺ�׺���ʽ
//�������ܣ��ò�����ջΪ��
void emptySTACK_CHAR(STACK_CHAR *ch);
//�������ܣ��ò�����ջΪ��
void emptySTACK_NUM(STACK_NUM *num);
//�������ܣ��жϲ�����ջ�Ƿ�Ϊ��
int isemptySTACK_CHAR(STACK_CHAR ch);
//�������ܣ��жϲ�����ջ�Ƿ�Ϊ��
int isemptySTACK_NUM(STACK_NUM num);
//�������ܣ��õ���ǰ������ջջ��Ԫ��
char gettopChar(STACK_CHAR ch);
//�������ܣ��õ���ǰ������ջջ��Ԫ��
double gettopNum(STACK_NUM num);
//�������ܣ�����������ջջ��Ԫ��
void popSTACK_CHAR(STACK_CHAR *ch);
//�������ܣ�����������ջջ��Ԫ��
void popSTACK_NUM(STACK_NUM *num);
//�������ܣ���������ջѹ��һ��������
void pushSTACK_CHAR(STACK_CHAR *ch, char x);
//�������ܣ���������ջѹ��һ��������
void pushSTACK_NUM(STACK_NUM *num, double x);
//�������ܣ��������ȼ����
int pre_judge(char x);
//�������ܣ���׺���ʽת��׺���ʽ
void midtoend(int n);
//�������ܣ������׺���ʽ��ֵ��ʵ����ʽ��
double calculate(int n);
int main()
{
	int i,n;
	emptySTACK_CHAR(&ops);
	emptySTACK_NUM(&nums);
	printf("������ָ��(0��1):");
	scanf("%d",&n);
	while(n==1) {
	printf("���������׺���ʽΪ��\n");
	scanf("%s",mid);
	midtoend(maxlen);
	printf("ת��֮��ĺ�׺���ʽΪ��\n");
	for (i = 0; end[i] != '\0'; i++)
	{
		if (end[i] == '$')//����Ϊ���ű�ǵ�$�ָ�Ϊ����
			printf("-");
		else
			printf("%c", end[i]);
	}
	printf("\n");
	printf("��׺���ʽ�ļ�����Ϊ��%g\n", calculate(maxlen));
	printf("������ָ��(0��1)");
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
		printf("��ǰ������ջΪ�գ�\n");
	}
	else
	{
		ch->charnum += 1;
		printf("������ջ�е�Ԫ���У�");
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
		printf("��ǰ������ջΪ�գ�\n");
	}
	else
	{
		num->numsnum += 1;
		printf("������ջ�е�Ԫ���У�");
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
		printf("��ǰ������ջ������\n");
		return;
	}
	else
	{
		ch->charnum -= 1;
		ch->element[ch->charnum] = x;
		printf("������ջ�е�Ԫ���У�");
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
		printf("��ǰ������ջ������\n");
		return;
	}
	else
	{
		num->numsnum -= 1;
		num->element[num->numsnum] = x;
		printf("������ջ�е�Ԫ���У�");
		for (i = num->numsnum; i <= maxlen - 1; i++)
		{
			printf(" %g ", num->element[i]);
		}
		printf("\n");
	}
	return;
}
int pre_judge(char x)//�൱�ڲ����ȼ���
{
	int pre = 0;
	switch (x)
	{
	case'(':pre = 1;//�������ȼ�
		break;
	case')':pre = 1;
		break;
	case'+':pre = 2;//�Ӽ����ȼ�
		break;
	case'-':pre = 2;
		break;
	case'*':pre = 3;//�˳����ȼ�
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
	if (mid[0] == '-')//�ж���λ�ĸ��ţ����������Ŵ���
	{
		end[0] = '$';//�Ǹ���Ϊ$
		isminus = 1;//�ӵ�һ�����֮�󣩿�ʼ���ɨ��
		endnum++;
	}
	for (i = isminus; mid[i] != '\0'; i++)
	{
		if (isdigit(mid[i]) && !isdigit(mid[i + 1]) && mid[i + 1] != '.')//��ǰ�ַ������ֵ����һλ
		{
			end[endnum] = mid[i];
			endnum++;
			end[endnum] = ' ';
			endnum++;
		}
		else if ((isdigit(mid[i]) && (isdigit(mid[i + 1]) || mid[i + 1] == '.')) || mid[i] == '.')//��ǰ�ַ������ֵ��м�ĳλ
		{
			end[endnum] = mid[i];
			endnum++;
		}
		else if (mid[i - 1] == '(' && mid[i] == '-')//�����������ұߵĸ���
		{
			end[endnum] = '$';
			endnum++;
		}
		else if (mid[i - 1] != '(' && (mid[i] == '+' || mid[i] == '-' || mid[i] == '*' || mid[i] == '/' || mid[i] == '%'))//���������
		{
			while (isemptySTACK_CHAR(ops) == 0)
			{
				//��ջ�����������ȼ��ߣ���ջ��������������ջ�������ֱ������Ҫ��Ϊֹ
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
			pushSTACK_CHAR(&ops, mid[i]);//������Ҫ��������ѹ��ջ
		}
		else if (mid[i] == '(')//������������ջ
			pushSTACK_CHAR(&ops, mid[i]);
		else if (mid[i] == ')')//������������ʱ����ջ���ֱ��������Ϊֹ
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
		if (end[i] == '$')//ɨ������ǵĸ���
		{
			isminus = 1;
			j = i + 1;
		}
		if (end[i] == ' '&&isdigit(end[i - 1]))//��ȡ�ַ����е����ֲ�ͨ��atof����ת��double����
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
		else if (((end[i - 1] == ' ' || end[i - 1] == '$')&&isdigit(end[i])) || (i==0 && isdigit(end[i]))) //���������ֵĵ�һλ
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
