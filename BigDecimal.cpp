#include "BigDecimal.h"

string BigDecimal::add(const string& other)
{
	string ans;
	// 倒序遍历
	// i从当前数的个位开始，j从other的个位开始，add表示进位
	int i = this->number.length() - 1, j = other.length() - 1, add = 0;
	while (i >= 0 || j >= 0 || add != 0)
	{
		// >=0表示还有数没有处理完，<0 表示已经处理完所有数，直接置为0
		int x = i >= 0 ? this->number[i] - '0' : 0;
		int y = j >= 0 ? other[j] - '0' : 0;
		int result = x + y + add;
		ans.push_back('0' + result % 10);
		add = result / 10;
		i--;
		j--;
	}
	// 计算完以后的答案需要翻转过来
	std::reverse(ans.begin(), ans.end());
	return ans;
}

BigDecimal BigDecimal::add(const BigDecimal& other)
{
	return add(other.number);
}

BigDecimal BigDecimal::operator+(const BigDecimal& other)
{
	return this->add(other);
}

string BigDecimal::subtract(const string& other)
{
	// 先比较大小，让大的减小的
	string num_a, num_b;
	// 记录负号
	bool minus = false;
	switch (compare(this->number, other))
	{
	case 1:
		num_a = this->number;
		num_b = other;
		break;
	case -1:
		minus = true;
		num_a = other;
		num_b = this->number;
		break;
	default:
		return "0";
	}
	string ans;
	// 倒序遍历
	// i从当前数的个位开始，j从num_b的个位开始，borrow表示借位
	int i = num_a.length() - 1, j = num_b.length() - 1, borrow = 0;
	while (i >= 0)
	{
		// >=0表示还有数没有处理完，<0 表示已经处理完所有数，直接置为0
		int x = num_a[i] - '0';
		int y = j >= 0 ? num_b[j] - '0' : 0;
		int result = x - y - borrow;
		ans.push_back('0' + (result + 10) % 10);
		borrow = result < 0;
		i--;
		j--;
	}
	if (minus)
	{
		ans += "-";
	}
	// 计算完以后的答案需要翻转过来
	std::reverse(ans.begin(), ans.end());
	return ans;
}

BigDecimal BigDecimal::subtract(const BigDecimal& other)
{
	return this->subtract(other.number);
}

BigDecimal BigDecimal::operator-(const BigDecimal& other)
{
	return this->subtract(other);
}

/**
 * @brief 检查输入的表达式是否合法
 * @param experssion 待检查的表达式
 * @return true-检查通过 false-检查不通过
 */
bool BigDecimal::check_expression(const string& experssion)
{
	// 第一步根据运算符将表达式分割为num1 operator num2三部分
	auto index = experssion.find_first_of("+-*/");
	// 没找到就返回false
	if (index == string::npos)
	{
		return false;
	}
	string num1 = experssion.substr(0, index);
	string num2 = experssion.substr(index + 1);
	// 去除头尾的空格
	trim(num1), trim(num2);
	// 找到第一个不为数字的字符位置
	index = num1.find_first_not_of("0123456789");
	// index不表示不存在则说明num1有问题
	if (index != string::npos)
	{
		return false;
	}
	index = num2.find_first_not_of("0123456789");
	// 同上
	if (index != string::npos)
	{
		return false;
	}
	return true;
}

// 比较str1和str2的大小，str1大返回1，相等返回0，str2返回-1
int BigDecimal::compare(const string& str1, const string& str2)
{
	// 位数更多的一定更大
	if (str1.size() > str2.size())
	{
		return 1;
	}
	else if (str1.size() < str2.size())
	{
		return -1;
	}
	return str1.compare(str2);
}

/**
 * @brief 将传入的字符串去掉头尾的空格
 * @param str 传入的字符串
 */
void BigDecimal::trim(string& str)
{
	// 找到第一个和最后一个不为空格的位置
	auto first = str.find_first_not_of(" ");
	auto last = str.find_last_not_of(" ");
	// str替换为first和last之间的位置
	str = str.substr(first, last - first + 1);
}
