#include "topn.h"
#include "BigDecimal.h"
#include "io_handler.h"

int main()
{
	pf.significant_digits = 6;
	pf.equation_output = true;
	// 初始化两个数
	BigDecimal a("1145141919810");
	BigDecimal b("888484");
	// 计算和
	auto res1 = a + b;
	res1.show();
	// 计算差
	auto res2 = a - b;
	res2.show();
	// 计算积
	auto res3 = a * b;
	res3.show();
	// 计算商
	auto res4 = a / b;
	res4.show();
	// 计算幂
	auto res5 = a.pow(b);
	// res5.show();
	// 计算平方根
	auto res6 = a.sqrt();
	res6.show();
	// pf.significant_digits = 5;
	// string str = "1.123456";
	// cout << BigDecimal::format_string(str) << "\n";
	return 0;
}