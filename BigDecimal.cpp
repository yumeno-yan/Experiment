#include "BigDecimal.h"
#include "io_handler.h"

print_format pf = { 4,false };

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
	for (int i = num_b.size() - 1; i >= 0; i--)
	{
		// 先记录每一次乘法的结果
		mul_res = BigDecimal(num_a).multiply_single(num_b[i], num_b.size() - i - 1);
		mul_res_arr.emplace_back(mul_res.number);
		// 乘法结果与当前的加法结果相加
		add_res = mul_res + add_res;
	}
	if (pf.equation_output)
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
	// 去除前导0
	string str = this->number;
	string oth = other;
	auto str_non_zero = str.find_first_not_of("0");
	auto oth_non_zero = oth.find_first_not_of("0");
	if (oth_non_zero == string::npos)
	{
		return "NaN";
	}
	if (str_non_zero == string::npos)
	{
		return "0";
	}
	str.erase(0, str_non_zero);
	oth.erase(0, oth_non_zero);

	// 记录每次的余数和过程中的积，用于输出算式
	vector<string> remainder_arr, tmp_arr;
	// 先将其补到相同位数
	int point = oth.size() > str.size() ? oth.size() - str.size() : 0;
	string zero(point, '0');
	str += std::move(zero);
	string ans;
	// 计算要算的位数：整数部分+保留小数点位数+补0的个数
	// 这里加上补0个数是为了转为科学计数法方法时防止位数不够
	int digit_number = str.size() - oth.size() + 2 + max(pf.significant_digits, 0) + point;
	// 余数
	string remainder = str.substr(0, oth.size());
	int k = oth.size() - 1;
	for (int i = 0; i <= digit_number; i++)
	{
		bool find = false;
		for (int j = 1; j <= 10; j++)
		{
			if (j != 10)	// j==10的时候说明j一定为9
			{
				string tmp = BigDecimal(oth).multiply_single((char)(j + '0'), 0);
				switch (compare(remainder, tmp))
				{
				case 0:
					j++;
				case -1:
					find = true;
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
				string tmp = BigDecimal(oth).multiply_single(x, 0);
				tmp_arr.emplace_back(tmp);
				ans += x;
				remainder = BigDecimal(remainder).subtract(tmp);
				if (remainder == "0")
				{
					remainder.pop_back();
				}
				remainder += ++k >= str.size() ? '0' : str[k];
				remainder_arr.emplace_back(remainder);
				break;
			}
		}
	}
	// 输出对应的算式
	if (pf.equation_output)
		divide_print(ans, str, oth, remainder_arr, tmp_arr);
	// 先补上缺失的0
	// string不可以直接在头元素插入，所以先翻转
	std::reverse(ans.begin(), ans.end());
	for (int i = 0; i < point; i++)
	{
		ans += '0';
	}
	// 再翻转回来
	std::reverse(ans.begin(), ans.end());
	// 再补上小数点的位置
	int pos = str.size() - oth.size() + 1;
	ans = ans.substr(0, pos) + "." + ans.substr(pos);
	// 去除前导0
	int zero_pos = 0;
	while (true)
	{
		// 当前是0且下一位不是小数点
		if (ans[zero_pos] == '0' && zero_pos + 1 != pos)
		{
			zero_pos++;
		}
		else
		{
			break;
		}
	}
	ans.erase(0, zero_pos);
	return format_string(ans);
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
 * @brief 幂运算，这里用到了快速幂
 * @brief 快速幂的时间复杂度为O(logn)，在大数情景下性能显著提升
 */
string BigDecimal::pow(const string& other)
{
	// 幂运算时不输出算式且不进行科学计数法
	auto flag = pf.equation_output;
	auto significant_digits = pf.significant_digits;
	pf.equation_output = false;
	pf.significant_digits = -1;
	BigDecimal ans("1");
	BigDecimal a(this->number);
	string n = other;
	int cnt = 8;
	while (compare(n, "0") > 0 && cnt-- > 0)
	{
		if ((n.back() - '0') & 1)
		{
			ans = ans * a;
		}
		a = a * a;
		// 这里要达到整除的效果
		n = BigDecimal(n).divide("2");
		auto pos = n.find_first_of(".");
		n = n.substr(0, pos);
	}
	pf.equation_output = flag;
	pf.significant_digits = significant_digits;
	return ans.number;
}

BigDecimal BigDecimal::pow(const BigDecimal& other)
{
	return this->pow(other.number);
}

/**
 * @brief 牛顿迭代法求平方根
 */
BigDecimal BigDecimal::sqrt()
{
	auto flag = pf.equation_output;
	auto significant_digits = pf.significant_digits;
	pf.equation_output = false;
	pf.significant_digits = -1;

	auto& n = *this;
	// 这里选取比n小一点的10的整数幂作为初始值
	string initial_value("1");
	for (int i = 0;i < (n.number.size() - 1) / 2;i++)
		initial_value += "0";
	BigDecimal x(initial_value);
	int cnt = 20;
	while (cnt-- > 0)
	{
		x = x.float_add(n.float_divide(x)).float_divide(BigDecimal("2"));
	}
	pf.equation_output = flag;
	pf.significant_digits = significant_digits;
	auto& decimal = x.number;
	// 保留6位小数
	decimal = decimal.substr(0, decimal.find_first_of(".") + 7);
	return x;
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
	// index存在则说明num1有问题
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
 * @brief 根据表达式来计算结果
 * @see 注意调用此函数前必须先调用check_expression确保表达式的正确性!!!
 * @param experssion 要计算的表达式
 * @return 计算的结果
 */
BigDecimal BigDecimal::calc_experssion(const string& experssion)
{
	auto index = experssion.find_first_of("+-*/");
	string num1 = experssion.substr(0, index);
	string num2 = experssion.substr(index + 1);
	trim(num1), trim(num2);
	BigDecimal x1(num1), x2(num2);
	switch (experssion[index])
	{
	case '+':
		return x1 + x2;
	case '-':
		return x1 - x2;
	case '*':
		return x1 * x2;
	case '/':
		return x1 / x2;
	default:
		return BigDecimal("");
	}
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
	for (int i = str.size() - 1; i >= 0; i--)
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
	for (int i = 0; i < zero_num; i++)
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

// 带浮点数的加法
BigDecimal BigDecimal::float_add(const BigDecimal& other)
{
	auto pos1 = this->number.find_first_of(".");
	auto pos2 = other.number.find_first_of(".");
	string a_integer = this->number.substr(0, pos1);
	string a_decimal = pos1 == string::npos ? "" : this->number.substr(pos1 + 1);
	string b_integer = other.number.substr(0, pos2);
	string b_decimal = pos2 == string::npos ? "" : other.number.substr(pos2 + 1);
	// 整数部分的和
	auto integer = BigDecimal(a_integer) + BigDecimal(b_integer);
	// 小数部分的和
	// 小数部分需要先补齐至相同位
	const auto a_size = a_decimal.size(), b_size = b_decimal.size();
	if (a_size > b_size)
	{
		for (int i = 0; i < a_size - b_size; i++)
			b_decimal += "0";
	}
	else
	{
		for (int i = 0; i < (b_size - a_size); i++)
			a_decimal += "0";
	}
	auto decimal = BigDecimal(a_decimal) + BigDecimal(b_decimal);
	// 如果进位了需要在整数部分+1，小数部分去除进位
	if (decimal.number.size() > max(a_decimal.size(), b_decimal.size()))
	{
		integer = (BigDecimal(integer) + BigDecimal("1")).number;
		decimal.number.erase(0, 1);
	}
	// 最后处理一下末尾的0
	auto& dn = decimal.number;
	dn = "." + dn;
	for (int i = dn.size() - 1;i >= 0;i--)
	{
		if (dn[i] == '0' || dn[i] == '.')
		{
			dn.pop_back();
		}
		else
		{
			break;
		}
	}
	return BigDecimal(integer.number + dn);
}

// 带浮点数的除法
BigDecimal BigDecimal::float_divide(const BigDecimal& other)
{
	// 记录下除数和被除数的小数位数
	// a_number b_number各自对应原始的字符串
	auto& a_n = this->number, b_n = other.number;
	// an和bn各自对应的小数点的位置
	auto a_pos = a_n.find_first_of("."), b_pos = b_n.find_first_of(".");
	int a_count = a_pos == string::npos ? 0 : a_n.size() - a_pos - 1;
	int b_count = b_pos == string::npos ? 0 : b_n.size() - b_pos - 1;
	string a_integer = a_n.substr(0, a_pos) + (a_count == 0 ? "" : a_n.substr(a_pos + 1));
	string b_integer = b_n.substr(0, b_pos) + (b_count == 0 ? "" : b_n.substr(b_pos + 1));
	// cout << "a_integer: " << a_integer << ", b_integer: " << b_integer << "\n";
	BigDecimal res = BigDecimal(a_integer) / BigDecimal(b_integer);
	auto& rn = res.number;
	// cout << "rn: " << rn << "\n";
	int sub = a_count - b_count;
	// cout << "sub: " << sub << "\n";
	int pos = rn.find_first_of(".");
	if (sub > 0)	// 小数点前移
	{
		// 算一下要补几个0
		int cnt = sub - pos + 1;
		if (cnt > 0)
		{
			string zero(cnt, '0');
			rn = zero[0] + "." + zero.substr(1) + rn.substr(0, pos) + rn.substr(pos + 1);
		}
		else
		{
			cnt = -cnt + 1;
			string tmp = rn.substr(0, pos);
			rn = tmp.substr(0, cnt) + "." + tmp.substr(cnt, pos) + rn.substr(pos + 1);
		}
	}
	else if (sub < 0) // 小数点后移
	{
		sub = -sub;
		// 算一下补几个0
		int cnt = sub - rn.size() + pos + 1;
		// cout << "cnt: " << cnt << "\n";
		if (cnt > 0)
		{
			string zero(cnt, '0');
			rn += std::move(zero);
			rn = rn.substr(0, pos) + rn.substr(pos + 1);
		}
		else
		{
			rn = rn.substr(0, pos) + rn.substr(pos + 1, sub) + "." + rn.substr(pos + 1 + sub);
		}
	}
	// 去除前导0
	int zero_pos = 0;
	auto& ans = res.number;
	pos = ans.find_first_of(".");
	while (true)
	{
		// 当前是0且下一位不是小数点
		if (ans[zero_pos] == '0' && zero_pos + 1 != pos)
		{
			zero_pos++;
		}
		else
		{
			break;
		}
	}
	ans.erase(0, zero_pos);
	if (ans.back() == '.')
		ans.pop_back();
	// cout << ans << "\n";
	return res;
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
	coh.init("/home/jieyan/Experiment");
	// 输出第一行乘数
	for (int i = 0; i < res.size() - num1.size(); i++)
	{
		coh << " ";
	}
	coh << num1 << "\n";
	// 输出第二行乘数
	coh << "x";
	for (int i = 0; i < res.size() - num2.size() - 1; i++)
	{
		coh << " ";
	}
	coh << num2 << "\n";
	// 输出中间的线
	for (int i = 0; i < res.size(); i++)
	{
		coh << "-";
	}
	coh << "\n";
	// 输出每个中间的积
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < res.size() - arr[i].size(); j++)
		{
			coh << " ";
		}
		coh << arr[i].substr(0, arr[i].size() - i) << "\n";
	}
	// 乘以个位数的话直接返回
	if (arr.size() == 1)
	{
		return;
	}
	// 输出中间的线
	for (int i = 0; i < res.size(); i++)
	{
		coh << "-";
	}
	coh << "\n";
	// 输出最后的积
	coh << res << "\n";
}

/**
* @brief 用于除法的算式输出，在10÷2中，10是被除数，2是除数
* @param res 除法的结果
* @param dividend 被除数
* @param divisor 除数
* @param remainder_arr 余数数组
* @param tmp_arr 积数组
*/
void BigDecimal::divide_print(const string& res, const string& dividend, const string& divisor, const vector<string>& remainder_arr, const vector<string>& tmp_arr)
{
	coh.init("/home/jieyan/Experiment");
	// 输出除数，被除数，商
	do
	{
		for (int i = 0; i < divisor.size() * 2; i++)
			coh << " ";
		coh << res << "\n";
		for (int i = 0; i < divisor.size(); i++)
			coh << " ";
		for (int i = 0; i < divisor.size() + res.size(); i++)
			coh << "-";
		coh << "\n";
		coh << divisor << ")" << dividend << "\n";
	} while (0);

	// align控制末位对齐
	int align = divisor.size() * 2 + 1;
	for (int i = 0; i < res.size() - 1; i++)
	{
		for (int j = 0; j < align - tmp_arr[i].size(); j++)
			coh << " ";
		coh << tmp_arr[i] << "\n";
		for (int j = 0; j < align - tmp_arr[i].size() - 1; j++)
			coh << " ";
		for (int j = 0; j < tmp_arr[i].size() + 3; j++)
			coh << "-";
		coh << "\n";
		align++;
		for (int j = 0; j < align - remainder_arr[i].size(); j++)
			coh << " ";
		coh << remainder_arr[i] << "\n";
	}
}

/**
 * @brief 格式化输出，由于这是大数，这里主要是科学计数法
 * @brief 主要通过全局变量pf来控制格式化
 * @param 需要格式化的字符串
 * @return 格式化完成后的字符串
 */
string BigDecimal::format_string(const string& str)
{
	string res;
	// 科学计数法，decimal表示实数部分，exp表示指数部分
	string decimal;
	int exp = 0;
	if (pf.significant_digits == -1)
		return str;
	// 如果要使用科学计数法
	// 先找到小数点的位置
	auto position = str.find_first_of(".");
	if (position != 1)	// 如果是大数，形如1234.5678
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
	else	// 形如1.114514
	{
		exp = 0;
		decimal = str;
	}
	if (pf.significant_digits == 0)
	{
		// 默认保留5位有效数字（即整数1位+小数点后4位）
		pf.significant_digits = 5;
	}
	// 先提取要计算的部分
	string tmp = decimal.substr(0, 1) + decimal.substr(2, pf.significant_digits);
	// 四舍六入五成双
	int last_digit = tmp.back() - '0';
	int penultimate_digit = tmp[tmp.size() - 2] - '0';
	if (last_digit < 4 || (last_digit == 5 && penultimate_digit % 2 == 0))
	{
		tmp.pop_back();
	}
	else
	{
		tmp.pop_back();
		tmp = (BigDecimal(tmp) + BigDecimal("1")).number;
		if (tmp.size() > pf.significant_digits)
		{
			exp++;
			tmp.pop_back();
		}
	}
	res = tmp.substr(0, 1) + "." + tmp.substr(1);
	if (exp < 0)
	{
		res += "e-" + to_string(abs(exp));
	}
	else if (exp > 0)
	{
		res += "e" + to_string(exp);
	}
	return res;
}
