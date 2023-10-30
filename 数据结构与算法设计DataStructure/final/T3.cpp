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
            cout << "两字符串可循环匹配" << endl;
            system("pause");
            return 0;
        }
        // 通过将字符串s1的首字符移动到字符串尾进行判断当，当循环次数达到s1长度时，循环停止
        string tmp = "";
        for (int j = 1; j < l; j++)
            tmp += s1[j];
        tmp += s1[0];
        s1 = tmp;
    }
    cout << "两字符串不可循环匹配" << endl;
    system("pause");
    return 0;
}
