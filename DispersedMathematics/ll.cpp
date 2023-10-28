#include <stdio.h>
#include <string.h>
#include <iostream>
#define T 1
#define F 0

struct Stack
{
	int top;
	char arr[80];
} number = {-1}, symbol = {-1};
int var[26];	 // 记录变元元素和个数
int num_var = 0; // 记录变元的个数
int alphabet_true_false[26];
int enum_result[80];
char str_copy[80]; // 输入的字符串的副本
void count_var_num(char str[])
{ // 记录变元的个数,用全局变量num储存
	int i, len = strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			if (var[str[i] - 'A'] == 0)
			{
				var[str[i] - 'A'] = 1;
				++num_var;
			}
		}
	}
}

void string_in(char str[])
{
	int i;
	gets(str);
	strcpy(str_copy, str);
	count_var_num(str); // 记录变元的个数,用全局变量num储存
	int len = strlen(str);
	for (i = 0; i < len; i++)
	{
		switch (str[i])
		{
		case '-':
			str[i] = ')' + 5;
			break;
		case '*':
			str[i] = ')' + 4;
			break;
		case '|':
			str[i] = ')' + 3;
			break;
		case '>':
			str[i] = ')' + 2;
			break;
		case '=':
			str[i] = ')' + 1;
			break;
		}
	}
}
void reverse_polish(char s[])
{
	int i, len = strlen(s);
	for (i = 0; i < len; i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{ // 如果是命题变元就直接入number栈
			number.arr[++number.top] = s[i];
		}
		else if (s[i] > ')' && s[i] <= 5 + ')')
		{
			if (symbol.top == -1 || symbol.arr[symbol.top] == ')')
			{
				++symbol.top;
				symbol.arr[symbol.top] = s[i];
			}
			else if (s[i] >= symbol.arr[symbol.top])
			{
				++symbol.top;
				symbol.arr[symbol.top] = s[i];
			}
			else
			{
				while (symbol.top != -1 && s[i] < symbol.arr[symbol.top])
				{
					++number.top;
					number.arr[number.top] = symbol.arr[symbol.top];
					--symbol.top;
				}
				--i;
			}
		}
		else if (s[i] == '(' || s[i] == ')')
		{
			if (s[i] == '(')
			{
				++symbol.top;
				symbol.arr[symbol.top] = s[i];
			}
			else
			{
				while (symbol.arr[symbol.top] != '(')
				{
					++number.top;
					number.arr[number.top] = symbol.arr[symbol.top];
					--symbol.top;
				}
				if (symbol.top != -1)
					--symbol.top;
			}
		}
	}
	while (symbol.top != -1)
	{
		++number.top;
		number.arr[number.top] = symbol.arr[symbol.top];
		--symbol.top;
	}
}

int check(int num_var)
{ // 判断enum_result[]的二进制情况组成的是极小值(return 1)还是极大值(return 0)
	struct Stack ans = {-1};
	int i, k = 0, len = 0, temp;
	for (i = 0; i < 26; i++)
	{
		if (var[i])
		{
			++len;
			alphabet_true_false[i] = enum_result[k++]; // enum_result里只有真或假（1，0）
			// 这一步类似于变元p被赋值为false(0)
			// 或者t被赋值为true(1)
		}
	}
	for (i = 0; i <= number.top; i++)
	{
		if (number.arr[i] >= 'A' && number.arr[i] <= 'Z')
		{
			++ans.top;
			ans.arr[ans.top] = alphabet_true_false[number.arr[i] - 'A'];
		}
		else
		{
			switch (number.arr[i])
			{
			case '.':
				ans.arr[ans.top] = !ans.arr[ans.top];
				break;
			case '-':
				ans.arr[ans.top - 1] = ans.arr[ans.top - 1] & ans.arr[ans.top];
				--ans.top;
				break;
			case ',':
				ans.arr[ans.top - 1] = ans.arr[ans.top - 1] | ans.arr[ans.top];
				--ans.top;
				break;
			case '+':
				ans.arr[ans.top - 1] = !ans.arr[ans.top - 1] | ans.arr[ans.top];
				--ans.top;
				break;
			case '*':
				ans.arr[ans.top - 1] =
					(!ans.arr[ans.top - 1] | ans.arr[ans.top]) & (!ans.arr[ans.top] | ans.arr[ans.top - 1]);
				--ans.top;
				break;
			}
		}
	}
	// printf("%4d\n",ans.arr[0]);
	return ans.arr[0];
}

void binary_enumeration(int num_var)
{
	int i, j;
	int conjunction_top = -1, disjunction_top = -1;
	int result_conjunction[80] = {0}; // 储存的是主合取结果
	int result_disjunction[80] = {0}; // 储存的是主析取结果
	for (i = 0; i < (1 << num_var); i++)
	{ //
		memset(enum_result, 0, num_var);
		for (j = 0; j < num_var; j++)
		{ // 这一层的循环说白了就是把变量j的值转换为对应的二进制，并把二进制值储存到enum_result数组里
			if (i & (1 << (num_var - j - 1)))
			{
				enum_result[j] = T;
			}
			else
			{
				enum_result[j] = F;
			}
		}
		if (check(num_var))
		{
			result_disjunction[++disjunction_top] = i; // 主析取十进制下标
		}
		else
		{
			result_conjunction[++conjunction_top] = i; // 主合取十进制下标
		}
	}
	if (disjunction_top == -1)
	{
		printf("0\n");
	}
	else if (conjunction_top == -1)
	{
		printf("1\n");
	}
	else
	{
		printf("2\n");
	}
}
int main()
{
	int i = 0;
	char str[80];
	string_in(str);				 // 输入小写字符
	reverse_polish(str);		 // 逆波兰表达式 去括号
	binary_enumeration(num_var); // 把变元个数num传入函数
	system("pause");
	return 0;
}
