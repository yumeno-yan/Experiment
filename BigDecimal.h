#pragma once
#include <string>
#include <iostream>
#include <unordered_set>
#include <map>
#include <algorithm>

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
	static bool check_expression(const string& experssion);
	void show() const
	{
		cout << this->number << "\n";
	}
private:
	static int compare(const string& str1, const string& str2);
	static void trim(string& str);
private:
	string number;
};
