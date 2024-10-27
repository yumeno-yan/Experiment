#pragma once
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class BigDecimal
{
public:
	BigDecimal(const string& str) :number(str) {}
	string add(const string& other);
	BigDecimal add(const BigDecimal& other);
	BigDecimal operator+(const BigDecimal& other);
	static bool check_expression(const string& experssion);
	void show() const
	{
		cout << this->number << "\n";
	}
private:
	static void trim(string& str);
private:
	string number;
};
