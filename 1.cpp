#include <iostream>
#include <math.h>
#include <Windows.h>
#include <string>
using namespace std;
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
typedef struct {
	char *base;
	char *top;
	int stacksize;
}SqStack;


int InitStack(SqStack &S) {
	//构造一个空栈S
	S.base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;//如果底和顶相等则返回OK
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}



char Push(SqStack &S, char e) {
	//元素e入栈
	if (S.top - S.base >= S.stacksize) {
		S.base = (char*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(char));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}



char Pop(SqStack &S, int e) {
	//栈顶元素出栈，赋值给e
	if (S.top == S.base)	return ERROR;
	e = *--S.top;
	return OK;
}



char GetTop(SqStack S) {
	//若栈不空，则用e返回S的栈顶元素，并返回OK,否则返回ERROR
	char e;
	if (S.top == S.base)	return ERROR;
	e = *(S.top - 1);
	return e;
}
bool empty(SqStack S) {
	if (S.base==S.top)
		return true;
	return false;
}//判断栈是不是为空
bool judge(char x) {
	//判断x是否为数字
	if (x > '0'&&x < '9')
		return true;
	return false;
}
int priority(char x) {
	//判断运算符优先级
	if (x == '+' || x == '-')
		return 0;
	else if (x == '*' || x == '/')
		return 1;
	else if (x == '(' || x == ')')
		return -1;
	else if (x == '#')
		return -2;
	return -3;
}
int Calculate(string s) {
	SqStack OPTR, OPND;
	InitStack(OPTR);//设立两个栈一个用来存放符号，一个用来存放数据
	InitStack(OPND);
	int a, b;
	int e = 0;
	for (int i = 0; i < s.size(); i++) {//输入的字符串形式，既有符号又有数字，所以需要把符号结构的数字转化
		if (judge(s[i])) {
			int Temp = 0;
			string temp;
			temp += s[i];
			while (judge(s[++i]))
				temp += s[i];
			for (int j = 0; j < temp.size(); j++)
				Temp = Temp * 10 + temp[j] - 48;
			Push(OPND, Temp);
		}//将字符数字转化为整形数字
		if (!judge(s[i])) {
			if (empty(OPTR))//如果不是数字且OPTR存放字符的栈为空
				Push(OPTR, s[i]);//则入栈的第一个符号为"#"
			else {
				
				if (priority(s[i]) > priority(GetTop(OPTR)) || s[i] == '(') {//如果当前入栈的符号优先级大于栈内符号优先级
					Push(OPTR, s[i]);//将高优先级运算符入栈
				}
				else {
					while (priority(s[i]) <= priority(GetTop(OPTR)) ){
						if (GetTop(OPTR) == '#'&&s[i] == '#') {
							int answer;
							int e=0;
							Pop(OPTR, e);
							answer = GetTop(OPND);
							cout << endl << "答案是" << answer << endl;
							Pop(OPND, e);
							return 0;
						}
						else if (GetTop(OPTR) == '('&&s[i] == ')') //入栈的是左括号，右左括号相遇时，跳过右括号，删除左括号
							++i;
						else {
							int e=0;
							a = GetTop(OPND);
							Pop(OPND, e);
							b = GetTop(OPND);
							Pop(OPND, e);
						}
						if (GetTop(OPTR) == '+') {
							b += a;
							Push(OPND, b);
						}
						else if (GetTop(OPTR) == '-') {
							b -= a;
							Push(OPND, b);
						}
						else if (GetTop(OPTR) == '*') {
							b *= a;
							Push(OPND, b);
						}
						else if (GetTop(OPTR) == '/') {
							b /= a;
							Push(OPND, b);
						}
						char e = 0;
						Pop(OPTR, e);
						
					}//将优先级高的运算符实现计算
					Push(OPTR, s[i]);//用于当top=='#'时候，将最后一个运算符入栈
				}
			}
		}
	}
	return OK;
}
int main()
{
	string expression;
	cout << "输入一个用'#'作为开头和结尾的算式:" << endl;
	cin >> expression;
	Calculate(expression);
	system("pause");
	return 0;
}
