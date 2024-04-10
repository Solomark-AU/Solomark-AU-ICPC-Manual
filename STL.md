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
