#include <cstring>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
#define MAXLEN 255

void get_nextval(char T[], int nextval[])
{
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i < T[0])
        if (j == 0 || T[i] == T[j])
        {
            ++i;
            ++j;
            if (T[i] != T[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
}

int Index_KMP(char S[], char T[], int pos, int next[])
{
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0])
        if (
            j == 0 || S[i] == T[j])
        {
            ++i;
            ++j;
        }
        else

            j = next[j];
    if (j > T[0])

        return i - T[0];
    else
        return 0;
}

int main()
{
    char S[MAXLEN + 1], T[MAXLEN + 1];
    char S1[MAXLEN], S2[MAXLEN];
    cin >> S1 >> S2;
    strcpy(&S[1], S1);
    strcpy(&T[1], S2);
    S[0] = strlen(S1);
    T[0] = strlen(S2);
    int *p = new int[T[0] + 1];
    get_nextval(T, p);
    cout << Index_KMP(S, T, 1, p)<<endl;
    system("pause");
    return 0;
}