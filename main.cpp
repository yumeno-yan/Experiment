#include "topn.h"
#include "BigDecimal.h"
#include "io_handler.h"

int main()
{
	// coh.init("/home/jieyan/Experiment");
	// coh << "123\n" << "456";
	pf.significant_digits = 6;
	pf.equation_output = true;
	// auto ans = BigDecimal::calc_experssion("888484/114514");
	BigDecimal a("2");
	BigDecimal b("10");
	auto ans = a.pow(b);
	// auto ans = a / b;
	ans.show();
	// pf.significant_digits = 5;
	// string str = "1.123456";
	// cout << BigDecimal::format_string(str) << "\n";
	return 0;
}