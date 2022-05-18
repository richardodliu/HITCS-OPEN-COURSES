#include <stdafx.h>
#include <stdio.h>
#include <iostream>   
#include <iomanip>  
#include <math.h>  
#include <string.h>  
#include <stack> 
#define MAX 100  

using namespace std;

/******************** Function Indentify Head File Start ****************************/

bool operator_priority(char temp_operator, char expression)
//若栈顶运算符temp_operator优先级比当前表达式的高，则返回true,否则返回false  
{
	if (temp_operator == '-' || temp_operator == '+')
	{
		if (expression == '-' || expression == '+'  || expression == '(' || expression == '#')
			return true;
		else if (expression == '/' || expression == '*' || expression == '^' )
			return false;
	}

	else if (temp_operator == '/' || temp_operator == '*')
	{
		if (expression == '-' || expression == '+' || expression == '/' || expression == '*' ||expression == '(' || expression == '#')
			return true;
		else if ( expression == '^' )
			return false;
	}

	else if (temp_operator == '(')
	{
		return false;
	}

	else if (temp_operator == ')')
		return true;

	else if (temp_operator == '#')
		return false;

	else if (temp_operator == '^')/////////  
	{
		return true;
	}
	else
		exit(233);
}

bool is_operator(char expression)
//判断expression是否为运算符，若是返回true，否则返回false  
{
	if (expression == '-' || expression == '+' || expression == '*' || expression == '/' || expression == ')' || expression == '(' || expression == '^' || expression == '#')
		return true;
	else return false;
}

bool is_number(char expression)
{
	if (expression <= '9'&&expression >= '0')
		return true;
	else
		return false;
}

bool is_letter(char expression)
{
	if ((expression >= 'a'&&expression <= 'z') || expression == '_')
		return true;
	else
		return false;
}


int len = 0, i = 0, now = 0;
char post[200];
//char str[200][200];
char RPN[200];
char expression[200];
stack<char> RPN_opr;

void mid_transform()
{
	scanf("%s", expression);
	strcat(expression, "#");
	RPN_opr.push('#');

	while (len < strlen(expression))
	{
		while (!is_operator(expression[len]) && len < strlen(expression))
		{
			//str[i][j] = expression[len];
			RPN[now] = expression[len];
			len++;
			now++;
		}
		RPN[now] = ' ';
		now++;

		if (expression[len] == '(' )
		{
			RPN_opr.push(expression[len]);
			len++;
		}
		else if (expression[len] == ')')
		{
			while (RPN_opr.top() != '(')
			{
				RPN[now] = RPN_opr.top();
				RPN_opr.pop();
				now++;
				RPN[now] = ' ';
				now++;
			}
			RPN_opr.pop();
			len++;
		}
		else
		{
			if (!operator_priority(RPN_opr.top(), expression[len]))
			{
				RPN_opr.push(expression[len]);
				len++;
			}
			else
			{
				while (operator_priority(RPN_opr.top(), expression[len]))
				{
					RPN[now] = RPN_opr.top();
					RPN_opr.pop();
					now++;
					RPN[now] = ' ';
					now++;
				}

				RPN_opr.push(expression[len]);
				len++;
			}
		}



	}

	while (RPN_opr.top() != '#')
	{
		RPN[now] = RPN_opr.top();
		RPN_opr.pop();
		now++;
		RPN[now] = ' ';
		now++;
	}


}

double Caculate(double variable)
{
	stack<double> storage;
	len = strlen(RPN);
	i = 0;
	int j;
	double number;

	while (i < len)
	{
		if (RPN[i] == ' ')
		{
			i++;
			continue;
		}
			
		if (is_number(RPN[i]))
		{
			number = 0;
			while (is_number(RPN[i]))
			{
				number = number * 10 + RPN[i] - '0';
				i++;
			}
			storage.push(number);
		}

		if (is_letter(RPN[i]))
		{
			char func[200] = { 0 };
			j = 0;
			while (is_letter(RPN[i]))
			{
				func[j] = RPN[i];
				j++; i++;
			}

			number = 0;
			if (strcmp(func, "x")==0)number = variable;
			else if (strcmp(func, "fabs_x") == 0)number = fabs(variable);
			else if (strcmp(func, "cos_x") == 0)number = cos(variable);
			else if (strcmp(func, "sin_x") == 0)number = sin(variable);
			else if (strcmp(func, "tan_x") == 0)number = tan(variable);
			else if (strcmp(func, "asin_x") == 0)number = asin(variable);
			else if (strcmp(func, "acos_x") == 0)number = acos(variable);
			else if (strcmp(func, "atan_x") == 0)number = atan(variable);
			//  else if(strcmp(func, "atan2_x")==0)number=atan2(1,2);  
			else if (strcmp(func, "sinh_x") == 0)number = sinh(variable);
			else if (strcmp(func, "cosh_x") == 0)number = cosh(variable);
			else if (strcmp(func, "tanh_x") == 0)number = tanh(variable);
			else if (strcmp(func, "exp_x") == 0)number = exp(variable);
			else if (strcmp(func, "floor_x") == 0)number = floor(variable);
			//  else if(strcmp(func, "fmod_x")==0)number=fmod(5,3);  
			else if (strcmp(func, "log_x") == 0)number = log(variable);
			//  else if(strcmp(func, "log10_x")==0)number=log10(105);  
			else
			{
				cout << "Error:Function Not Support" << endl;
				getchar(); getchar();
				exit(3);
			}

			storage.push(number);
		}

		if (is_operator(RPN[i]))
		{
			double number1, number2;
			number2 = storage.top();
			storage.pop();
			number1 = storage.top();
			storage.pop();

			switch (RPN[i])
			{
				case '+':number1 += number2; break;
				case '-':number1 -= number2; break;
				case '*':number1 *= number2; break;
				case '/':number1 /= number2; break;
				case '^':number1 = pow(number1, number2); break;
			}
			storage.push(number1);
			i++;
		}
	}

	if (storage.size() == 1)
	{
		return storage.top();
	}
	else
	{
		cout << "Error: Reverse Polish Nonation Illegal." << endl;
		getchar(); getchar();
		exit(1);
	}

}

void menu()
//输出提示并调用相关函数进行计算  
{
	int i;
	cout << "*****************************************************************" << endl;
	cout << "Please input the  function(care for the format):" << endl;

	len = 0;
	mid_transform();
	cout << "followings is the infix of the  function:" << endl;
	for (i = 0; i<strlen(expression)-1; i++)
	{
		if (expression[i] != ' ')
			cout << expression[i];
	}

	cout << endl << "followings is the suffix of the  function:" << endl;
	printf("%s\n", RPN);
	cout << endl << "*****************************************************************" << endl;
}

/*********  Head File Test Function  **********
int main()
{
	while(1)
	{
		menu();
		cout << Caculate(7) << endl;
		getchar();
	}

return 0;
}
/*********  Head File Test Function End  ***********/

/************Function Indentify Head File End*************************/

//Caculating 
//测试实例  
//      sin(x)*dx|0——PI=2  

#define PI 3.141592653  
double x0 = 0;
double x1 = PI;/////////////////赋初值  

double inc;/////////////////表示小区间长度  
double sum[MAX];////////////表示积分结果  
double e[MAX];//////////////记录积分误差  
int nun_interval[MAX];////////记录区间个数  
int num_f[MAX];//////////记录对应函数值的个数  
int choice;//表示是进行课本函数积分的验证，还是通过输入函数进行识别  

void print(int num)
//以固定格式输出  
{
	int i;

	/////////////////输出测试实例的结果,带误差的比较  
	if (1 == choice)
	{
		for (i = 0; i<num; i++)
		{
			e[i] = sum[i] - 2;
		}
		for (i = 0; i<num - 1; i++)
		{
			cout << setw(15) << nun_interval[i] << setw(15) << num_f[i] << setw(20) << sum[i] - 2.0 << setw(20) << e[i + 1] / e[i] << endl;
		}
		cout << setw(15) << nun_interval[i] << setw(15) << num_f[i] << setw(20) << sum[i] - 2.0 << setw(20) << endl;
	}

	/////////////////输出输出随机函数的结果,由于不知道精确值，所以不带误差的比较  
	else if (2 == choice)
	{
		for (i = 0; i<num - 1; i++)
		{
			cout << setw(15) << nun_interval[i] << setw(15) << num_f[i] << setw(20) << sum[i] << endl;
		}
		cout << setw(15) << nun_interval[i] << setw(15) << num_f[i] << setw(20) << sum[i] << endl;
	}
}

double Constant_rule()
//Constant rule确定小区间面积  
{
	int j;
	if (1 == choice)
		cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Constant rule" << setw(20) << "e[2*n]/e[n]" << endl;
	else cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Result of Constant rule " << endl;

	///////反复进行，逐步将区间长度减小，逐步逼近精确值  
	for (j = 0; j<20; j++)
	{
		nun_interval[j] = (int)pow(2, j);
		sum[j] = 0;
		inc = (x1 - x0) / nun_interval[j];
		int i = 0;
		////利用递推法求当前区间分法的积分值sum[j]  
		while (i<nun_interval[j])
		{
			if (2 == choice)sum[j] += inc*Caculate(x0 + i*inc);
			else sum[j] += inc*sin(x0 + i*inc);
			i++;
		}
		num_f[j] = nun_interval[j] + 1;
		
	}
	print(j);
	return sum[j - 1];
}

double Trapezium_rule()
//Trapezium rule确定小区间面积  
{
	int j;
	if (1 == choice)
		cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Trapezium rule" << setw(20) << "e[2*n]/e[n]" << endl;
	else cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Result of Trapezium rule " << endl;

	///////反复进行，逐步将区间长度减小，逐步逼近精确值  
	for (j = 0; j<20; j++)
	{
		nun_interval[j] = (int)pow(2, j);
		sum[j] = 0;
		inc = (x1 - x0) / nun_interval[j];
		int i = 0;

		////利用递推法求当前区间分法的积分值sum[j]  
		while (i<nun_interval[j])
		{
			if (2 == choice)sum[j] += inc*(Caculate(x0 + i*inc) + Caculate(x0 + (i + 1)*inc)) / 2.0;
			else sum[j] += inc*(sin(x0 + i*inc) + sin(x0 + (i + 1)*inc)) / 2.0;
			i++;
		}
		num_f[j] = nun_interval[j] + 1;
	}
	print(j);
	return sum[j - 1];
}

double Mid_point_rule()
//Mid_point rule确定小区间面积  
{
	int j;
	if (1 == choice)
		cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Mid_point rule" << setw(20) << "e[2*n]/e[n]" << endl;
	else cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Result of Mid_point rule " << endl;

	///////反复进行，逐步将区间长度减小，逐步逼近精确值  
	for (j = 0; j<20; j++)
	{
		nun_interval[j] = (int)pow(2, j);
		sum[j] = 0;
		inc = (x1 - x0) / nun_interval[j];
		int i = 0;

		////利用递推法求当前区间分法的积分值sum[j]  
		while (i<nun_interval[j])
		{
			if (2 == choice)sum[j] += inc* (Caculate((x0 + i*inc + x0 + (i + 1)*inc) / 2.0));
			else sum[j] += inc* (sin((x0 + i*inc + x0 + (i + 1)*inc) / 2.0));
			i++;
		}
		num_f[j] = nun_interval[j];
	}
	print(j);
	return sum[j - 1];
}

double Simpson_rule()
//Simpson's_rule()确定小区间面积  
{
	int j;
	if (1 == choice)
		cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Simpson's rule" << setw(20) << "e[2*n]/e[n]" << endl;
	else cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Result of Simpson's rule " << endl;

	///////反复进行，逐步将区间长度减小，逐步逼近精确值  
	for (j = 0; j<11; j++)
	{
		nun_interval[j] = (int)pow(2, j);
		sum[j] = 0;
		inc = (x1 - x0) / nun_interval[j];
		int i = 0;

		////利用递推法求当前区间分法的积分值sum[j]  
		while (j != 0 & i<nun_interval[j])
		{
			if (2 == choice)sum[j - 1] += inc / 3.0 *(Caculate(x0 + i*inc) + 4 * Caculate(x0 + (i + 1)*inc) + Caculate(x0 + (i + 2)*inc));
			else sum[j - 1] += inc / 3.0 *(sin(x0 + i*inc) + 4 * sin(x0 + (i + 1)*inc) + sin(x0 + (i + 2)*inc));
			i = i + 2;
		}
		num_f[j] = nun_interval[j] * 2 + 1;
	}
	print(j - 1);
	return sum[j - 2];
}


double Gauss_quadrature()
//Gauss_quadrature()确定小区间面积  
{
	int j;
	if (1 == choice)
		cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Gauss quadrature" << setw(20) << "e[2*n]/e[n]" << endl;
	else cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Result of Gauss quadrature " << endl;

	///////反复进行，逐步将区间长度减小，逐步逼近精确值  
	for (j = 0; j<10; j++)
	{
		nun_interval[j] = (int)pow(2, j);
		sum[j] = 0;
		inc = (x1 - x0) / nun_interval[j];
		int i = 0;

		////利用递推法求当前区间分法的积分值sum[j]  
		while (i<nun_interval[j])
		{
			if (2 == choice)sum[j] += inc / 2.0 * (Caculate(x0 + inc*i + (1.0 / 2.0 - sqrt(3.0) / 6.0)*inc) + Caculate(x0 + inc*i + (1.0 / 2.0 + sqrt(3.0) / 6.0)*inc));
			else sum[j] += inc / 2.0 * (sin(x0 + inc*i + (1.0 / 2.0 - sqrt(3.0) / 6.0)*inc) + sin(x0 + inc*i + (1.0 / 2.0 + sqrt(3.0) / 6.0)*inc));
			i++;
		}
		num_f[j] = nun_interval[j] * 2;
	}
	print(j);
	return sum[j - 1];
}

double Gauss_quadrature_three_point()
//Gauss_quadrature_three_point()确定小区间面积  
{
	int j;
	if (1 == choice)
		cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Gauss quadrature three point" << setw(20) << "e[2*n]/e[n]" << endl;
	else cout << setw(15) << "No.interval" << setw(15) << "No.f(x)" << setw(20) << "Result of Gauss quadrature three point " << endl;

	///////反复进行，逐步将区间长度减小，逐步逼近精确值  
	for (j = 0; j<10; j++)
	{
		nun_interval[j] = (int)pow(2, j);
		sum[j] = 0;
		inc = (x1 - x0) / nun_interval[j];
		num_f[j] = 3 * nun_interval[j];
		int i = 0;

		////利用递推法求当前区间分法的积分值sum[j]  
		while (j != 0 && i<nun_interval[j])
		{
			if (2 == choice)sum[j - 1] += inc / 9.0 * (8 * Caculate(x0 + inc + inc*i) + 5 * Caculate(x0 + inc + inc*i - sqrt(3.0 / 5.0)*inc) + 5 * Caculate(x0 + inc + inc*i + sqrt(3.0 / 5.0)*inc));
			else sum[j - 1] += inc / 9.0 * (8 * sin(x0 + inc + inc*i) + 5 * sin(x0 + inc + inc*i - sqrt(3.0 / 5.0)*inc) + 5 * sin(x0 + inc + inc*i + sqrt(3.0 / 5.0)*inc));
			i = i + 2;
		}
		//sum[j]/=2;  
	}
		print(j - 1);
	return sum[j - 2];
}


int main()
{

	while (1)
	{
		/////////////////////////////////根据菜单提示进行相应操作///////////////////////////////  
		int flag = 0;
		do
		{
			if (flag)cout << "Your choice is illegal,please choose again!" << endl;
			cout << "============================menu================================" << endl;
			cout << "              1.Integral verification on the books" << endl;
			cout << "              2.Input new function and do numerical integration" << endl;
			cout << "              3.Quits the program" << endl;
			cout << "Please choose [ ]\b\b";
			cin >> choice;
			getchar();
			cout << "================================================================" << endl << endl;
			flag++;
		} while (choice != 1 && choice != 2 && choice != 3);
		if (2 == choice)
		{
			menu();
			cout << endl << "Please input interval [x0,x1]:";
			cin >> x0 >> x1;
			cout << "followings is the result of the intigration:" << endl << endl;
		}
		else if (3 == choice)
			exit(0);

		double result;
		cout << "*********here is the result of Constant rule***********" << endl;
		result = Constant_rule();
		cout << "result of Constant rule:" << result << endl << endl;

		cout << "*********here is the result of Trapezium rule***********" << endl;
		result = Trapezium_rule();
		cout << "result of Trapezium rule:" << result << endl << endl;

		cout << "*********here is the result of Mid point rule***********" << endl;
		result = Mid_point_rule();
		cout << "result of Mid point rule:" << result << endl << endl;

		cout << "*********here is the result of Simpson rule***********" << endl;
		result = Simpson_rule();
		cout << "result of Simpson rule:" << result << endl << endl;

		cout << "*********here is the result of Gauss quadrature*********" << endl;
		result = Gauss_quadrature();
		cout << "result of Gauss quadrature:" << result << endl << endl;

		cout << "*********here is the result of Gauss quadrature three point**********" << endl;
		result = Gauss_quadrature_three_point();
		cout << "result of Gauss quadrature three point:" << result << endl << endl;
	}
	return 0;
}

