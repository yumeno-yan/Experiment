#include "BigDecimal.h"

print_format pf = { 6,2 };

string BigDecimal::add(const string& other)
{
	string ans;
	// 倒序遍历
	// i从当前数的个位开始，j从other的个位开始，add表示进位
	int i = this->number.length() - 1, j = other.length() - 1, add = 0;
	while (i >= 0 || j >= 0 || add != 0)
	{
		// >=0表示还有数没有处理完，<0 表示已经处理完所有数，直接置为0
		int x = i >= 0 ? this->number[i] - '0' : 0;
		int y = j >= 0 ? other[j] - '0' : 0;
		int result = x + y + add;
		ans.push_back('0' + result % 10);
		add = result / 10;
		i--;
		j--;
	}
	// 计算完以后的答案需要翻转过来
	std::reverse(ans.begin(), ans.end());
	return ans;
}

BigDecimal BigDecimal::add(const BigDecimal& other)
{
	return add(other.number);
}

BigDecimal BigDecimal::operator+(const BigDecimal& other)
{
	return this->add(other);
}

string BigDecimal::subtract(const string& other)
{
	// 先比较大小，让大的减小的
	string num_a, num_b;
	// 记录负号
	bool minus = false;
	switch (compare(this->number, other))
	{
	case 1:
		num_a = this->number;
		num_b = other;
		break;
	case -1:
		minus = true;
		num_a = other;
		num_b = this->number;
		break;
	default:
		return "0";
	}
	string ans;
	// 倒序遍历
	// i从当前数的个位开始，j从num_b的个位开始，borrow表示借位
	int i = num_a.length() - 1, j = num_b.length() - 1, borrow = 0;
	while (i >= 0)
	{
		// >=0表示还有数没有处理完，<0 表示已经处理完所有数，直接置为0
		int x = num_a[i] - '0';
		int y = j >= 0 ? num_b[j] - '0' : 0;
		int result = x - y - borrow;
		ans.push_back('0' + (result + 10) % 10);
		borrow = result < 0;
		i--;
		j--;
	}
	// 去除前导0
	while (ans.size() > 0 && ans.back() == '0')
	{
		ans.pop_back();
	}
	if (minus && ans.size() > 0)
	{
		ans += "-";
	}
	// 计算完以后的答案需要翻转过来
	std::reverse(ans.begin(), ans.end());
	return ans;
}

BigDecimal BigDecimal::subtract(const BigDecimal& other)
{
	return this->subtract(other.number);
}

BigDecimal BigDecimal::operator-(const BigDecimal& other)
{
	return this->subtract(other);
}

string BigDecimal::multiply(const string& other)
{
	// 比较大小，让大的乘以小的
	string num_a, num_b;
	switch (compare(this->number, other))
	{
	case 0:
	case 1:
		num_a = this->number;
		num_b = other;
		break;
	case -1:
		num_a = other;
		num_b = this->number;
		break;
	default:
		break;;
	}
	// 遍历较小数的每一位，使其与较大数相乘，记录结果并相加
	BigDecimal add_res("0"), mul_res("");
	// 用于存储每一次的积，输出用
	vector<string> mul_res_arr;
	for (int i = num_b.size() - 1;i >= 0;i--)
	{
		// 先记录每一次乘法的结果
		mul_res = BigDecimal(num_a).multiply_single(num_b[i], num_b.size() - i - 1);
		mul_res_arr.emplace_back(mul_res.number);
		// 乘法结果与当前的加法结果相加
		add_res = mul_res + add_res;
	}
	multiply_print(num_a, num_b, add_res.number, mul_res_arr, "");
	return add_res.number;
}

BigDecimal BigDecimal::multiply(const BigDecimal& other)
{
	return this->multiply(other.number);
}

BigDecimal BigDecimal::operator*(const BigDecimal& other)
{
	return this->multiply(other);
}

string BigDecimal::divide(const string& other)
{
	string str = this->number;
	// 先将其补到相同位数
	int point = other.size() > str.size() ? other.size() - str.size() : 0;
	for (int i = 0;i < point;i++)
	{
		str += "0";
	}
	string ans;
	// 计算要算的位数：整数部分+保留小数点位数+补0的个数
	// 这里加上补0个数是为了转为科学计数法方法时防止位数不够
	int digit_number = str.size() - other.size() + 2 + pf.decimal_point + point;
	// 余数
	string remainder = str.substr(0, other.size());
	int k = other.size() - 1;
	for (int i = 0;i <= digit_number;i++)
	{
		bool find = false;
		for (int j = 1;j <= 10;j++)
		{
			if (j != 10)	// j==10的时候说明j一定为9
			{
				string tmp = BigDecimal(other).multiply_single((char)(j + '0'), 0);
				switch (compare(remainder, tmp))
				{
				case 0:
					j++;
				case -1:
					find = true;
					break;
				case 1:
					break;
				default:
					break;
				}
			}
			else
			{
				find = true;
			}
			if (find)
			{
				char x = j - 1 + '0';
				string tmp = BigDecimal(other).multiply_single(x, 0);
				ans += x;
				remainder = BigDecimal(remainder).subtract(tmp);
				if (remainder == "0")
				{
					remainder.pop_back();
				}
				remainder += ++k >= str.size() ? '0' : str[k];
				break;
			}
		}
	}
	// 先补上缺失的0
	// string不可以直接在头元素插入，所以先翻转
	std::reverse(ans.begin(), ans.end());
	for (int i = 0;i < point;i++)
	{
		ans += '0';
	}
	// 再翻转回来
	std::reverse(ans.begin(), ans.end());
	// 再补上小数点的位置
	int pos = str.size() - other.size() + 1;
	ans = ans.substr(0, pos) + "." + ans.substr(pos);
	return ans;
}

BigDecimal BigDecimal::divide(const BigDecimal& other)
{
	return this->divide(other.number);
}

BigDecimal BigDecimal::operator/(const BigDecimal& other)
{
	return this->divide(other);
}

/**
 * @brief 检查输入的表达式是否合法
 * @param experssion 待检查的表达式
 * @return true-检查通过 false-检查不通过
 */
bool BigDecimal::check_expression(const string& experssion)
{
	// 第一步根据运算符将表达式分割为num1 operator num2三部分
	auto index = experssion.find_first_of("+-*/");
	// 没找到就返回false
	if (index == string::npos)
	{
		return false;
	}
	string num1 = experssion.substr(0, index);
	string num2 = experssion.substr(index + 1);
	// 去除头尾的空格
	trim(num1), trim(num2);
	// 找到第一个不为数字的字符位置
	index = num1.find_first_not_of("0123456789");
	// index不表示不存在则说明num1有问题
	if (index != string::npos)
	{
		return false;
	}
	index = num2.find_first_not_of("0123456789");
	// 同上
	if (index != string::npos)
	{
		return false;
	}
	return true;
}

/**
 * @brief 计算当前数乘以单个数的结果，并在结尾补0
 * @param single 传入的字符
 * @param i 需要补充的0的个数
 */
string BigDecimal::multiply_single(const char& single, int zero_num = 0)
{
	string ans;
	const auto& str = this->number;
	int tmp = 0;
	for (int i = str.size() - 1;i >= 0;i--)
	{
		int mul_res = (str[i] - '0') * (single - '0') + tmp;
		ans += mul_res % 10 + '0';
		tmp = mul_res / 10;
	}
	if (tmp)
	{
		ans += tmp + '0';
	}
	std::reverse(ans.begin(), ans.end());
	for (int i = 0;i < zero_num;i++)
	{
		ans += '0';
	}
	return ans;
}

// 比较str1和str2的大小，str1大返回1，相等返回0，str2返回-1
int BigDecimal::compare(const string& str1, const string& str2)
{
	// 位数更多的一定更大
	if (str1.size() > str2.size())
	{
		return 1;
	}
	else if (str1.size() < str2.size())
	{
		return -1;
	}
	auto res = str1.compare(str2);
	if (res < 0)
		return -1;
	else if (res == 0)
		return 0;
	else
		return 1;
}

/**
 * @brief 将传入的字符串去掉头尾的空格
 * @param str 传入的字符串
 */
void BigDecimal::trim(string& str)
{
	// 找到第一个和最后一个不为空格的位置
	auto first = str.find_first_not_of(" ");
	auto last = str.find_last_not_of(" ");
	// str替换为first和last之间的位置
	str = str.substr(first, last - first + 1);
}

/**
 * @brief 用于乘法中的算式输出
 * @param num1 乘数
 * @param num2 被乘数
 * @param res 相乘的结果
 * @param arr 乘法过程中每一位的积
 * @param file_path 输出到文件的路径
 */
void BigDecimal::multiply_print(const string& num1, const string& num2, const string& res, const vector<string>& arr, const string& file_path)
{
	// 输出第一行乘数
	for (int i = 0;i < res.size() - num1.size();i++)
	{
		cout << " ";
	}
	cout << num1 << "\n";
	// 输出第二行乘数
	cout << "x";
	for (int i = 0;i < res.size() - num2.size() - 1;i++)
	{
		cout << " ";
	}
	cout << num2 << "\n";
	// 输出中间的线
	for (int i = 0;i < res.size();i++)
	{
		cout << "-";
	}
	cout << "\n";
	// 输出每个中间的积
	for (int i = 0;i < arr.size();i++)
	{
		for (int j = 0;j < res.size() - arr[i].size();j++)
		{
			cout << " ";
		}
		cout << arr[i].substr(0, arr[i].size() - i) << "\n";
	}
	// 乘以个位数的话直接返回
	if (arr.size() == 1)
	{
		return;
	}
	// 输出中间的线
	for (int i = 0;i < res.size();i++)
	{
		cout << "-";
	}
	cout << "\n";
	// 输出最后的积
	cout << res << "\n";
}

string BigDecimal::format_string(const string& str)
{
	string res;
	// 先转为科学计数法，decimal表示实数部分，exp表示指数部分
	string decimal;
	int exp = 0;
	// 先找到小数点的位置
	auto position = str.find_first_of(".");
	// 如果要使用科学计数法
	if (pf.scientific_notation != 0)
	{
		// 如果是大数，形如1234.5678
		if (position != 1)
		{
			exp += position - 1;
			// 将1234.5678分为1 . 234 5678四个部分
			decimal = str.substr(0, 1) + "." + str.substr(1, position - 1) + str.substr(position + 1);
		}
		else if (str[0] == '0')	// 如果是较小数，形如0.000123456
		{
			// 找到第一个非0的位置
			auto non_zero_position = str.find_first_not_of("0.");
			exp -= non_zero_position - position;
			decimal = str.substr(non_zero_position, 1) + "." + str.substr(non_zero_position + 1);
		}
		else	// 1.114514
		{
			exp = 0;
			decimal = str;
		}
	}
	else
	{
		exp = 0;
		decimal = str;
	}

	// 再保留小数
	if ((decimal[pf.decimal_point + 3] - '0') >= 5)
	{

	}
	else
	{
		decimal = decimal.substr(0, pf.decimal_point + 2);
	}

	return "";
}
