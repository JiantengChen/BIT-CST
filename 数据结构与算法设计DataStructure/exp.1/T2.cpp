#include <iostream>
#include <cstdio>

using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int Status;
typedef int SElemType;

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

Status InitStack(SqStack &S)
{
    S.base = new SElemType[MAXSIZE];
    if (!S.base)
        return OVERFLOW;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}

Status Push(SqStack &S, char e)
{
    if (S.top - S.base == S.stacksize)
        return ERROR;
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S, char &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}

Status Pop_num(SqStack &S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}

Status GetTop(SqStack S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}

Status GetTop_char(SqStack S, char &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}

bool StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return true;
    else
        return false;
}

void Converter(SqStack S_sign, char input[], char re[])
{
    bool sign_condition;
    int i = 0, count = 0;
    char ch, temp;
    ch = input[i];
    while (ch != '\0')
    {
        sign_condition = input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '(' || input[i] == ')' || input[i] == '^';
        if (!(sign_condition || (input[i] >= '0' && input[i] <= '9')))
            break;
        switch (input[i])
        {
        case '(':
            Push(S_sign, input[i]);
            break;
        case ')':
            while (GetTop_char(S_sign, temp) && temp != '(')
            {
                Pop(S_sign, temp);
                re[count++] = temp;
            }
            Pop(S_sign, temp);
            break;
        case '+':
        case '-':
            while (!StackEmpty(S_sign) && GetTop_char(S_sign, temp) && temp != '(')
            {
                Pop(S_sign, temp);
                re[count++] = temp;
            }
            Push(S_sign, input[i]);
            break;
        case '*':
        case '/':
            while (!StackEmpty(S_sign) && GetTop_char(S_sign, temp) && temp == '/' || temp == '*' || temp == '^')
            {
                Pop(S_sign, temp);
                re[count++] = temp;
            }
        case '^':
            while (!StackEmpty(S_sign) && GetTop_char(S_sign, temp) && temp == '^')
            {
                Pop(S_sign, temp);
                re[count++] = temp;
            }
            Push(S_sign, input[i]);
            break;
        case ' ':
            break;
        default:
            re[count++] = '\\';
            while (input[i] >= '0' && input[i] <= '9')
            {
                re[count++] = input[i];
                i++;
            }
            re[count++] = '\\';
            i--;
            break;
        }
        ch = input[i++];
    }
    while (!StackEmpty(S_sign))
    {
        Pop(S_sign, temp);
        re[count++] = temp;
    }
    re[count] = '\0';
}

int ResultCal(SqStack S_sign, SqStack S_num, char re[])
{
    int temp1, temp2, temp0;
    for (int i = 0; i < MAXSIZE; i++)
    {
        int tempnum[MAXSIZE], temp = 0;
        bool sign_condition = re[i] == '+' || re[i] == '-' || re[i] == '*' || re[i] == '/' || re[i] == '(' || re[i] == ')' || re[i] == '^';
        if (re[i] == '\0')
            return temp0;
        if (re[i] == '\\' && re[i + 1] != '\\')
        {
            i++;
            int count = 0;
            while (1)
            {
                if (re[i] == '\\')
                    break;
                if (re[i] <= '9' && re[i] >= '0')
                {
                    Push(S_num, re[i] - 48);
                    count++;
                }
                i++;
            }
            if (count > 1)
            {
                for (int j = 0; j < count; j++)
                {
                    Pop_num(S_num, tempnum[j]);
                    temp += re[i - count + j] - 48;
                    temp *= 10;
                }
                temp /= 10;
                Push(S_num, temp);
            }
        }
        else if (sign_condition)
        {
            Pop_num(S_num, temp1);
            Pop_num(S_num, temp2);
            switch (re[i])
            {
            case '+':
                temp0 = temp1 + temp2;
                break;
            case '-':
                temp0 = temp2 - temp1;
                break;
            case '*':
                temp0 = temp2 * temp1;
                break;
            case '/':
                temp0 = temp2 / temp1;
                break;
            case '^':
                temp0 = 1;
                for (int j = 0; j < temp1; j++)
                {
                    temp0 *= temp2;
                }
                break;
            default:
                break;
            }
            Push(S_num, temp0);
        }
    }
    return temp0;
}

int legalExpression(char input[])
{

    for (int i = 0; i < MAXSIZE; i++)
    {
        if (input[i] == '\0' || input[i] == ' ' || input[i] == '\n')
            return 1;
        if (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != '^' && input[i] != '(' && input[i] != ')' && input[i] != '0' && input[i] != '1' && input[i] != '2' && input[i] != '3' && input[i] != '4' && input[i] != '5' && input[i] != '6' && input[i] != '7' && input[i] != '8' && input[i] != '9')
            return 0;
    }
    return 1;
}

void inputExpression(char input[])
{
    do
    {
        cout << "请输入表达式：" << endl;
        cin >> input;
        if (legalExpression(input))
            break;
        else
            cout << "输入表达式含有非法字符或为小数，请重新输入" << endl;
    } while (1);
}

int main()
{
    SqStack S_sign, S_num;
    InitStack(S_sign);
    InitStack(S_num);
    char input[MAXSIZE], re[MAXSIZE];
    while (1)
    {
        inputExpression(input);
        Converter(S_sign, input, re);
        cout<<re<<endl;
        cout << "Result: " << ResultCal(S_sign, S_num, re) << endl;
    }
    system("pause");
    return 0;
}
