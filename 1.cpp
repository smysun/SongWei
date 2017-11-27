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
	//����һ����ջS
	S.base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;//����׺Ͷ�����򷵻�OK
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}



char Push(SqStack &S, char e) {
	//Ԫ��e��ջ
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
	//ջ��Ԫ�س�ջ����ֵ��e
	if (S.top == S.base)	return ERROR;
	e = *--S.top;
	return OK;
}



char GetTop(SqStack S) {
	//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK,���򷵻�ERROR
	char e;
	if (S.top == S.base)	return ERROR;
	e = *(S.top - 1);
	return e;
}
bool empty(SqStack S) {
	if (S.base==S.top)
		return true;
	return false;
}//�ж�ջ�ǲ���Ϊ��
bool judge(char x) {
	//�ж�x�Ƿ�Ϊ����
	if (x > '0'&&x < '9')
		return true;
	return false;
}
int priority(char x) {
	//�ж���������ȼ�
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
	InitStack(OPTR);//��������ջһ��������ŷ��ţ�һ�������������
	InitStack(OPND);
	int a, b;
	int e = 0;
	for (int i = 0; i < s.size(); i++) {//������ַ�����ʽ�����з����������֣�������Ҫ�ѷ��Žṹ������ת��
		if (judge(s[i])) {
			int Temp = 0;
			string temp;
			temp += s[i];
			while (judge(s[++i]))
				temp += s[i];
			for (int j = 0; j < temp.size(); j++)
				Temp = Temp * 10 + temp[j] - 48;
			Push(OPND, Temp);
		}//���ַ�����ת��Ϊ��������
		if (!judge(s[i])) {
			if (empty(OPTR))//�������������OPTR����ַ���ջΪ��
				Push(OPTR, s[i]);//����ջ�ĵ�һ������Ϊ"#"
			else {
				
				if (priority(s[i]) > priority(GetTop(OPTR)) || s[i] == '(') {//�����ǰ��ջ�ķ������ȼ�����ջ�ڷ������ȼ�
					Push(OPTR, s[i]);//�������ȼ��������ջ
				}
				else {
					while (priority(s[i]) <= priority(GetTop(OPTR)) ){
						if (GetTop(OPTR) == '#'&&s[i] == '#') {
							int answer;
							int e=0;
							Pop(OPTR, e);
							answer = GetTop(OPND);
							cout << endl << "����" << answer << endl;
							Pop(OPND, e);
							return 0;
						}
						else if (GetTop(OPTR) == '('&&s[i] == ')') //��ջ���������ţ�������������ʱ�����������ţ�ɾ��������
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
						
					}//�����ȼ��ߵ������ʵ�ּ���
					Push(OPTR, s[i]);//���ڵ�top=='#'ʱ�򣬽����һ���������ջ
				}
			}
		}
	}
	return OK;
}
int main()
{
	string expression;
	cout << "����һ����'#'��Ϊ��ͷ�ͽ�β����ʽ:" << endl;
	cin >> expression;
	Calculate(expression);
	system("pause");
	return 0;
}
