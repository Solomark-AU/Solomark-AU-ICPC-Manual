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

# 三、队列与优先队列
### <1>queue 队列
##### 1、主要介绍
C++ 在 STL 中提供了一个容器 `std::queue`,使用前需要先引入 `<queue>` 头文件。

STL 中对 queue 的定义
```cpp
// clang-format off
template<
    class T,
    class Container = std::deque<T>
> class queue;
```
T 为 queue 中要存储的数据类型。

`Container `为用于存储元素的底层容器类型。这个容器必须提供通常语义的下列函数：
```cpp
back()
front()
push_back()
pop_front()
```
STL 容器 `std::deque` 和 `std::list` 满足这些要求。如果不指定，则默认使用 `std::deque` 作为底层容器。

##### 2、queue初始化
`queue<Type, Container>` (<数据类型，容器类型>）
初始化时必须要有数据类型，容器可省略，省略时则默认为deque 类型

初始化示例

```cpp
queue<int>q1;
queue<double>q2;  
queue＜char＞q3；
//默认为用deque容器实现的queue；

queue＜char, list＜char＞＞q1；
//用list容器实现的queue 

queue＜int, deque＜int＞＞q2；
 //用deque容器实现的queue 
```
注意：不能用vector容器初始化queue
因为queue转换器要求容器支持front（）、back（）、push_back（）及 pop_front（），说明queue的数据从容器后端入栈而从前端出栈。所以可以使用deque和list对queue初始化，而vector因其缺少pop_front（），不能用于queue。

##### 3、queue操作
函数运用示例
###### 1：`push（）`
在队尾插入一个元素
```cpp
 queue <string> q;
    q.push("first");
    q.push("second");
    cout<<q.front()<<endl;
```

输出 first

###### 2：`pop() `
将队列中最靠前位置的元素删除，没有返回值
```cpp
queue <string> q;
	q.push("first");
	q.push("second");
	q.pop();
	cout<<q.front()<<endl;
```

输出 second 因为 first 已经被pop（）函数删掉了

###### 3：`size()`
 返回队列中元素个数
```cpp
  queue <string> q;
	   q.push("first");
	   q.push("second");
	   cout<<q.size()<<endl;
```

输出2，因为队列中有两个元素

###### 4：`empty() `
如果队列空则返回true
```cpp
queue <string> q;
    cout<<q.empty()<<endl;
    q.push("first");
    q.push("second");
    cout<<q.empty()<<endl;
```
分别输出1和0
最开始队列为空，返回值为1（ture）；
插入两个元素后，队列不为空，返回值为0（false）；

###### 5：`front()` 
返回队列中的第一个元素
```cpp
queue <string> q;
    q.push("first");
    q.push("second");
    cout<<q.front()<<endl;
    q.pop();
    cout<<q.front()<<endl;
```
第一行输出first；
第二行输出second，因为pop（）已经将first删除了

###### 6：`back() `
返回队列中最后一个元素
```cpp
queue <string> q;
q.push("first");
q.push("second");
cout<<q.back()<<endl;
```

输出最后一个元素second

###### 7:运算符
此外，queue 还提供了一些运算符。较为常用的是使用赋值运算符 `= `为 queue 赋值，示例：
```cpp
std::queue<int> q1, q2;

// 向 q1 的队尾插入 1
q1.push(1);

// 将 q1 赋值给 q2
q2 = q1;

// 输出 q2 的队首元素
std::cout << q2.front() << std::endl;
// 输出: 1
```

### <2> priority_queue 优先队列
##### 1.priority_queue的定义
1.区别：它和queue不同的就在于我们可以自定义其中数据的优先级, 让优先级高的排在队列前面,优先出队，并且没有front()，back()函数，只用top()访问队首元素
2.相同：优先队列具有队列的所有特性，包括基本操作，只是在这基础上添加了内部的一个排序，它本质是一个堆实现的，都包含同一个头文件

和队列基本操作相同:

·top 访问队头元素
·empty 队列是否为空
·size 返回队列内元素个数
·push 插入元素到队尾 (并排序)
·emplace 原地构造一个元素并插入队列
·pop 弹出队头元素
·swap 交换内容

##### 2、定义方式
```cpp
priority_queue <type> name; /* 定义一个最大优先队列 */
priority_queue <type, vector<type>, greater<type> > name; 
/* 定义一个最小优先队列 */

/* 例子 */
priority_queue <int> q;
priority_queue <string, vector<string>, greater<string> > qs;
```
最小优先队列，指保证队首永远是优先级最小的元素的优先队列。

最大优先队列，指保证队首永远是优先级最高的元素的优先队列。

需要注意的是，在定义小根优先队列的时候，greater的“>”和优先队列的“>”中间要有一个空格，否则部分编译器会将其识别为右移符号导致编译错误

# 四、deque双向队列
### 一、deque的简介
deque是一个双向队列（double-ended queue），可以在队列的两端进行元素的插入和删除操作。deque的全称是double-ended queue，翻译过来就是双端队列，也有人称之为双向队列，这两个名称都可以表示该数据结构。deque是C++STL（标准模板库）中的一种容器，可以用于存储各种类型的元素。deque的特点是可以在队列的两端进行元素的操作，并且可以高效地在队列的任意位置进行元素的插入和删除操作。
可以说deque几乎涵盖了queue（队列）、stack（堆栈）、vector（向量 ）等的全部用法，功能非常的强大。

使用queue时需要包含头文件：
```cpp
#include<deque>
```

### 二、deque的定义及初始化
定义
deque<数据类型>容器名
例：
```cpp
//deque的定义 
deque<int>d1; //定义一个储存数据类型为int的双端队列d1 
deque<double>d2; //定义一个储存数据类型为double的双端队列d2 
deque<string>d3; //定义一个储存数据类型为string的双端队列d3 
deque<结构体类型>d4; //定义一个储存数据类型为结构体类型的双端队列d4 
deque<int> d5[N]; //定义一个储存数据类型为int的双端队列数组d5 
deque<double>d6[N]; //定义一个储存数据类型为double的双端队列数组d6 
```
### 三、deque的成员函数
关于deque的常用函数：
```cpp
push_back()//在队列的尾部插入元素。
emplace_front()//与push_front()的作用一样 
push_front()//在队列的头部插入元素。
emplace_back()//与push_back()的作用一样 
pop_back()//删除队列尾部的元素。
pop_front()//删除队列头部的元素。
back()//返回队列尾部元素的引用。
front()//返回队列头部元素的引用。
clear()//清空队列中的所有元素。
empty()//判断队列是否为空。
size()//返回队列中元素的个数。
begin()//返回头位置的迭代器
end()//返回尾+1位置的迭代器
rbegin()//返回逆头位置的迭代器 
rend()//返回逆尾-1位置的迭代器 
insert()//在指定位置插入元素 
erase()//在指定位置删除元素 
```
示例代码：
```cpp
#include<iostream>
#include<deque>
using namespace std;
int main()
{
	deque<int> d; //定义一个数据类型为int的deque
	d.push_back(1); //向队列中加入元素1 
	d.push_back(2); //向队列中加入元素2
	d.push_back(3); //向队列中加入元素3
	d.push_back(4); //向队列中加入元素4
	cout<<"双端队列中现在的元素为："<<endl;
	for(int i=0;i<d.size();i++)
	{
		cout<<d[i]<<" ";
	}
	cout<<endl;
	d.pop_front();
	cout<<"弹出队首元素后，双端队列中现在的元素为："<<endl;
	for(int i=0;i<d.size();i++)
	{
		cout<<d[i]<<" ";
	}
	cout<<endl;
	d.pop_back();
	cout<<"弹出队尾元素后，双端队列中现在的元素为："<<endl;
	for(int i=0;i<d.size();i++)
	{
		cout<<d[i]<<" ";
	}
	cout<<endl;
	d.push_back(6);
	cout<<"在队尾添加元素6后，双端队列中现在的元素为："<<endl;
	for(int i=0;i<d.size();i++)
	{
		cout<<d[i]<<" ";
	}
	cout<<endl;
	d.push_front(8);
	cout<<"在队首添加元素8后，双端队列中现在的元素为："<<endl;
	for(int i=0;i<d.size();i++)
	{
		cout<<d[i]<<" ";
	}
}
```
运行结果：

双端队列中现在的元素为：
```cpp
1 2 3 4
```
弹出队首元素后，双端队列中现在的元素为：
```cpp
2 3 4
```
弹出队尾元素后，双端队列中现在的元素为：
```cpp
2 3
```
在队尾添加元素6后，双端队列中现在的元素为：
```cpp
2 3 6
```
在队首添加元素8后，双端队列中现在的元素为：
```cpp
8 2 3 6
```
### 四、deque的遍历方法
1.通过迭代器iterator遍历
```cpp
#include<iostream>
#include<deque>
using namespace std;
int main()
{
	deque<int> d; //定义一个数据类型为int的deque
	d.push_back(1); //向队列中加入元素1 
	d.push_back(2); //向队列中加入元素2
	d.push_back(3); //向队列中加入元素3
	d.push_back(4); //向队列中加入元素4
	deque<int>::iterator it;
	for(it=d.begin();it!=d.end();it++)
	{
		cout<<*it<<" ";
	}
}
```
运行结果：
```cpp
1 2 3 4
```
2.通过下标遍历
```cpp
#include<iostream>
#include<deque>
using namespace std;
int main()
{
	deque<int> d; //定义一个数据类型为int的deque
	d.push_back(1); //向队列中加入元素1 
	d.push_back(2); //向队列中加入元素2
	d.push_back(3); //向队列中加入元素3
	d.push_back(4); //向队列中加入元素4
	for(int i=0;i<d.size();i++)
	{
		cout<<d[i]<<" ";
	}
}
```
运行结果：
```cpp
1 2 3 4
```
3.通过foreach遍历
```cpp
#include<iostream>
#include<deque>
using namespace std;
int main()
{
	deque<int> d; //定义一个数据类型为int的deque
	d.push_back(1); //向队列中加入元素1 
	d.push_back(2); //向队列中加入元素2
	d.push_back(3); //向队列中加入元素3
	d.push_back(4); //向队列中加入元素4
	for(int it:d)
	{
		cout<<it<<" ";
	}
}
```
运行结果：
```cpp
1 2 3 4
```

# 五、stack 栈
### 1、定义
只允许在一端进行插入或删除操作的线性表，后进先出的线性表。首先，栈是一种线性表，但限定这种线性表只能在某一段进行插入和删除操作

栈顶（Top）：线性表允许进行插入和删除的一端。

栈底（Bottom）：固定的，不允许进行插入和删除的另一端。

空栈：不含任何元素。

### 2、常用操作
STL 中的 stack 容器提供了一众成员函数以供调用，其中较为常用的有：

元素访问
st.top() 返回栈顶
修改
st.push() 插入传入的参数到栈顶
st.pop() 弹出栈顶
容量
st.empty() 返回是否为空
st.size() 返回元素数量
此外，std::stack 还提供了一些运算符。较为常用的是使用赋值运算符 = 为 stack 赋值，示例：
```cpp
//stack<类型> 名字;
stack<int> s;

// 新建两个栈 st1 和 st2
std::stack<int> st1, st2;

// 为 st1 装入 1
st1.push(1);

// 将 st1 赋值给 st2
st2 = st1;

// 输出 st2 的栈顶元素
cout << st2.top() << endl;
// 输出: 1
```

# 六、map
### 1、map介绍与初始化

##### 1、map简介
map是STL（中文标准模板库）的一个关联容器。

可以将任何基本类型映射到任何基本类型。如int array[100]事实上就是定义了一个int型到int型的映射。
map提供一对一的数据处理，key-value键值对，其类型可以自己定义，第一个称为关键字，第二个为关键字的值
map内部是自动排序的
###### 2、 map构造函数
默认构造函数
```cpp
std::map<int, std::string> myMap; // 创建一个空的map，键类型为int，值类型为std::string
```
拷贝构造函数
```cpp
std::map<int, std::string> myMap1 = { {1, "one"}, {2, "two"} };  
std::map<int, std::string> myMap2(myMap1); // 使用myMap1初始化myMap2，myMap2现在包含myMap1的所有元素
```
##### 3、 map赋值操作（=，swap）
重载等号操作符
```cpp
std::map<int, std::string> myMap1 = { {1, "one"}, {2, "two"} };  
std::map<int, std::string> myMap2;  
myMap2 = myMap1; // 使用重载的等号操作符将myMap1的内容赋值给myMap2
```
swap函数
```cpp
std::map<int, std::string> myMap1 = { {1, "one"}, {2, "two"} };  
std::map<int, std::string> myMap2 = { {3, "three"}, {4, "four"} };  
myMap1.swap(myMap2); // 交换myMap1和myMap2的内容，现在myMap1包含{3, "three"}, {4, "four"}，myMap2包含{1, "one"}, {2, "two"}
```
##### 4、 map的容量（size、empty）
size函数
```cpp
std::map<int, std::string> myMap = { {1, "one"}, {2, "two"}, {3, "three"} };  
std::size_t size = myMap.size(); // size现在是3，因为myMap中有3个元素
```
empty函数
```cpp
std::map<int, std::string> myMap;  
if (myMap.empty()) {  
    std::cout << "The map is empty." << std::endl; // 输出"The map is empty."，因为myMap是空的  
} else {  
    std::cout << "The map is not empty." << std::endl;  
}
```
这些函数展示了map的一些基本用法，包括创建map、添加元素、复制map、交换map内容以及查询map的大小和是否为空。map的键和值可以是任何数据类型，包括自定义类型，只要键类型支持比较操作即可

### 2、map的增删查改
以下是针对map插入和删除操作的示例代码：

##### 1、map插入数据元素操作
```cpp
#include <iostream>  
#include <map>  
#include <string>  
  
int main() {  
    std::map<int, std::string> mapStu;  
  
    // 第一种 通过pair的方式插入对象  
    mapStu.insert(std::pair<int, std::string>(3, "小张"));  
  
    // 第二种 通过make_pair的方式插入对象（注意：您的示例中写成了inset，这是错误的，应该是insert）  
    mapStu.insert(std::make_pair(-1, "校长"));  
  
    // 第三种 通过value_type的方式插入对象  
    mapStu.insert(std::map<int, std::string>::value_type(1, "小李"));  
  
    // 第四种 通过数组的方式插入值  
    // 这种方式在键已存在时更新对应的值，在键不存在时插入新的键值对  
    mapStu[3] = "小刘"; // 注意：这会替换掉key为3的原始值"小张"  
    mapStu[5] = "小王";  
  
    // 输出map内容  
    for (const auto& kv : mapStu) {  
        std::cout << kv.first << ": " << kv.second << std::endl;  
    }  
  
    return 0;  
}

```
##### 2、map键值对value的修改
map容器中，改变某个键（key）对应的值（value）可以通过以下方式实现。

使用下标操作符（operator[]）
下标操作符可以用于访问或修改map中的元素。如果键已经存在，它会返回对应的引用，你可以直接通过这个引用修改值。如果键不存在，它会创建一个新的键值对，键为你提供的键，值为该类型的默认值。
```cpp
std::map<int, std::string> mapStu;  
mapStu[3] = "小张"; // 如果键3不存在，会创建一个新的键值对(3, "小张")  
mapStu[3] = "小刘"; // 如果键3已经存在，会更新其对应的值为"小刘"
```
使用find方法和迭代器
首先，使用find方法查找键在map中的位置，然后检查返回的迭代器是否指向map的结束位置（即键是否不存在）。如果键存在，可以通过迭代器访问并修改其对应的值。
```cpp
std::map<int, std::string> mapStu;  
mapStu[3] = "小张";  
  
// 使用find查找键3  
auto it = mapStu.find(3);  
if (it != mapStu.end()) {  
    // 键存在，修改其对应的值  
    it->second = "小刘";  
} else {  
    // 键不存在，可以选择插入新的键值对  
    mapStu[3] = "小刘";  
}
```
在这个例子中，it->second就是键为3的元素的值的引用，你可以直接给它赋新的值来修改它。
使用find方法则更加安全，因为它不会在你尝试修改不存在的键时创建新的键值对。
在大多数情况下，如果只是想修改现有键的值，并且确定该键一定存在，使用下标操作符可能是最简洁的方式。但如果你不确定键是否存在，或者不想在键不存在时创建新的键值对，那么使用find方法会更加合适。

##### 3、map的删操作（erase、clear）
假设mapStu是一个map容器，则：
```cpp
mapStu.clear(); //删所有
mapStu.erase(it);//删迭代器指定
mapStu.erase(beg, end);//删key区间
mapStu.erase(key1);  //删key对应

#include <iostream>  
#include <map>  
#include <string>  
  
int main() {  
    std::map<int, std::string> mapStu;  
  
    // 假设已经插入了一些元素  
    mapStu.insert(std::pair<int, std::string>(3, "小张"));  
    mapStu.insert(std::pair<int, std::string>(5, "小王"));  
    mapStu.insert(std::pair<int, std::string>(7, "小赵"));  
  
    // 删除所有元素  
    mapStu.clear();  
    std::cout << "After clear(): ";  
    for (const auto& kv : mapStu) {  
        std::cout << kv.first << ": " << kv.second << " ";  
    }  
    std::cout << std::endl;  
  
    // 重新插入一些元素  
    mapStu.insert(std::pair<int, std::string>(3, "小张"));  
    mapStu.insert(std::pair<int, std::string>(5, "小王"));  
    mapStu.insert(std::pair<int, std::string>(7, "小赵"));  
  
    // 删除指定迭代器所指的元素  
    auto it = mapStu.find(5);  
    if (it != mapStu.end()) {  
        mapStu.erase(it);  
    }  
  
    // 输出map内容  
    std::cout << "After erase(pos): ";  
    for (const auto& kv : mapStu) {  
        std::cout << kv.first << ": " << kv.second << " ";  
    }  
    std::cout << std::endl;  
  
    // 重新插入一些元素  
    mapStu.insert(std::pair<int, std::string>(3, "小张"));  
    mapStu.insert(std::pair<int, std::string>(5, "小王"));  
    mapStu.insert(std::pair<int, std::string>(7, "小赵"));  
  
    // 删除指定区间的元素  
    auto beg = mapStu.find(3);  
    auto end = mapStu.find(7);  
    mapStu.erase(beg, end); // 注意：这里删除的是[beg, end)区间  
  
    // 输出map内容  
    std::cout << "After erase(beg, end): ";  
    for (const auto& kv : mapStu) {  
        std::cout << kv.first << ": " << kv.second << " ";  
    }  
    std::cout << std::endl;  
  
    // 重新插入一些元素  
    mapStu.insert(std::pair<int, std::string>(3, "小张"));  
    mapStu.insert(std::pair<int, std::string>(5, "小王"));  
  
    // 删除指定key的元素  
    mapStu.erase(5);  
  
    // 输出map内容  
    std::cout << "After erase(keyElem): ";  
    for (const auto& kv : mapSt

```
### 3 、指定键的排序规则
std::map 默认是按照键（key）的升序进行排序的。然而，你可以通过提供自定义的比较函数或仿函数（functor）来改变这一排序规则。这里其实map的定义语法模板要填三个参数，map<T1,T2,R> ，第三个参数就是比较规则的函数（仿函数、lamda表达式、谓词等函数对象）

以下是一个例子，展示了如何使用std::greater仿函数来创建一个键为降序的map：
```cpp
#include <map>  
#include <string>  
#include <iostream>  
#include <functional> // 为了使用std::greater  
  
int main() {  
    // 创建一个键为降序的map，使用std::greater<int>作为比较函数  
    std::map<int, std::string, std::greater<int>> mapStuDesc;  
      
    mapStuDesc[3] = "小张";  
    mapStuDesc[5] = "小王";  
    mapStuDesc[1] = "小李";  
      
    // 遍历map并输出元素  
    for (const auto& pair : mapStuDesc) {  
        std::cout << "键: " << pair.first << ", 值: " << pair.second << std::endl;  
    }  
      
    return 0;  
}
```
在这个例子中，std::greater<int>是一个仿函数，它告诉map按照键的降序来存储元素。当你遍历这个map时，你会看到键是按照从大到小的顺序输出的。还可以创建自己的仿函数来实现更复杂的排序规则。例如，如果想要根据某个自定义的条件（假设是键的绝对值）来排序键，可以这样做：
```cpp
struct MyCompare {  
    bool operator()(const int& a, const int& b) const {  
        // 在这里实现你的比较逻辑  
        // 例如，假设我们想要按照键的绝对值来排序  
        return std::abs(a) < std::abs(b);  
    }  
};  
  
int main() {  
    std::map<int, std::string, MyCompare> mapAbsDesc;  
      
    mapAbsDesc[-3] = "小张";  
    mapAbsDesc[5] = "小王";  
    mapAbsDesc[-1] = "小李";  
      
    // 遍历map并输出元素  
    for (const auto& pair : mapAbsDesc) {  
        std::cout << "键: " << pair.first << ", 值: " << pair.second << std::endl;  
    }  
      
    return 0;  
}
```
在这个例子中，MyCompare是一个自定义的仿函数，它根据键的绝对值来进行比较。因此，当你遍历mapAbsDesc时，元素会按照键的绝对值的升序输出。

### 4、pair结构
pair 通常用于将两个值组合成一个单一的实体，以便可以作为一个整体进行传递或返回。std::pair 的两个元素可以是任何类型，包括基本数据类型（如 int、double 等）或自定义类型（如类、结构体等）。这两个元素分别被称为 first 和 second。

使用方法是先包含头文件：#include <utility>
定义和使用 std::pair：
```cpp
std::pair<int, std::string> myPair;  
myPair.first = 10;  
myPair.second = "Hello";
使用 make_pair 函数创建 std::pair对象：

std::pair<int, std::string> myPair = std::make_pair(10, "Hello");
```

# 七、set和multiset
### 1、结构
　　set和multiset会根据特定的排序原则将元素排序。两者不同之处在于，multisets允许元素重复，而set不允许重复。

　　只要是assignable、copyable、comparable（根据某个排序准则）的型别T，都可以成为set或者multisets的元素。如果没有特别的排序原则，采用默认的less，已operator < 对元素进行比较，以便完成排序。

排序准则必须遵守以下原则：

 必须是“反对称的”，对operator <而言，如果x < y为真，y<x为假。
 必须是“可传递的”，对operator <而言，如果x<y为真，y<z为真，那么x<z也为真。
 必须是“非自反的”，对operator<而言，x<x永远为假。
### 2、能力
　　和所有的标准关联容器类似，sets和multisets通常以平衡二叉树完成。



　　自动排序的主要优点在于使二叉树搜寻元素具有良好的性能，在其搜索函数算法具有对数复杂度。但是自动排序也造成了一个限制，不能直接改变元素值，因为这样会打乱原有的顺序，要改变元素的值，必须先删除旧元素，再插入新元素。所以sets和multisets具有以下特点：

不提供直接用来存取元素的任何操作元素
通过迭代器进行元素的存取。
### 3、操作函数
##### 3.1 构造、拷贝、析构


set c

产生一个空的set/multiset，不含任何元素

set c(op)

以op为排序准则，产生一个空的set/multiset

set c1(c2)

产生某个set/multiset的副本，所有元素都被拷贝

set c(beg,end)

以区间[beg,end)内的所有元素产生一个set/multiset

set c(beg,end, op)

以op为排序准则，区间[beg,end)内的元素产生一个set/multiset

c.~set()

销毁所有元素，释放内存

set<Elem>

产生一个set，以(operator <)为排序准则

set<Elem,0p>

产生一个set，以op为排序准则

##### 3.2 非变动性操作
操作

效果

c.size()

返回当前的元素数量

c.empty ()

判断大小是否为零，等同于0 == size()，效率更高

c.max_size()

返回能容纳的元素最大数量

c1 == c2

判断c1是否等于c2

c1 != c2

判断c1是否不等于c2(等同于!(c1==c2))

c1 < c2

判断c1是否小于c2

c1 > c2

判断c1是否大于c2

c1 <= c2

判断c1是否小于等于c2(等同于!(c2<c1))

c1 >= c2

判断c1是否大于等于c2 (等同于!(c1<c2))

##### 3.3 特殊的搜寻函数
　　sets和multisets在元素快速搜寻方面做了优化设计，提供了特殊的搜寻函数，所以应优先使用这些搜寻函数，可获得对数复杂度，而非STL的线性复杂度。比如在1000个元素搜寻，对数复杂度平均十次，而线性复杂度平均需要500次。

操作

效果

count (elem)

返回元素值为elem的个数

find(elem)

返回元素值为elem的第一个元素，如果没有返回end()

lower _bound(elem)

返回元素值为elem的第一个可安插位置，也就是元素值 >= elem的第一个元素位置

upper _bound (elem)

返回元素值为elem的最后一个可安插位置，也就是元素值 > elem 的第一个元素位置

equal_range (elem)

返回elem可安插的第一个位置和最后一个位置，也就是元素值==elem的区间

##### 3.4 赋值
操作

效果

c1 = c2

将c2的元素全部给c1

c1.swap(c2)

将c1和c2 的元素互换

swap(c1,c2)

同上，全局函数

##### 3.5 迭代器相关函数
　　sets和multisets的迭代器是双向迭代器，对迭代器操作而言，所有的元素都被视为常数，可以确保你不会人为改变元素值，从而打乱既定顺序，所以无法调用变动性算法，如remove()。

操作

效果

c.begin()

返回一个随机存取迭代器，指向第一个元素

c.end()

返回一个随机存取迭代器，指向最后一个元素的下一个位置

c.rbegin()

返回一个逆向迭代器，指向逆向迭代的第一个元素

c.rend()

返回一个逆向迭代器，指向逆向迭代的最后一个元素的下一个位置

##### 3.6 安插和删除元素
　　必须保证参数有效,迭代器必须指向有效位置，序列起点不能位于终点之后，不能从空容器删除元素。

操作

效果

c.insert(elem)

插入一个elem副本，返回新元素位置，无论插入成功与否。

c.insert(pos, elem)

安插一个elem元素副本，返回新元素位置，pos为收索起点，提升插入速度。

c.insert(beg,end)

将区间[beg,end)所有的元素安插到c，无返回值。

c.erase(elem)

删除与elem相等的所有元素，返回被移除的元素个数。

c.erase(pos)

移除迭代器pos所指位置元素，无返回值。

c.erase(beg,end)

移除区间[beg,end)所有元素，无返回值。

c.clear()

移除所有元素，将容器清空

### 4、示例代码
##### 4.1 set
```cpp
// cont/set1.cpp

    #include <iostream>
    #include <set>
    using namespace std;

    int main()
    {

       /*type of the collection:
        *-no duplicates
        *-elements are integral values
        *-descending order
        */
       typedef set<int,greater<int> > IntSet;

       IntSet coll1;         // empty set container

       //insert elements in random order
       coll1.insert(4);
       coll1.insert(3);
       coll1.insert(5);
       coll1.insert(1);
       coll1.insert(6);
       coll1.insert(2);
       coll1.insert(5);

       //iterate over all elements and print them
       IntSet::iterator pos;
       for (pos = coll1.begin(); pos != coll1.end(); ++pos) {
           cout << *pos << ' ';
       }
       cout << endl;

       //insert 4 again and process return value
       pair<IntSet::iterator,bool> status = coll1.insert(4);
       if (status.second) {
           cout << "4 inserted as element "
                << distance (coll1.begin(),status. first) + 1
                << endl;
       }
       else {
           cout << "4 already exists" << endl;
       }

       //assign elements to another set with ascending order
       set<int> coll2(coll1.begin(),
                      coll1.end());

       //print all elements of the copy
       copy (coll2.begin(), coll2.end(),
             ostream_iterator<int>(cout," "));
       cout << endl;

       //remove all elements up to element with value 3
       coll2.erase (coll2.begin(), coll2.find(3));

       //remove all elements with value 5
       int num;
       num = coll2.erase (5);
       cout << num << " element(s) removed" << endl;

       //print all elements
       copy (coll2.begin(), coll2.end(),
             ostream_iterator<int>(cout," "));
       cout << endl;
    }
```

输出：
```cpp
   6 5 4 3 2 1
   4 already exists
   1 2 3 4 5 6
   1 element(s) removed
   3 4 6
```
##### 4.2 multiset
复制代码
```cpp
 // cont/mset1.cpp

   #include <iostream>
   #include <set>
   using namespace std;

   int main()
   {

       /*type of the collection:
        *-duplicates allowed
        *-elements are integral values
        *-descending order
        */
       typedef multiset<int,greater<int> > IntSet;

       IntSet coll1,        // empty multiset container

       //insert elements in random order
       coll1.insert(4);
       coll1.insert(3);
       coll1.insert(5);
       coll1.insert(l);
       coll1.insert(6);
       coll1.insert(2);
       coll1.insert(5);

       //iterate over all elements and print them
       IntSet::iterator pos;
       for (pos = coll1.begin(); pos != coll1.end(); ++pos) {
           cout << *pos << ' ';
       }
       cout << endl;

       //insert 4 again and process return value
       IntSet::iterator ipos = coll1.insert(4);
       cout << "4 inserted as element "
            << distance (coll1.begin(),ipos) + 1
            << endl;

       //assign elements to another multiset with ascending order
       multiset<int> coll2(coll1.begin(),
                              coll1.end());

       //print all elements of the copy
       copy (coll2.begin(), coll2.end(),
             ostream_iterator<int>(cout," "));
       cout << endl;

       //remove all elements up to element with value 3
       coll2.erase (coll2.begin(), coll2.find(3));

       //remove all elements with value 5
       int num;
       num = coll2.erase (5);
       cout << num << " element(s) removed" << endl;

       //print all elements
       copy (coll2.begin(), coll2.end(),
             ostream_iterator<int>(cout," "));
       cout << endl;
   }
```

输出：
```cpp
6 5 5 4 3 2 1
4 inserted as element 5
1 2 3 4 4 5 5 6
2 element(s) removed
3 4 4 6
```

# 八、bitset
bitset 【压位】
它是一种类似数组的结构，它的每一个元素只能是０或１，每个元素仅用１bit空间,用于节省空间，
并且可以直接用01串赋值，可以理解为一个二进制的数组
### ①头文件
```cpp
include<bitset>
```
### ②初始化
```cpp
bitset<4> bs;　　//无参构造，长度为４，默认每一位为０

bitset<8> b(12);　　//长度为８，二进制保存，前面用０补充

string s = "100101"; //01串赋值
bitset<10> bs(s);　　//长度为10，前面用０补充

```
### ③支持操作
```cpp
  ~取反，&与，|与或，^异或
    >>，<<  移动
    ==，!=
    []   取0/1
```
### ④常用函数
```cpp
 	count(); //返回1的个数
    any(); //判断是否至少有一个1
    none(); //判断是否全为0
    set(); //把所有位置赋值为1
    set(k,v); //将第k位变成v
    reset(); //把所有位变成0
    flip(); //把所有位取反，等价于~
    flip(k); //把第k位取反
```