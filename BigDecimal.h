#pragma once
#include <string>
#include <iostream>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

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
	// 以下函数用于输出算式
	void multiply_print(const string& num1, const string& num2, const string& res, const vector<string>& arr, const string& file_path);
private:
	string number;
};
