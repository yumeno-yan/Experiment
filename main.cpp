#include "topn.h"
#include "BigDecimal.h"
#include "io_handler.h"

int main()
{
	// coh.init("/home/jieyan/Experiment");
	// coh << "123\n" << "456";
	//vector<Student> arr{ 1.5,2.5,3.5,4.5,6.5,7.5,7.5,1.5,5.5,6.5,9.5,11.5 };
	//auto a = top_n(arr, 8);
	//for (auto& s : a)
	//{
	//	cout << s.score << " ";
	//}
	//cout << "\n";
	pf.significant_digits = 7;
	BigDecimal a("888484");
	BigDecimal b("114514");
	auto ans = a / b;
	ans.show();
	// pf.significant_digits = 5;
	// string str = "1.123456";
	// cout << BigDecimal::format_string(str) << "\n";
	return 0;
}