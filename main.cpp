#include "topn.h"
#include "BigDecimal.h"
#include "io_handler.h"

int main()
{
	// coh.init("/home/jieyan/Experiment");
	// coh << "123\n" << "456";
	pf.significant_digits = 7;
	// auto ans = BigDecimal::calc_experssion("888484/114514");
	string str1, str2;
	Ci_handler::read_number("../test_in1.txt", str1);
	Ci_handler::read_number("../test_in2.txt", str2);
	// BigDecimal a("888484");
	// BigDecimal b("114514");
	BigDecimal a(str1), b(str2);
	auto ans = a * b;
	ans.show();
	// pf.significant_digits = 5;
	// string str = "1.123456";
	// cout << BigDecimal::format_string(str) << "\n";
	return 0;
}