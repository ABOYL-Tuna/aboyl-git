#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 判断输入数据是否是数字，进行bool判断
bool numtell(string s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (i == 0)
        {
            if (!(s[i] > 0 && s[i] <= 9))
                return false;
        }
        else
        {
            if (!(s[i] >= 0 && s[i] <= 9))
                return false;
        }
        return true;
    }
}
// 由于string中储存的仅仅是对应数字的ASC码，不方便计算，所以最后统一用vector动态数组来实现运算
void Add(string &numstrA, string &numstrB) // 对加法进行重载
{
    vector<int> a;   // 第一个容器存放第一个数
    vector<int> b;   // 第二个容器存放第二个数
    vector<int> add; // 和容器存放俩数之和

    int index = 0; // 设置进位

    // 首先将俩个数保存在容器中
    // 并且是逆序保存  为了迎合vector的Push_back添加函数
    for (int i = numstrA.size() - 1; i >= 0; i--)
    {
        a.push_back(numstrA[i] - '0');
    }

    for (int i = numstrB.size() - 1; i >= 0; i--)
    {
        b.push_back(numstrB[i] - '0');
    }

    // 然后开始加法算法，对两个数逐位相加
    // 首先我们不管俩个数的长度大小，一直加到最短的那个数完全被加
    for (int i = 0; i < numstrA.size() && i < numstrB.size(); i++)
    {
        add.push_back((a[i] + b[i] + index) % 10); // 将逐位相加的结果储存在sum容器中
        index = (a[i] + b[i] + index) / 10;        // 满10则进行进位
    }

    // 然后开始考虑长度比较长的数的多余位置没有参加算法
    if (numstrA.size() > numstrB.size())
    {
        // 这是a的长度比b大的情况，这时候已经计算到了b的长度位上
        for (int i = numstrB.size(); i < numstrA.size(); i++)
        {
            add.push_back((index + a[i]) % 10);
            index = (a[i] + index) / 10;
        }
    }

    if (numstrB.size() > numstrA.size())
    {
        // 这是b的长度比a大的情况,这时候已经计算到了a的长度位上
        for (int i = numstrA.size(); i < numstrB.size(); i++)
        {
            add.push_back((index + b[i]) % 10);
            index = (index + b[i]) / 10;
        }
    }

    // 计算完毕后判断进位  如果进位不为空那么还要往前进1
    if (index != 0)
    {
        add.push_back(1);
        index = 0; // 并且清空进位
    }

    // 到这里已经完成加法算法
    // 下面为输出代码

    // 由于使用的容器较多，我选择使用迭代器输出sum  vector容器里的数据 即为最后的结果
    cout << numstrA << "+" << numstrB << "=";
    for (auto p = add.end() - 1; p >= add.begin(); p--)
    {
        cout << *p;
        if (p == add.begin())
        {
            break;
        }
    }
    cout << endl;

    // 函数结束
}
void Sub(string &numstrA, string &numstrB) // 对乘法进行重载
{
    vector<int> a;   // 容器a存入第一个数据
    vector<int> b;   // 容器b存入第二个数据
    vector<int> sub; // 差值容器存入最后结果
    int lend = 0;    // 定义借位数
    int tem = 0;     // 定义一个标志变量
                 // 添加这一步是若两数相等则直接给结果，不需要经过算法；
    if (numstrA == numstrB)
    {
        sub.push_back(0);
        goto flag;
    }
    // 因为减法运算还是从低位开始 那么我们还是 将数据倒序存入
    for (int i = numstrA.size() - 1; i >= 0; i--)
    {
        a.push_back(numstrA[i] - '0');
    }

    for (int i = numstrB.size() - 1; i >= 0; i--)
    {
        b.push_back(numstrB[i] - '0');
    }

    // 下面开始减法算法
    // 我选择使用绝对值算法 -> 首先放正负到一边，计算之前判断谁大谁小，保证永远使用大数减小数，最后再进行符号讨论；
    // 先利用位数来判断大小
    if (a.size() > b.size()) // a>b
    {
        tem = 0; // 标志a>b
        // 首先计算位数相同的地方
        for (int i = 0; i < numstrB.size(); i++)
        {
            if (a[i] < b[i])
            { // 借位过程
                for (int j = i + 1; j < numstrA.size(); j++)
                {
                    // 向高位借位，如果高位不为0，则可以正常借到；
                    if (a[j] != 0)
                    {
                        lend = 1;
                        a[j] -= 1;
                        break;
                    } // 如果高位为0，则向更高位借，0上有借位看为9；
                    else
                    {
                        a[j] = 9;
                    }
                }
                sub.push_back(lend * 10 + a[i] - b[i]);
                lend = 0;
            }
            else
            {
                sub.push_back(a[i] - b[i]);
            }
        } // 后续直接输入a的剩余数给sub即可
        for (int i = numstrB.size(); i < numstrA.size(); i++)
        {
            sub.push_back(a[i]);
        }
    }
    else
    {
        if (a.size() == b.size()) // 这包含了位数相等的情况所以要再次分开
        {
            for (int i = a.size() - 1;; i--)
            {
                if (a[i] > b[i])
                {
                    tem = 0;
                    break;
                }
                else
                {
                    if (a[i] < b[i])
                    {
                        tem = 1;
                        break;
                    }
                    else
                        continue;
                }
            }
        }
        // 之后算法和之前相同
        // 首先计算位数相同的地方
        for (int i = 0; i < numstrA.size(); i++)
        {
            if (b[i] < a[i])
            {
                for (int j = i + 1; j < numstrB.size(); j++)
                {
                    // 向高位借位，如果高位不为0，则可以正常借到；
                    if (b[j] != 0)
                    {
                        lend = 1;
                        b[j] -= 1;
                        break;
                    } // 如果高位为0，则向更高位借，0上有借位看为9；
                    else
                    {
                        b[j] = 9;
                    }
                }
                sub.push_back(lend * 10 + b[i] - a[i]);
                lend = 0;
            }
            else
            {
                sub.push_back(b[i] - a[i]);
            }
        }
        for (int i = numstrA.size(); i < numstrB.size(); i++)
        {
            sub.push_back(b[i]);
        }
    }
    // 删 除 前 导 0
    for (int i = sub.size() - 1; i >= 0; i--)
    {
        if (sub[i] == 0)
        {
            sub.erase(sub.begin() + i);
        }
        // 一旦有不为0的直接跳出循环
        else
        {
            break;
        }
    }
    // 减法算法结束
    // 下面为用迭代器输出
flag:
    cout << numstrA << "-" << numstrB << "=";
    // 如果A比B小需要输出负号
    if (tem)
    {
        cout << "-";
    }
    for (auto p = sub.end() - 1; p >= sub.begin(); p--)
    {
        cout << *p;
        if (p == sub.begin())
        {
            break;
        }
    }
    cout << endl;
    // 清内存(在网上看到了这个过程就去学习了一下，当有erase等这种清除时，仅仅是清除了内容，而非容量)
    vector<int>().swap(a);
    vector<int>().swap(b);
    vector<int>().swap(sub);
}
// 减法完成
void Mul(string &numstrA, string &numstrB)
{
    vector<int> a;    // a容器中存放第一个数
    vector<int> b;    // b容器中存放第二个数
    vector<int> mul;  // mul容器中存放俩数的乘积
    vector<int> temp; // temp容器为工具容器 用于储存 计算过程中的步骤
    int index = 0;    // 定义进位为0 Index
                   // 乘法也是从小位开始算起 所以也采用逆序储存逆序输出
    for (int i = numstrA.size() - 1; i >= 0; i--)
    {
        a.push_back(numstrA[i] - '0');
    }

    for (int i = numstrB.size() - 1; i >= 0; i--)
    {
        b.push_back(numstrB[i] - '0');
    }

    for (int i = 0; i < b.size(); i++)
    { // 这里用a的每一位去乘b的每一位
        for (int j = 0; j < a.size(); j++)
        {
            temp.push_back((a[j] * b[i] + index) % 10);
            index = (a[j] * b[i] + index) / 10;
        }
        // 使得低位补0
        for (int j = 0; j < i; j++)
        {
            temp.insert(temp.begin(), 0);
        }
        // 这里需要用到加法函数，所以内置一个新函数，为了重复利用代码，在设计一个vector型的数组
        vector<int> Muladd(vector<int> & a, vector<int> & b);
        // 执行加法  加法执行完毕后清空temp容器
        mul = Muladd(temp, mul);
        temp.clear();
    }
    // 最后一个进位加上
    if (index != 0)
    {
        mul.push_back(index);
    }
    // 乘法计算结束
    // 接下来为 迭代器输出储存乘积的容器 product
    cout << numstrA << "*" << numstrB << "=";
    for (auto p = mul.end() - 1; p >= mul.begin(); p--)
    {
        cout << *p;
        if (p == mul.begin())
        {
            break;
        }
    }
    cout << endl;
    // 输出完毕 接下来进行容器清内存
    vector<int>().swap(a);
    vector<int>().swap(b);
    vector<int>().swap(temp);
    vector<int>().swap(mul);
}
// 对乘法内置加法函数的类外定义
vector<int> Muladd(vector<int> &a, vector<int> &b)
{
    // 这个函数是实现两个容器的大数数据相加 与加法类一致
    int index = 0;   // 设置进位
    vector<int> sum; // 设置存放俩数和的容器 最后需要返回这个容器
    for (int i = 0; i < a.size() && i < b.size(); i++)
    {
        sum.push_back((index + a[i] + b[i]) % 10);
        index = (a[i] + b[i] + index) / 10;
    }
    // 相等的位数已经相加完毕
    // 接下来相加 独立的位数

    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            sum.push_back((a[i] + index) % 10);
            index = (a[i] + index) / 10;
        }
    }

    if (a.size() < b.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            sum.push_back((b[i] + index) % 10);
            index = (b[i] + index) / 10;
        }
    }

    if (index != 0)
    {
        sum.push_back(1);
    }
    // 计算完毕 返回算出的和容器vector
    // 注意 这时候的 vector 仍然是低数在左。高数在右
    return sum;
}

void Div(string &numstrA, string &numstrB)
{
    vector<int> divsub(vector<int> a, vector<int> b);    // 声明除法内置减法运算   运行的是第一个数减去第二个数（这里不改变母值，仅利用数据）
    int Comparevector(vector<int> & a, vector<int> & b); // 声明比较容器储存的数的大小的函数
    vector<int> a;                                       // a容器存放第一个数
    vector<int> b;                                       // b容器存放第二个数
    vector<int> div;                                     // div容器存放商

    // 读取环节
    // 因为除法的运算是从高位往低位进行运算 那么我们选择正向输入以方便运算
    for (int i = 0; i < numstrA.size(); i++)
    {
        a.push_back(numstrA[i] - '0');
    }

    for (int i = 0; i < numstrB.size(); i++)
    {
        b.push_back(numstrB[i] - '0');
    }

    // 开始除法算法这里利用减法来循环算出取整结果
    //  1.将被除数位数用0补齐使得其长度和除数的长度相等
    // 为了保留ab容器 利用复制构造创建新容器
    vector<int> B(b);
    vector<int> A(a);
    // 首先可以直接判断 俩数大小关系 如果前小于后直接输出0，没必要进行以下算法
    if (Comparevector(a, b) == 0) // a<=b的情况都能包括进来
    {
        cout << numstrA << "/" << numstrB << "=" << 0;
        return;
    }

    if (b.size() == a.size())
    {
        int j = 0;
        while (Comparevector(A, B) != 0)
        {
            A = divsub(A, B);
            j++;
        }
        cout << numstrA << "/" << numstrB << "=" << j << endl;
        return;
    }
    // a位数大于b
    int i;
    for (int i = B.size(); i < a.size(); i++)
    {
        B.push_back(0);
    }
    // 为了能重复利用代码，当二者位数一样时，就无须重新改动代码,进行低位补0
    while (B.size() > b.size())
    {
        // 这个只限于长度不相等  如果长度相等直接做减法很快得出答案！
        if (Comparevector(B, A) == 1)
        {
            // 始终保持位数一致
            B.pop_back();
            if (Comparevector(B, A) == 1) // 这个比较是用于下一次循环的时候
            {
                div.push_back(0);
                // 相当于商*10
            }
        }
        if (Comparevector(B, A) != 1)
        {
            for (i = 1; i != 1.1; i++)
            {
                A = divsub(A, B);
                if (Comparevector(A, B) == 0)
                {
                    div.push_back(i);
                    i = 1;
                    break;
                }
            }
        }
    }
    // 除法算法结束
    // 接下来为迭代器输出
    cout << numstrA << "/" << numstrB << "=";
    for (auto p = div.begin(); p < div.end(); p++)
    {
        cout << *p;
    }
    // 清理内存
    vector<int>().swap(a);
    vector<int>().swap(b);
    vector<int>().swap(A);
    vector<int>().swap(div);
}
vector<int> divsub(vector<int> a, vector<int> b) // 为了防止参数被改变 采用 值传递
{
    vector<int> divs;
    // 既然在除法里面的减法合理，那么一定是大数减小数  这里默认a>b
    // 因为传进来的容器是正序的 所以为了计算方便 我们需要做倒序处理,reverse为反转字符串函数
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int lend = 0; // 初始化借位
    // 既然已经默认了 a>b  那么a的位数一定大于等于b的位数
    for (int i = 0; i < b.size(); i++)
    {
        if (a[i] < b[i])
        {
            for (int j = i + 1; j < a.size(); j++) // a向高位非0数借位
            {
                if (a[j] != 0)
                {
                    a[j] -= 1;
                    lend = 1;
                    break;
                }
                else
                {
                    a[j] = 9; // 向0借位为9
                }
            }
        }
        divs.push_back(lend * 10 + a[i] - b[i]);
        lend = 0;
    }
    // 接下来为a多出的位数
    for (int i = b.size(); i < a.size(); i++)
    {
        divs.push_back(a[i]);
    }
    // 然后要让差恢复正常顺序
    reverse(divs.begin(), divs.end());
    for (int i = 0; i != 1.1; i++)
    {
        // 删除前导0
        if (divs[0] == 0 && divs.size() != 1)
        {
            divs.erase(divs.begin(), divs.begin() + 1);
        }
        else
        {
            break;
        }
    }
    return divs;
}
int Comparevector(vector<int> &a, vector<int> &b) // 这是内置在除法类中的比较函数 用于比较俩个正向储存的容器数的大小
// 若a>b  则返回1   小于则返回0      相等则返回3
{
    if (a.size() > b.size())
        return 1;
    if (a.size() < b.size())
        return 0;
    if (a.size() == b.size())
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] > b[i])
                return 1;
            if (a[i] < b[i])
                return 0;
        }
        return 3;
    }
}
// 至此，除法完成
void Mod(string &numstrA, string &numstrB)
{
    // 由于前面的铺垫，那么我们对于取模运算就比较容易实现，直接套用除法，乘法，减法即可

    vector<int> divsub(vector<int> a, vector<int> b);
    int Comparevector(vector<int> & a, vector<int> & b); // 声明比较容器储存的数的大小的函数
    vector<int> a;                                       // a容器存放第一个数
    vector<int> b;                                       // b容器存放第二个数
    vector<int> div;                                     // div容器存放商

    // 读取环节
    // 因为除法的运算是从高位往低位进行运算 那么我们选择正向输入以方便运算
    for (int i = 0; i < numstrA.size(); i++)
    {
        a.push_back(numstrA[i] - '0');
    }

    for (int i = 0; i < numstrB.size(); i++)
    {
        b.push_back(numstrB[i] - '0');
    }

    // 开始除法算法这里利用减法来循环算出取整结果
    //  1.将被除数位数用0补齐使得其长度和除数的长度相等
    // 为了保留ab容器 利用复制构造创建新容器
    vector<int> B(b);
    vector<int> A(a);
    // 首先可以直接判断 俩数大小关系 如果前小于后直接输出0，没必要进行以下算法
    if (Comparevector(a, b) == 0) // a<=b的情况都能包括进来
    {
        cout << numstrA << "/" << numstrB << "=" << 0;
        return;
    }

    if (b.size() == a.size())
    {
        int j = 0;
        while (Comparevector(A, B) != 0)
        {
            A = divsub(A, B);
            j++;
        }
        cout << numstrA << "/" << numstrB << "=" << j << endl;
        return;
    }
    // a位数大于b
    int i;
    for (int i = B.size(); i < a.size(); i++)
    {
        B.push_back(0);
    }
    // 为了能重复利用代码，当二者位数一样时，就无须重新改动代码,进行低位补0
    while (B.size() > b.size())
    {
        // 这个只限于长度不相等  如果长度相等直接做减法很快得出答案！
        if (Comparevector(B, A) == 1)
        {
            // 始终保持位数一致
            B.pop_back();
            if (Comparevector(B, A) == 1) // 这个比较是用于下一次循环的时候
            {
                div.push_back(0);
                // 相当于商*10
            }
        }
        if (Comparevector(B, A) != 1)
        {
            for (i = 1; i != 1.1; i++)
            {
                A = divsub(A, B);
                if (Comparevector(A, B) == 0)
                {
                    div.push_back(i);
                    i = 1;
                    break;
                }
            }
        }
    }
    vector<int> a1(div); // 复制div给a1进行乘法
    vector<int> b1(b);   // 复制b给b1进行乘法
    vector<int> mul;     // mul容器中存放俩数的乘积
    vector<int> temp;    // temp容器为工具容器 用于储存 计算过程中的步骤
    int index = 0;       // 定义进位为0 Index
                   // 乘法也是从小位开始算起 所以也采用逆序储存逆序输出
    for (int i = numstrA.size() - 1; i >= 0; i--)
    {
        a1.push_back(numstrA[i] - '0');
    }

    for (int i = numstrB.size() - 1; i >= 0; i--)
    {
        b1.push_back(numstrB[i] - '0');
    }

    for (int i = 0; i < b1.size(); i++)
    { // 这里用a的每一位去乘b的每一位
        for (int j = 0; j < a1.size(); j++)
        {
            temp.push_back((a[j] * b1[i] + index) % 10);
            index = (a1[j] * b1[i] + index) / 10;
        }
        // 使得低位补0
        for (int j = 0; j < i; j++)
        {
            temp.insert(temp.begin(), 0);
        }
        // 这里需要用到加法函数，所以内置一个新函数，为了重复利用代码，在设计一个vector型的数组
        vector<int> Muladd(vector<int> & a, vector<int> & b);
        // 执行加法  加法执行完毕后清空temp容器
        mul = Muladd(temp, mul);
        temp.clear();
    }
    // 最后一个进位加上
    if (index != 0)
    {
        mul.push_back(index);
    }
    // 导入减法的运算重载

    vector<int> a2(a);   // 把a给到a2，避免原值破坏
    vector<int> b2(mul); // 把乘法结果mul给到b2
    vector<int> sub;     // 差值容器存入最后结果
    int lend = 0;        // 定义借位数
    int tem = 0;         // 定义一个标志变量
                 // 添加这一步是若两数相等则直接给结果，不需要经过算法；
    if (numstrA == numstrB)
    {
        sub.push_back(0);
        goto flag;
    }
    // 因为减法运算还是从低位开始 那么我们还是 将数据倒序存入
    for (int i = numstrA.size() - 1; i >= 0; i--)
    {
        a2.push_back(numstrA[i] - '0');
    }

    for (int i = numstrB.size() - 1; i >= 0; i--)
    {
        b2.push_back(numstrB[i] - '0');
    }

    // 下面开始减法算法

    if (a2.size() > b2.size()) // a>b
    {
        tem = 0; // 标志a>b
        // 首先计算位数相同的地方
        for (int i = 0; i < numstrB.size(); i++)
        {
            if (a2[i] < b2[i])
            { // 借位过程
                for (int j = i + 1; j < numstrA.size(); j++)
                {
                    // 向高位借位，如果高位不为0，则可以正常借到；
                    if (a2[j] != 0)
                    {
                        lend = 1;
                        a2[j] -= 1;
                        break;
                    } // 如果高位为0，则向更高位借，0上有借位看为9；
                    else
                    {
                        a2[j] = 9;
                    }
                }
                sub.push_back(lend * 10 + a2[i] - b2[i]);
                lend = 0;
            }
            else
            {
                sub.push_back(a2[i] - b2[i]);
            }
        } // 后续直接输入a的剩余数给sub即可
        for (int i = numstrB.size(); i < numstrA.size(); i++)
        {
            sub.push_back(a2[i]);
        }
    }
    else
    {
        if (a2.size() == b2.size()) // 这包含了位数相等的情况所以要再次分开
        {
            for (int i = a2.size() - 1;; i--)
            {
                if (a2[i] > b2[i])
                {
                    tem = 0;
                    break;
                }
                else
                {
                    if (a2[i] < b2[i])
                    {
                        tem = 1;
                        break;
                    }
                    else
                        continue;
                }
            }
        }
        // 之后算法和之前相同
        // 首先计算位数相同的地方
        for (int i = 0; i < numstrA.size(); i++)
        {
            if (b2[i] < a2[i])
            {
                for (int j = i + 1; j < numstrB.size(); j++)
                {
                    // 向高位借位，如果高位不为0，则可以正常借到；
                    if (b2[j] != 0)
                    {
                        lend = 1;
                        b2[j] -= 1;
                        break;
                    } // 如果高位为0，则向更高位借，0上有借位看为9；
                    else
                    {
                        b2[j] = 9;
                    }
                }
                sub.push_back(lend * 10 + b2[i] - a2[i]);
                lend = 0;
            }
            else
            {
                sub.push_back(b2[i] - a2[i]);
            }
        }
        for (int i = numstrA.size(); i < numstrB.size(); i++)
        {
            sub.push_back(b2[i]);
        }
    }
    // 删 除 前 导 0
    for (int i = sub.size() - 1; i >= 0; i--)
    {
        if (sub[i] == 0)
        {
            sub.erase(sub.begin() + i);
        }
        // 一旦有不为0的直接跳出循环
        else
        {
            break;
        }
    }
    // 减法算法结束
    // 下面为用迭代器输出
flag:
    // 利用迭代器进行遍历完成取模运算
    for (auto p = sub.end() - 1; p >= sub.begin(); p--)
    {
        cout << *p;
        if (p == sub.begin())
        {
            break;
        }
    }
}
