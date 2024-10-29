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
	string dir_path;	// 输出的路径，文件名会自动填充
};

extern print_format pf;

class BigDecimal
{
public:
	BigDecimal(const string& str) :number(str) {}
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
	// 检查表达式是否正确
	static bool check_expression(const string& experssion);
	inline void show() const
	{
		cout << this->number << "\n";
	}
private:
	string multiply_single(const char& single, int zero_num);
	static int compare(const string& str1, const string& str2);
	static void trim(string& str);
private:
	/// 以下函数用于输出
	// 列乘法算式
	void multiply_print(const string& num1, const string& num2, const string& res, const vector<string>& arr, const string& file_path);
	// 列除法算式
	void divide_print(const string& res, const string& dividend, const string& divisor, const vector<string>& remainder_arr, const vector<string>& tmp_arr);
	// 以规定的格式返回
	static string format_string(const string& str);
private:
	string number;
};
