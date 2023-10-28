#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool is_operator(char c)
{
    return (c == '*' || c == '|' || c == '-');
}

int precedence(char c)
{
    if (c == '-')
        return 3;
    else if (c == '*')
        return 2;
    else if (c == '|')
        return 1;
    else
        return 0;
}

string to_postfix(string infix)
{
    stack<char> op_stack;
    string postfix = "";
    for (int i = 0; i < infix.length(); i++)
    {
        char c = infix[i];
        if (isalpha(c))
            postfix += c;
        else if (is_operator(c))
        {
            while (!op_stack.empty() && precedence(op_stack.top()) >= precedence(c))
            {
                postfix += op_stack.top();
                op_stack.pop();
            }
            op_stack.push(c);
        }
        else if (c == '(')
            op_stack.push(c);
        else if (c == ')')
        {
            while (op_stack.top() != '(')
            {
                postfix += op_stack.top();
                op_stack.pop();
            }
            op_stack.pop();
        }
    }
    while (!op_stack.empty())
    {
        postfix += op_stack.top();
        op_stack.pop();
    }
    return postfix;
}

bool evaluate_postfix(string postfix, bool values[])
{
    stack<bool> eval_stack;
    for (int i = 0; i < postfix.length(); i++)
    {
        char c = postfix[i];
        if (isalpha(c))
        {
            int index = c - 'P';
            eval_stack.push(values[index]);
        }
        else if (is_operator(c))
        {
            bool operand2 = eval_stack.top();
            eval_stack.pop();
            if (c == '-')
                eval_stack.push(!operand2);
            else
            {
                bool operand1 = eval_stack.top();
                eval_stack.pop();
                if (c == '*')
                    eval_stack.push(operand1 && operand2);
                else if (c == '|')
                    eval_stack.push(operand1 || operand2);
            }
        }
    }
    return eval_stack.top();
}

int main()
{
    string formula;
    cin >> formula;
    string postfix = to_postfix(formula);
    bool values0[2] = {true, true};
    bool values1[2] = {false, false};
    bool values2[2] = {true, false};
    bool values3[2] = {false, true};
    bool result1, result2, result3, result4;
    result1 = evaluate_postfix(postfix, values0);
    result2 = evaluate_postfix(postfix, values1);
    result3 = evaluate_postfix(postfix, values2);
    result4 = evaluate_postfix(postfix, values3);
    if (result1 && result2 && result3 && result4)
        cout << "1" << endl;
    else if (!result1 && !result2 && !result3 && result4)
        cout << "0" << endl;
    else
        cout << "2" << endl;
    system("pause");
    return 0;
}
