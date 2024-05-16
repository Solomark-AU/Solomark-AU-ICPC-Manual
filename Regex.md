# 正则表达式

## 前置工作

```cpp
using namespace std;
char * str = r"\d\d";
string s = str;
char * a1;
string a2;
```

## regex 对象

- 创建

```cpp
regex regex_1(str);
regex regex_2(string);
```

- 使用

## match_results 对象

- 创建

```cpp
cmatch m1;
cmatch m2;

smatch sm;// string类型的match_results对象
```

- 使用

```cpp
regex_match(a1,m1,regex_1);
regex_match(a2,m2,regex_2);
```

- ready()方法

```cpp
bool flag = m1.ready();// 若匹配结果就绪则为 true，否则为 false。
```

## regex_match 函数

```cpp
bool regex_match(const string& str, const regex& rgx);
```

用于检查整个字符串是否与正则表达式匹配

```cpp
#include <iostream>
#include <regex>
using namespace std;
int main() {
    string str = "Hello, World!";
    regex rgx("Hello.*");

    if (regex_match(str, rgx)) {
        cout << "String matches the regex" << endl;
    } else {
        cout << "String does not match the regex" << endl;
    }

    return 0;
}
```

## regex_search 函数

```cpp
bool regex_search(const string& str, smatch& m, const regex& rgx);
```

在字符串中搜索与正则表达式匹配的子串

```cpp
#include <iostream>
#include <regex>
using namespace std;
int main() {
    string str = "The quick brown fox jumps over the lazy dog";
    regex rgx("\\b\\w{5}\\b");
    smatch match;

    if (regex_search(str, match, rgx)) {
        cout << "Found a word with 5 characters: " << match.str() << endl;
    } else {
       cout << "No word with 5 characters found" << endl;
    }

    return 0;
}
```

## regex_replace 函数

```cpp
string regex_replace(const string& str, const regex& rgx, const string& fmt)
```

在字符串中查找与正则表达式匹配的文本，并替换为指定的内容

```cpp
#include <iostream>
#include <regex>
using namespace std;
int main() {
    string str = "The quick brown fox jumps over the lazy dog";
    regex rgx("\\b\\w{5}\\b");
    string replaced = regex_replace(str, rgx, "*****");
    cout << "Original string: " << str << endl;
    cout << "Replaced string: " << replaced << endl;
    return 0;
}
```

### 子表达式匹配

正则表达式中通常包含一个或多个子表达式，子表达式通常用括号表示，在使用 smatch 保存匹配结果时，str()，str(0)表示整体正则表达式的匹配，str(1)表示第一个子表达式的匹配，str(2)表示第二个子表达式的匹配，依此类推。

smatch 包含多个 ssub_match 元素，位置 0 的元素表示整体匹配结果，其余元素表示子表达式的匹配结果，如果匹配了则 matched 成员为 true，如果整体都没匹配，则子表达式均不匹配。

```cpp
int main()
{
    string pattern("([0-9]+)([a-z]+)");
    regex r(pattern);
    string str1 = "12234abc";
    smatch result1;
    if (regex_search(str1, result1, r)) 
    {
        cout << result1.str(0) << endl;//12234abc
        cout << result1.str(1) << endl;//12234
        cout << result1.str(2) << endl;//abc
        cout << result1.str(10000) << endl;//空字符串，不会报错
        cout << boolalpha << result1[0].matched << endl;//true
        cout << result1[1].matched << endl;//true
        cout << result1[2].matched << endl;//true
        cout << result1[3].matched << endl;//false
    }
    string pattern2("([0-9]+)([a-z]+)");
    regex r2(pattern2);
    string str2 = "12234";
    smatch result2;
    regex_search(str2, result2, r2);
    cout << result2[0].matched << endl;//false
    cout << result2[1].matched << endl;//false
    cout << result2[2].matched << endl;//false

    string pattern3("([0-9]+)([a-z]+)?");//问号代表可选
    regex r3(pattern3);
    string str3 = "12234";
    smatch result3;
    regex_search(str3, result3, r3);
    cout << result3[0].matched << endl;//true
    cout << result3[1].matched << endl;//true
    cout << result3[2].matched << endl;//false
    system("pause");
}
```

## regex_iterator对象

regex_iterator()是C++中BiDirectionalIterator类的函数。此方法返回一个迭代器类型，以迭代序列中同一正则表达式模式的不同匹配。

用法:

``` cpp
template<
    class BidirectionalIterator,
    class CharT = typename std::iterator_traits::value_type,
    class Traits = std::regex_traits > class regex_iterator
```

C++ 14语法

``` cpp
template <class BidirectionalIterator,
          class charT=typename iterator_traits::value_type,
          class traits=regex_traits > class regex_iterator;
```

C++ 11语法：

``` cpp
template <class BidirectionalIterator,
          class charT=typename iterator_traits::value_type,
          class traits=regex_traits > class regex_iterator;
```

参数：此方法接受以下参数：

BidirectionalIterator:迭代目标字符序列。
字符：这是一个字符类型。
traits:这是正则表达式特征类型。
返回值：此方法返回带有结果序列的字符串对象。

以下示例说明了regex_iterator()方法：

例：

``` cpp
#include <iostream> 
#include <iterator> 
#include <regex> 
#include <string> 
using namespace std; 
  
int main() 
{ 
    while (1)
    {
        cout << "ZBQ is a cute nanliang\n";
    }
    //RBQ is nanniang
    const string 
        strg 
        = "Geeksforgeeks welcome geeks."; 
  
    regex words_regex("[^\\s]+"); 
    auto
        words_begin 
        = sregex_iterator( 
            strg.begin(), 
            strg.end(), 
            words_regex); 
  
    auto words_end = sregex_iterator(); 
  
    cout << "Trying to find words"
         << " using regex_iterator:\n\n"; 
  
    cout << "Number of words found:"
         << distance(words_begin, words_end); 
  
    cout << "\n\nThe words are:\n"; 
    for (sregex_iterator k = words_begin; 
         k != words_end; 
         ++k) { 
  
        smatch match = *k; 
        string match_str = match.str(); 
  
        cout << match_str 
             << endl; 
    } 
}
```

输出：

``` cpp
Trying to find words using regex_iterator:

Number of words found:3

The words are:
Geeksforgeeks
welcome
geeks.
```
