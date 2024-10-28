#include "topn.h"
#include "BigDecimal.h"

int main()
{
	//vector<Student> arr{ 1.5,2.5,3.5,4.5,6.5,7.5,7.5,1.5,5.5,6.5,9.5,11.5 };
	//auto a = top_n(arr, 8);
	//for (auto& s : a)
	//{
	//	cout << s.score << " ";
	//}
	//cout << "\n";
	BigDecimal a("333");
	BigDecimal b("1");
	// pf.decimal_point = 5;
	// auto ans = a / b;
	// ans.show();
	string str = "1234.5678";
	BigDecimal::format_string(str);
	return 0;
}