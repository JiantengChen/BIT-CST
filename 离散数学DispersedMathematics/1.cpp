#include <iostream>
#include <cstdio>

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

Status GetTop(SqStack S, char &e)
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

void Convert(SqStack equation, char input[], char res[])
{
    int i = 0, count = 0;
    char ch, temp;
    ch = input[i];
    while (ch != '\0')
    {
        if (!(input[i] == '0' || input[i] == '1' || input[i] == '|' || input[i] == '*' || input[i] == '(' || input[i] == ')'))
            break;
        switch (input[i])
        {
        case '(':
            Push(equation, input[i]);
            break;
        case ')':
            while (GetTop(equation, temp) && temp != ')')
            {
                Pop(equation, temp);
                res[count++] = temp;
            }
            Pop(equation, temp);
            break;
        case '|':
            while (!StackEmpty(equation) && GetTop(equation, temp) && temp != '(')
            {
                Pop(equation, temp);
                res[count++] = temp;
            }
            Push(equation, input[i]);
            break;
        case '*':
            while (!StackEmpty(equation) && GetTop(equation, temp) && temp == '*')
            {
                Pop(equation, temp);
                res[count++] = temp;
            }
            Push(equation, input[i]);
            break;
        default:
            res[count++] = '\\';
            while (input[i] == '0' || input[i] == '1')
            {
                res[count++] = input[i];
                i++;
            }
            res[count++] = '\\';
            i--;
            break;
        }
        ch = input[i++];
    }
    while (!StackEmpty(equation))
    {
        Pop(equation, temp);
        res[count++] = temp;
    }
    res[count] = '\0';
}

int Calculate(SqStack equation, SqStack equation_num, char res[])
{
    char t0, t1, t2;
    // std::cout << res << std::endl;

    for (int i = 0; i < MAXSIZE; i++)
    {
        // std ::cout << i << ":" << res[i] << std::endl;
        char num[MAXSIZE];
        if (res[i] == '\0')
            return t0 - 48;
        if (res[i] == '\\' && res[i + 1] != '\\')
        {
            i++;
            while (1)
            {
                if (res[i] == '\\')
                    break;
                if (res[i] == '0' || res[i] == '1')
                {
                    // std::cout << i << ":" << res[i] << std::endl;
                    Push(equation_num, res[i]);
                }
                i++;
            }
        }
        else if (res[i] == '|' || res[i] == '*')
        {
            Pop(equation_num, t1);
            Pop(equation_num, t2);
            switch (res[i])
            {
            case '|':
                t0 = '0';
                if (t1 == '1' || t2 == '1')
                    t0 = '1';
                break;
            case '*':
                t0 = '1';
                if (t1 == '0' || t2 == '0')
                    t0 = '0';
                break;
            default:
                break;
            }
            Push(equation_num, t0);
        }
    }
    return t0 - 48;
}

int main(int argc, char const *argv[])
{
    SqStack equation, equation_num;
    char input[MAXSIZE], res[100];

    InitStack(equation);
    InitStack(equation_num);

    std::cin >> input; // (1*0)*(1|(0|0))|1
    Convert(equation, input, res);
    // std::cout << res << std::endl;
    int result = Calculate(equation, equation_num, res);
    std::cout << result << std::endl;

    system("pause");
    return 0;
}
