#include "topn.h"
#include "BigDecimal.h"
#include "io_handler.h"

int main()
{
	// coh.init("/home/jieyan/Experiment");
	// coh << "123\n" << "456";
	pf.significant_digits = -1;
	pf.equation_output = false;
	// auto ans = BigDecimal::calc_experssion("888484/114514");
	BigDecimal a("888484");
	BigDecimal b("51.99");
	// auto ans = a.float_add(b);
	// auto ans = b.float_divide(BigDecimal("2"));
	auto ans = a.sqrt();
	ans.show();
	// pf.significant_digits = 5;
	// string str = "1.123456";
	// cout << BigDecimal::format_string(str) << "\n";
	return 0;
}