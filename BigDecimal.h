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
	int decimal_point; // 保留几位小数，默认为6
	int scientific_notation; // 是否采用科学计数法，0-不采用，1-采用，2-自动，默认为自动
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
	void show() const
	{
		cout << this->number << "\n";
	}
private:
	string multiply_single(const char& single, int zero_num);
	static int compare(const string& str1, const string& str2);
	static void trim(string& str);
private:
	// 以下函数用于输出
	void multiply_print(const string& num1, const string& num2, const string& res, const vector<string>& arr, const string& file_path);
	// 以规定的格式返回
public:
	static string format_string(const string& str);
private:
	string number;
};
