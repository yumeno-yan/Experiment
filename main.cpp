#include "topn.h"
#include "BigDecimal.h"
#include "io_handler.h"

// void test()
// {
// 	string str;
// 	getline(cin, str);
// 	if (BigDecimal::check_expression(str))
// 	{
// 		auto ans = BigDecimal::calc_expression(str);
// 		ans.show();
// 		ans.format_show();
// 	}
// 	else
// 	{
// 		cout << "invalid experssion\n";
// 	}

// }

int main(int argc, char* argv[])
{
	pf.significant_digits = 10;
	pf.equation_output = false;
	// // 初始化两个数
	// BigDecimal a("56922003254669360519221277544141136865");
	// BigDecimal b("4115575791522169834791714887721423442658045");
	// // 计算和
	// auto res1 = a + b;
	// res1.show();
	// //// 计算差
	// auto res2 = a - b;
	// res2.show();
	// // 计算积
	// auto res3 = a * b;
	// res3.show();
	// // 计算商
	// auto res4 = a / b;
	// res4.show();
	// // 计算幂
	// auto res5 = a.pow(b);
	// // res5.show();
	// res5.format_show();
	// // 计算平方根
	// auto res6 = a.sqrt();
	// res6.show();
	string str(argv[1]);
	auto pos = str.find_first_of("^");

	BigDecimal a(str.substr());
	BigDecimal b(argv[2]);
	a.pow(b).show();
	// auto ans = BigDecimal::calc_expression(argv[1]);
	// auto ans = BigDecimal::calc_expression("2822045247939963400314535328009835096319+4130672597162969766889460121879117110");
	// ans.show();
	return 0;
}