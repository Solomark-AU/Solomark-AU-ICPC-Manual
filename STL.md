# 一、模板类vector
### <1>头文件
`#include<vector>`
### <2>初始化
```cpp
#include<iostream>
#include<vector>
using namespace std;
int main () {
	//几种初始化的方法
    vector<int> a;//定义一个vector  未初始化 输出》 0
    
    vector<int> a(3);//定义一个长度为3的vector  未初始化 输出》0 0 0
    
    vector<int> a(10, 3); //定义一个长度为10，且每个数赋值为3
    
	//将向量b中从下标0 1 2（共三个）的元素赋值给a，a的类型为int型
	//它的初始化不和数组一样 
	vector<int>a(b.begin(),b.begin+3);

	//从数组中获得初值
	int b[7]={1,2,3,4,5,6,7};
	vector<int> a(b,b+7）;
	
    for(auto x : a) {//遍历输出 
        cout << x << " ";
    }
    return 0;
}
```
### <3>vector元素访问
##### 1、at()

v.at(pos) 返回容器中下标为 pos 的引用。如果数组越界抛出 std::out_of_range 类型的异常。

##### 2、operator[]

v[pos] 返回容器中下标为 pos 的引用。不执行越界检查。

##### 3、front()

v.front() 返回首元素的引用。
```cpp
a.front();
//返回a的第1个元素,当且仅当a存在
```


##### 4、back()

v.back() 返回末尾元素的引用。
```cpp
a.back(); 
//返回vector的最后一个数
```
##### 5、data()

v.data() 返回指向数组第一个元素的指针。

### <4>vector长度相关
##### 1、size()

`a.size( )//返回元素个数`

##### 2、resize( )

`a.resize( )//改变大小`
改变 vector 的长度，多退少补。补充元素可以由参数指定。
##### 3、empty()

`a.empty();
//判断a是否为空，空则返回true，非空则返回false`
##### 4、max_size() 
返回容器的最大可能长度。

##### 5、reserve() 
使得 vector 预留一定的内存空间，避免不必要的内存拷贝。

##### 6、capacity() 
返回容器的容量，即不发生拷贝的情况下容器的长度上限。

##### 7、shrink_to_fit() 
使得 vector 的容量与长度一致，多退但不会少。
### <5>元素增添与修改
##### 1.clear() 
清除所有元素
##### 1.insert() 
支持在某个迭代器位置插入元素、可以插入多个。复杂度与 pos 距离末尾长度成线性而非常数的
##### 1.erase() 
删除某个迭代器或者区间的元素，返回最后被删除的迭代器。复杂度与 insert 一致。
##### 1.push_back()
 在末尾插入一个元素，均摊复杂度为 常数，最坏为线性复杂度。

```cpp
a.push_back(5);
//在a的最后一个向量后插入一个元素，其值为5
```
##### 1.pop_back() 
删除末尾元素，常数复杂度。
 ```cpp
a.pop_back();
//删除a向量的最后一个元素
```
##### 1.swap() 
与另一个容器进行交换，此操作是 常数复杂度 而非线性的。
### <6>迭代器
##### 1.begin()/cbegin()

返回指向首元素的迭代器，其中 *begin = front。
```cpp
a.begin();// vector的第0个数
a.end();// vector的最后一个的数的后面一个数
//通常与for循环结合使用
```

##### 2.end()/cend()

返回指向数组尾端占位符的迭代器，注意是没有元素的。

##### 3.rbegin()/crbegin()

返回指向逆向数组的首元素的逆向迭代器，可以理解为正向容器的末元素。

##### 4.rend()/crend()

返回指向逆向数组末元素后一位置的迭代器，对应容器首的前一个位置，没有元素。

##### 5、倍增的思想
[C++]系统为某一程序分配空间的所需时间，与空间大小无关，与申请次数有关如申请一个空间为1000 和 空间为1 申请1000次的所需时间差别是很大的，申请次数越多，越耗时间
### <7>使用迭代器的遍历、插入、删除操作
迭代器类似于指针，提供了对象的间接访问，但获取迭代器并不是使用取地址符。如果将指针理解为元素的“地址”，那么迭代器可以理解为元素的“位置”。可以使用迭代器访问某个元素，迭代器也能从一个元素移动到另一个元素。

一个迭代器的范围由一对迭代器表示，分别为 begin 和 end。其中 begin 成员返回指向第一个元素的迭代器；end 成员返回容器最后一个元素的下一个位置（one past the end），也就是指向一个根本不存在的尾后位置，这样的迭代器没什么实际含义，仅是个标记而已，表示已经处理完了容器中的所有元素。所以 begin 和 end 表示的是一个左闭右开的区间 [ begin , end)

迭代器可以用来实现容器的遍历、插入等操作，可以细品下面的例子：

##### 1、遍历
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
int main(void)
{
    vector<string> a{"0", "1", "2", "3", "4", "5", "6", "7", "8"};
    auto it = a.begin();  // 返回一个迭代器类型，一般来说我们并不关心迭代器具体的数据类型
    while(it != a.end())
    {
        cout << *it << " ";
        it++;
    }
    return 0;
}
// 运行结果 //
0 1 2 3 4 5 6 7 8 
```
##### 2、插入

插入操作的函数：

`v.insert(p, n, val) `：在迭代器 p 之前插入 n 个值为 val 的元素，返回新添加的第一个元素的迭代器。
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
int main(void)
{
    vector<int> a{1, 2, 3, };
    auto it1 = a.begin();  // 返回一个迭代器类型，一般来说我们并不关心迭代器具体的数据类型
    auto it2 = a.insert((it1+1), {6, 7, 8});  // 利用迭代器在第二个元素之前插入数据
    cout << *it2 << endl;  // 返回的是新插入元素第一个元素的迭代器
    auto it = a.begin();  // 
    while(it != a.end())
    {
        cout << *it << " ";
        it++;
    }
    return 0;
}
// 输出结果 //
6
1 6 7 8 2 3
```
##### 3、删除 

删除操作的函数：

`v.erase(p) `：删除迭代器 p 所指的元素，返回指向被删除元素之后元素的迭代器。

`v.erase(b,e) `：删除迭代器 b, e 之间的元素，返回指向最后一个被删除元素之后元素的迭代器。
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
int main(void)
{
    vector<int> a{1, 2, 3, };
    auto it1 = a.begin();  // 返回一个迭代器类型，一般来说我们并不关心迭代器具体的数据类型
    auto it2 = a.erase(it1+1);  // 删除元素 2
    cout << *it2 << endl;  // 返回的是新插入元素第一个元素的迭代器
    auto it = a.begin();  // 
    while(it != a.end())
    {
        cout << *it << " ";
        it++;
    }
    return 0;
}
// 运行结果 //
3
1 3
```
### <8>vector 元素的重排操作（排序、逆序等）

容器的重排需要用到头文件 `<algorithm> `中的算法

##### 1、排序 sort()

使用到的函数为 sort() ：按输入序列的字典序升序排序，原位操作，无返回值函数原型：

`void std::sort<std::vector<int>::iterator>`
`(std::vector<int>::iterator, std::vector<int>::iterator)`
举例：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(void)
{
    vector<int> a{2, 0, 2, 2, 0, 3, 0, 9};
    sort(a.begin(), a.end());  //原位操作
    for(int i:a)
        cout << i << " ";
    return 0;
}
// 输出结果 //
0 0 0 2 2 2 3 9 
```
##### 2、消除相邻的重复元素 unique()

使用到的函数为 `unique()` ：将输入序列相邻的重复项“消除”，返回一个指向不重复值范围末尾的迭代器，一般配合 `sort()` 使用，函数原型：
```cpp
std::vector<int>::iterator std::unique<std::vector<int>::iterator>(std::vector<int>::iterator, std::vector<int>::iterator)
```
举例：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(void)
{
    vector<int> a{2, 0, 2, 2, 0, 3, 0, 9};
    sort(a.begin(), a.end());  // 先排序
    for(int i:a)   cout << i << " "; // 输出
    cout << endl;
    auto end_unique = unique(a.begin(), a.end());  //将输入序列相邻的重复项“消除”，返回一个指向不重复值范围末尾的迭代器
    a.erase(end_unique, a.end()); // 删除末尾元素
    for(int i:a)   cout << i << " "; // 输出
    return 0;
}
// 运行结果 //
0 0 0 2 2 2 3 9 
0 2 3 9
```
##### 3、逆序 reverse()

方法1：使用到的函数为 `reverse() `：将输入序列按照下标逆序排列，原位操作，无返回值函数原型：
```cpp
void std::reverse<std::vector<int>::iterator>(std::vector<int>::iterator, std::vector<int>::iterator)
```
 方法2：使用greater<int>() 作为参数（内置函数）

`sort(nums.begin(), nums.end(), greater<int>());`
 举例：
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(void)
{
    vector<int> a{2, 0, 2, 2, 0, 3, 0, 9};
    reverse(a.begin(), a.end());  // 原位逆序排列
    for(int i:a)   cout << i << " "; // 输出
    return 0;
}
// 运行结果 //
9 0 3 0 2 2 0 2 
```
### <9> vector 中找最值
容器的重排同样需要用到头文件 <algorithm> 中的算法。

##### 1、最大值 auto it = max_element(v.begin, v,end())，返回最大值的迭代器，函数原型如下：
```cpp
constexpr std::vector<int>::iterator std::max_element<std::vector<int>::iterator>(std::vector<int>::iterator, std::vector<int>::iterator)
```
##### 2、最小值 auto it = min_element(v.begin, v,end())，返回最小值的迭代器，函数原型如下：
```cpp
constexpr std::vector<int>::iterator std::min_element<std::vector<int>::iterator>(std::vector<int>::iterator, std::vector<int>::iterator)
```
##### 3、相对位置大小 auto b = distance(x, y)，x、y 是迭代器类型，返回 x、y 之间的距离，可以用来获取最大/小值的索引，函数原型如下：
```cpp
std::ptrdiff_t std::distance<std::vector<int>::iterator>(std::vector<int>::iterator __first, std::vector<int>::iterator __last)
```
举例：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(void)
{
    vector<int> a({0,1,-2,3});
    auto b = distance(a.begin(), min_element(a.begin(), a.end()));
    cout << a[b] << endl;
    return 0;
}
// 输出 //
-2
```
##### 6、改变vector大小 及其 内存分配机制
与内置数组一样，vector 的所有元素必须存放在一片连续的内存中，但 vector 的大小可变性使得其所占用的内存大小也是可变的。

为了避免每次改变 vector 时重新分配内存空间再将原来的数据从新拷贝到新空间的操作，标准库实现者采用了减少容器空间重新分配次数的策略：当不得不获取新空间时，vector（string 也是如此）通常会分配比需求更大的空间作为预留的备用空间，这样就减少了重新分配空间的次数。

改变 vector 的大小可以使用 v.resize(n, t) 函数，调整 v 的大小为 n 个元素，任何新添加的元素都初始化为值 t 。
举例：
```cpp
#include <iostream>
#include <vector>
using namespace std;
 
int main(void)
{
    vector<vector<int>> a;
    a.resize(3, vector<int>(3));
    cout << "row : " << a.size() << endl;
    cout << "col : " << a[0].size() << endl;
    return 0;
}
// 输出 //
row : 3
col : 3
```
函数 `v.resize(n)`  可以用来告知容器分配至少能分配 n 个元素的内存空间。并不改变容器中元素的数量，仅影响 vector 预先分配多大的内存空间

# 二、string
### <1> 头文件
##### C++的string标准库
string是C++标准库的重要部分，主要用于字符串处理。使用string库需要在同文件中包括该库 `#include<string>`
### <2> 初始化
使用等号的初始化叫做拷贝初始化，不使用等号的初始化叫直接初始化。
```cpp
#include<iostream>
#include<string>
using namespace std;
int main(){
    string s;               //  默认初始化，一个空白的字符串
    string s1("ssss");      // s1是字面值"ssss"的副本
    string s2(s1);          // s2是s1的副本
    string s3 = s2;         // s3是s2的副本
    string s4(10, '4');     // s4初始化
    string s5 = "Andre";    // 拷贝初始化
    string s6 = string(10, 'c');    // 可拷贝初始化，生成一个初始化好的对象，拷贝给s6

    char cs[] = "12345";
    string s7(cs, 3);       // 复制字符串cs的前三个字符到s当中

    string s8 = "abcde";
    string s9(s8, 2);

    string s10 = "asdsfasdgf";
    string s11(s10, 3, 4);  // s4是s3从下标s开始4个字符的拷贝，超出s10.size出现未定义
    return 0;
}
```
### <3>string类型的读入
```cpp
string s;
cin >> s;   //不能读入空格，以空格，制表符，回车符作为结束标志
getline(cin, s); //可以读入空格和制表符，以回车符作为结束的标志
```
### <4>string类型的长度
```cpp
string s = "Hello, world!"
int len = s.size();
int len = s.length();   //这两种方式是等价的
```
!!注意他们的类型都是 注：std::string 的成员函数 length() 的返回值类型为 unsigned 类型，因此当 s.length() < t.length() 时，二者相减会得到一个很大的数产生运行时错误，所以相减之前需要先将二者强制类型转换为 int 类型。
### <5> 字符串末尾添加字符
可以用+号和`append()`函数在函数的末尾添加字符。
```cpp
string s;
s += 'a';
s.append('a');
```
### <6>寻找某字符（串）第一次出现的位置
##### 来自OIwiki的介绍
`find(str,pos)` 函数可以用来查找字符串中一个字符/字符串在 pos（含）之后第一次出现的位置（若不传参给 pos 则默认为 0）。如果没有出现，则返回 string::npos（被定义为 -1，但类型仍为 size_t/unsigned long）。

示例：
```cpp
string s = "OI Wiki", t = "OI", u = "i";
int pos = 5;
printf("字符 I 在 s 的 %lu 位置第一次出现\n", s.find('I'));
printf("字符 a 在 s 的 %lu 位置第一次出现\n", s.find('a'));
printf("字符 a 在 s 的 %d 位置第一次出现\n", s.find('a'));
printf("字符串 t 在 s 的 %lu 位置第一次出现\n", s.find(t));
printf("在 s 中自 pos 位置起字符串 u 第一次出现在 %lu 位置", s.find(u, pos));
```
输出：
```cpp
字符 I 在 s 的 1 位置第一次出现
字符 a 在 s 的 18446744073709551615 位置第一次出现 // 即为 size_t(-1)，具体数值与平台有关。
字符 a 在 s 的 -1 位置第一次出现 // 强制转换为 int 类型则正常输出 -1
字符串 t 在 s 的 0 位置第一次出现
在 s 中自 pos 位置起字符串 u 第一次出现在 6 位置
```
##### 来自csdn的介绍
```cpp
1. size_t find (constchar* s, size_t pos = 0) const;

  //在当前字符串的pos索引位置开始，查找子串s，返回找到的位置索引，

    -1表示查找不到子串

2. size_t find (charc, size_t pos = 0) const;

  //在当前字符串的pos索引位置开始，查找字符c，返回找到的位置索引，

    -1表示查找不到字符

3. size_t rfind (constchar* s, size_t pos = npos) const;

  //在当前字符串的pos索引位置开始，反向查找子串s，返回找到的位置索引，

    -1表示查找不到子串

4. size_t rfind (charc, size_t pos = npos) const;

  //在当前字符串的pos索引位置开始，反向查找字符c，返回找到的位置索引，-1表示查找不到字符

5. size_tfind_first_of (const char* s, size_t pos = 0) const;

  //在当前字符串的pos索引位置开始，查找子串s的字符，返回找到的位置索引，-1表示查找不到字符

6. size_tfind_first_not_of (const char* s, size_t pos = 0) const;

  //在当前字符串的pos索引位置开始，查找第一个不位于子串s的字符，返回找到的位置索引，-1表示查找不到字符

7. size_t find_last_of(const char* s, size_t pos = npos) const;

  //在当前字符串的pos索引位置开始，查找最后一个位于子串s的字符，返回找到的位置索引，-1表示查找不到字符

8. size_tfind_last_not_of (const char* s, size_t pos = npos) const;

 //在当前字符串的pos索引位置开始，查找最后一个不位于子串s的字符，返回找到的位置索引，-1表示查找不到子串
 ```
```cpp
void test8()
{
    string s("dog bird chicken bird cat");

    //字符串查找-----找到后返回首字母在字符串中的下标

    // 1. 查找一个字符串
    cout << s.find("chicken") << endl;        // 结果是：9

    // 2. 从下标为6开始找字符'i'，返回找到的第一个i的下标
    cout << s.find('i',6) << endl;            // 结果是：11

    // 3. 从字符串的末尾开始查找字符串，返回的还是首字母在字符串中的下标
    cout << s.rfind("chicken") << endl;       // 结果是：9

    // 4. 从字符串的末尾开始查找字符
    cout << s.rfind('i') << endl;             // 结果是：18-------因为是从末尾开始查找，所以返回第一次找到的字符

    // 5. 在该字符串中查找第一个属于字符串s的字符
    cout << s.find_first_of("13br98") << endl;  // 结果是：4---b

    // 6. 在该字符串中查找第一个不属于字符串s的字符------先匹配dog，然后bird匹配不到，所以打印4
    cout << s.find_first_not_of("hello dog 2006") << endl; // 结果是：4
    cout << s.find_first_not_of("dog bird 2006") << endl;  // 结果是：9

    // 7. 在该字符串最后中查找第一个属于字符串s的字符
    cout << s.find_last_of("13r98") << endl;               // 结果是：19

    // 8. 在该字符串最后中查找第一个不属于字符串s的字符------先匹配t--a---c，然后空格匹配不到，所以打印21
    cout << s.find_last_not_of("teac") << endl;            // 结果是：21

}
```

### <7> 获取子字符串substr()
很有用 特别是求子串的时候
```cpp
#include<iostream> 
#include<string>
using namespace std;

int main () {
    string a = "ac";
    a += "w";//支持比较操作符>,>=,<,<=,==,!=
    cout << a << endl; //输出子串a :acw

    a += "ing";  
    cout << a << endl;
    //以字符串数组理解
    cout << a.substr(0, 3) << endl; //当第一个数是0 则后一位数:输出从头开始的长度为3的子串
    cout << a.substr(0, 3) << endl; //当第一个数是1 则输出下标为1 到下标为3的子串  
    cout << a.substr(0, 9) << endl;//如果超出长度范围 则输出原子串
    cout << a.substr(1) << endl; //从下标为1开始输出
    cout << a.substr(0) << endl; //原子串
    printf("%s\n", a.c_str());//如果用printf输出  

    return 0;
}  

//输出
/*
acw
acwing
acw
acw
acwing
cwing
acwing
acwing
*/
```
### <8>  string的遍历：借助迭代器 或者 下标法
```cpp
void test6()
{
    string s1("abcdef"); // 调用一次构造函数

    // 方法一： 下标法

    for( int i = 0; i < s1.size() ; i++ )
    {
        cout<<s1[i];
    }
    cout<<endl;

    // 方法二：正向迭代器

    string::iterator iter = s1.begin();
    for( ; iter < s1.end() ; iter++)
    {
        cout<<*iter;
    }
    cout<<endl;

    // 方法三：反向迭代器
    string::reverse_iterator riter = s1.rbegin();
    for( ; riter < s1.rend() ; riter++)
    {
        cout<<*riter;
    }
    cout<<endl;
}
```
### <9>插入/删除字符（串）& 替换字符（串）
##### 1、插入/删除字符（串
`insert(index,count,ch)` 和` insert(index,str) `是比较常见的插入函数。它们分别表示在 index 处连续插入 count 次字符串 ch 和插入字符串 str。

`erase(index,count)` 函数将字符串 index 位置开始（含）的 count 个字符删除（若不传参给 count 则表示删去 index 位置及以后的所有字符）。

示例：
```cpp
string s = "OI Wiki", t = " Wiki";
char u = '!';
s.erase(2);
printf("从字符串 s 的第三位开始删去所有字符后得到的字符串是 %s\n", s.c_str());
s.insert(2, t);
printf("在字符串 s 的第三位处插入字符串 t 后得到的字符串是 %s\n", s.c_str());
s.insert(7, 3, u);
printf("在字符串 s 的第八位处连续插入 3 次字符串 u 后得到的字符串是 %s",
       s.c_str());
```
输出：
```cpp
从字符串 s 的第三位开始删去所有字符后得到的字符串是 OI
在字符串 s 的第三位处插入字符串 t 后得到的字符串是 OI Wiki
在字符串 s 的第八位处连续插入 3 次字符串 u 后得到的字符串是 OI Wiki!!!
```
##### 2、替换字符（串）
`replace(pos,count,str) `和 `replace(first,last,str) `是比较常见的替换函数。它们分别表示将从 pos 位置开始 count 个字符的子串替换为 str 以及将以 first 开始（含）、last 结束（不含）的子串替换为 str，其中 first 和 last 均为迭代器。

示例：
```cpp
string s = "OI Wiki";
s.replace(2, 5, "");
printf("将字符串 s 的第 3~7 位替换为空串后得到的字符串是 %s\n", s.c_str());
s.replace(s.begin(), s.begin() + 2, "NOI");
printf("将字符串 s 的前两位替换为 NOI 后得到的字符串是 %s", s.c_str());
```
输出：
```
将字符串 s 的第 3~7 位替换为空串后得到的字符串是 OI
将字符串 s 的前两位替换为 NOI 后得到的字符串是 NOI
```
### <10>string的排序：sort(s.begin(),s.end())
```cpp
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

void test9()
{
    string s = "cdefba";
    sort(s.begin(),s.end());
    cout<<"s:"<<s<<endl;     // 结果：abcdef
}
```
### <11> empty(), clear()
`empty()`可以用来检查字符串是否为空，`clear()`用来清空字符串。
```cpp
string s1 = "012345";
if(!s1.empty()){
    cout << s1.length << endl;
    s1.clear();
}
```