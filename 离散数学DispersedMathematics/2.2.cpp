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
                else
                    eval_stack.push(operand1 || operand2); 
            }
        }
    }
    return eval_stack.top(); 
}

int predicate_type(string formula)
{
    bool values1[] = {true, false};
    bool values2[] = {false, true};
    bool values3[] = {false, false};
    bool values4[] = {true, true};
    string postfix = to_postfix(formula);
    bool result1 = evaluate_postfix(postfix, values1);
    bool result2 = evaluate_postfix(postfix, values2);
    bool result3 = evaluate_postfix(postfix, values3);
    bool result4 = evaluate_postfix(postfix, values4);
    if (result1 && result2 && result3 && result4)
        return 1;
    else if (!result1 && !result2 && !result3 && result4)
        return 0;
    else
        return 2;
}

int main()
{
    string formula;
    cin >> formula;
    int type = predicate_type(formula);
    if (type == 0)
        cout << 0 << endl;
    else if (type == 1)
        cout << 1 << endl;
    else
        cout << 2 << endl;
    system("pause");
    return 0;
}
