#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc, char const *argv[])
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    int l = s1.length();
    for (int i = 0; i < l; i++)
    {
        if (s1 == s2)
        {
            cout << "���ַ�����ѭ��ƥ��" << endl;
            system("pause");
            return 0;
        }
        // ͨ�����ַ���s1�����ַ��ƶ����ַ���β�����жϵ�����ѭ�������ﵽs1����ʱ��ѭ��ֹͣ
        string tmp = "";
        for (int j = 1; j < l; j++)
            tmp += s1[j];
        tmp += s1[0];
        s1 = tmp;
    }
    cout << "���ַ�������ѭ��ƥ��" << endl;
    system("pause");
    return 0;
}
