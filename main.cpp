#include <iostream>
#include "BigNum.h"
using namespace std;
int main()
{
    cout << "大数计算：" << endl;
    cout << "1.+\n2.-\n3.*\n4./\n5.退出" << endl;
    cout << "请输入命令序号：";
    int order;
    do
    {
        cin >> order;
        if (!(order >= 1 && order <= 5))
        {
            cout << "请输入正确的命令" << endl;
        }
    } while (!(order >= 1 && order <= 5));
    string numstr1, numstr2;
    switch (order)
    {
    case 1:
    {
        cout << "请输入两个大数(运算符号无需输入,以空格隔开)" << endl;
        do
        {
            cin >> numstr1 >> numstr2;
            if (!(numtell(numstr1) && numtell(numstr2)))
            {
                cout << "请输入正确数字" << endl;
            }
        } while (!(numtell(numstr1) && numtell(numstr2)));

        Add(numstr1, numstr2); //本来想构造一个返回字符串的函数，但操作时还需要开辟动态内存，
                               //否则无法实现数的传递，比较麻烦就换成了void函数在函数内就完成输出功能，后面设计的也是如此
        cout << endl;
        break;
    }
    case 2:
    {
        cout << "请输入两个大数(运算符号无需输入,以空格隔开)" << endl;
        do
        {
            cin >> numstr1 >> numstr2;
            if (!(numtell(numstr1) && numtell(numstr2)))
            {
                cout << "请输入正确数字" << endl;
            }
        } while (!(numtell(numstr1) && numtell(numstr2)));
        Sub(numstr1, numstr2);
        break;
    }
    case 3:
    {
        cout << "请输入两个大数(运算符号无需输入,以空格隔开)" << endl;
        do
        {
            cin >> numstr1 >> numstr2;
            if (!(numtell(numstr1) && numtell(numstr2)))
            {
                cout << "请输入正确数字" << endl;
            }
        } while (!(numtell(numstr1) && numtell(numstr2)));
        Mul(numstr1, numstr2);
        break;
    }
    case 4:
    {
        cout << "请输入两个大数(运算符号无需输入,以空格隔开)" << endl;
        do
        {
            cin >> numstr1 >> numstr2;
            if (!(numtell(numstr1) && numtell(numstr2)))
            {
                cout << "请输入正确数字" << endl;
            }
        } while (!(numtell(numstr1) && numtell(numstr2)));
        Div(numstr1, numstr2);
        break;
    }
    case 5:
    {
        return 0;
    }

        return 0;
    }
}
