#pragma once
#include <string>
#include <iostream>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

// 用于定义输出的样式
struct print_format
{
	int significant_digits; // 是否采用科学计数法，-1-不采用，0-自动，n-保留n位有效数字
	bool equation_output;	// 是否要输出算式，在幂运算时自动关闭
	string_view dir_path;	// 输出的路径，文件名会自动填充
};

extern print_format pf;

class BigDecimal
{
public:
	BigDecimal(const string& str) :number(str) {}
	BigDecimal(const BigDecimal& other) :number(other.number) {}
	BigDecimal& operator=(BigDecimal&& other) noexcept
	{
		if (this != &other)
		{
			this->number = std::move(other.number);
		}
		return *this;
	}
public:
	// 加法
	string add(const string& other);
	BigDecimal add(const BigDecimal& other);
	BigDecimal operator+(const BigDecimal& other);
	// 减法
	string subtract(const string& other);
	BigDecimal subtract(const BigDecimal& other);
	BigDecimal operator-(const BigDecimal& other);
	// 乘法
	string multiply(const string& other);
	BigDecimal multiply(const BigDecimal& other);
	BigDecimal operator*(const BigDecimal& other);
	// 除法
	string divide(const string& other);
	BigDecimal divide(const BigDecimal& other);
	BigDecimal operator/(const BigDecimal& other);
	// 幂运算
	BigDecimal pow(const string& other);
	BigDecimal pow(const BigDecimal& other);
	// 求平方根
	BigDecimal sqrt();
	// 检查数字是否正确
	static bool check_number(string& num);
	// 检查表达式是否正确
	static bool check_expression(const string& experssion);
	// 根据一个表达式来计算结果
	static BigDecimal calc_expression(const string& experssion);
	// 输出this->number
	inline void show() const
	{
		cout << this->number << "\n";
	}
	// 输出格式化后的number
	inline void format_show() const
	{
		cout << format_string(this->number) << "\n";
	}
private:
	/// 以下为辅助函数
	string multiply_single(const char& single, int zero_num);
	static int compare(string_view str1, string_view str2);
	static void trim(string& str);
	BigDecimal float_add(const BigDecimal& other);
	static void remove_lead_zero(string& str);
	BigDecimal float_divide(const BigDecimal& other);
private:
	/// 以下函数用于输出
	// 列乘法算式
	void multiply_print(string_view num1, string_view num2, string_view res, const vector<string>& arr);
	// 列除法算式
	void divide_print(string_view res, string_view dividend, string_view divisor, const vector<string>& remainder_arr, const vector<string>& tmp_arr);
	// 以规定的格式返回
	static string format_string(string_view str);
private:
	string number;
};
