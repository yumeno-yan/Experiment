# Experiment

## top-n问题
## BigDecimal问题
### QA
#### 为什么有些函数的参数列表声明为string_view?
string_view是C++17引入的一个类，用于取代const string&，其本质是轻量级非拥有式识图。
轻量级：不会有内存的申请与释放，内存占用小，构造和复制的成本低
非拥有式：与源字符串共享字符串内容，本身没有单独的一份资源。string_view所代表的字符串会随着原始的变量改变而改变（类似于引用）
使用的目的是提高程序的性能，节约空间，但是vector<string_view>在代码中是不可行的。

举例：
```C++
string str1 = "hello",str2="world";
vector<string_view> arr;
arr.push_back(str1);
arr.push_back(str2);    // 没问题

string str = "hello";
vector<string_view> arr;
arr.push_back(str);
str = "world";
arr.push_back(str); // 有问题，str改变会导致arr[0]和arr[1]都变成"world"
```

此外，string_view取代的是const string&，这意味着string_view本身是不能变的，因此没有pop_back(),push_back()等修改的函数。