#include "BigDecimal.h"

print_format pf = { 6,2 };

string BigDecimal::add(const string& other)
{
	string ans;
	// �������
	// i�ӵ�ǰ���ĸ�λ��ʼ��j��other�ĸ�λ��ʼ��add��ʾ��λ
	int i = this->number.length() - 1, j = other.length() - 1, add = 0;
	while (i >= 0 || j >= 0 || add != 0)
	{
		// >=0��ʾ������û�д����꣬<0 ��ʾ�Ѿ���������������ֱ����Ϊ0
		int x = i >= 0 ? this->number[i] - '0' : 0;
		int y = j >= 0 ? other[j] - '0' : 0;
		int result = x + y + add;
		ans.push_back('0' + result % 10);
		add = result / 10;
		i--;
		j--;
	}
	// �������Ժ�Ĵ���Ҫ��ת����
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
	// �ȱȽϴ�С���ô�ļ�С��
	string num_a, num_b;
	// ��¼����
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
	// �������
	// i�ӵ�ǰ���ĸ�λ��ʼ��j��num_b�ĸ�λ��ʼ��borrow��ʾ��λ
	int i = num_a.length() - 1, j = num_b.length() - 1, borrow = 0;
	while (i >= 0)
	{
		// >=0��ʾ������û�д����꣬<0 ��ʾ�Ѿ���������������ֱ����Ϊ0
		int x = num_a[i] - '0';
		int y = j >= 0 ? num_b[j] - '0' : 0;
		int result = x - y - borrow;
		ans.push_back('0' + (result + 10) % 10);
		borrow = result < 0;
		i--;
		j--;
	}
	// ȥ��ǰ��0
	while (ans.size() > 0 && ans.back() == '0')
	{
		ans.pop_back();
	}
	if (minus && ans.size() > 0)
	{
		ans += "-";
	}
	// �������Ժ�Ĵ���Ҫ��ת����
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
	// �Ƚϴ�С���ô�ĳ���С��
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
	// ������С����ÿһλ��ʹ����ϴ�����ˣ���¼��������
	BigDecimal add_res("0"), mul_res("");
	// ���ڴ洢ÿһ�εĻ��������
	vector<string> mul_res_arr;
	for (int i = num_b.size() - 1;i >= 0;i--)
	{
		// �ȼ�¼ÿһ�γ˷��Ľ��
		mul_res = BigDecimal(num_a).multiply_single(num_b[i], num_b.size() - i - 1);
		mul_res_arr.emplace_back(mul_res.number);
		// �˷�����뵱ǰ�ļӷ�������
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
	// �Ƚ��䲹����ͬλ��
	int point = other.size() > str.size() ? other.size() - str.size() : 0;
	for (int i = 0;i < point;i++)
	{
		str += "0";
	}
	string ans;
	// ����Ҫ���λ������������+����С����λ��+��0�ĸ���
	// ������ϲ�0������Ϊ��תΪ��ѧ����������ʱ��ֹλ������
	int digit_number = str.size() - other.size() + 1 + pf.decimal_point + point;
	// ����
	string remainder = str.substr(0, other.size());
	int k = other.size() - 1;
	for (int i = 0;i <= digit_number;i++)
	{
		bool find = false;
		for (int j = 1;j <= 10;j++)
		{
			if (j != 10)	// j==10��ʱ��˵��jһ��Ϊ9
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
	// �Ȳ���ȱʧ��0
	// string������ֱ����ͷԪ�ز��룬�����ȷ�ת
	std::reverse(ans.begin(), ans.end());
	for (int i = 0;i < point;i++)
	{
		ans += '0';
	}
	// �ٷ�ת����
	std::reverse(ans.begin(), ans.end());
	// �ٲ���С�����λ��
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
 * @brief �������ı��ʽ�Ƿ�Ϸ�
 * @param experssion �����ı��ʽ
 * @return true-���ͨ�� false-��鲻ͨ��
 */
bool BigDecimal::check_expression(const string& experssion)
{
	// ��һ����������������ʽ�ָ�Ϊnum1 operator num2������
	auto index = experssion.find_first_of("+-*/");
	// û�ҵ��ͷ���false
	if (index == string::npos)
	{
		return false;
	}
	string num1 = experssion.substr(0, index);
	string num2 = experssion.substr(index + 1);
	// ȥ��ͷβ�Ŀո�
	trim(num1), trim(num2);
	// �ҵ���һ����Ϊ���ֵ��ַ�λ��
	index = num1.find_first_not_of("0123456789");
	// index����ʾ��������˵��num1������
	if (index != string::npos)
	{
		return false;
	}
	index = num2.find_first_not_of("0123456789");
	// ͬ��
	if (index != string::npos)
	{
		return false;
	}
	return true;
}

/**
 * @brief ���㵱ǰ�����Ե������Ľ�������ڽ�β��0
 * @param single ������ַ�
 * @param i ��Ҫ�����0�ĸ���
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

// �Ƚ�str1��str2�Ĵ�С��str1�󷵻�1����ȷ���0��str2����-1
int BigDecimal::compare(const string& str1, const string& str2)
{
	// λ�������һ������
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
 * @brief ��������ַ���ȥ��ͷβ�Ŀո�
 * @param str ������ַ���
 */
void BigDecimal::trim(string& str)
{
	// �ҵ���һ�������һ����Ϊ�ո��λ��
	auto first = str.find_first_not_of(" ");
	auto last = str.find_last_not_of(" ");
	// str�滻Ϊfirst��last֮���λ��
	str = str.substr(first, last - first + 1);
}

/**
 * @brief ���ڳ˷��е���ʽ���
 * @param num1 ����
 * @param num2 ������
 * @param res ��˵Ľ��
 * @param arr �˷�������ÿһλ�Ļ�
 * @param file_path ������ļ���·��
 */
void BigDecimal::multiply_print(const string& num1, const string& num2, const string& res, const vector<string>& arr, const string& file_path)
{
	// �����һ�г���
	for (int i = 0;i < res.size() - num1.size();i++)
	{
		cout << " ";
	}
	cout << num1 << "\n";
	// ����ڶ��г���
	cout << "x";
	for (int i = 0;i < res.size() - num2.size() - 1;i++)
	{
		cout << " ";
	}
	cout << num2 << "\n";
	// ����м����
	for (int i = 0;i < res.size();i++)
	{
		cout << "-";
	}
	cout << "\n";
	// ���ÿ���м�Ļ�
	for (int i = 0;i < arr.size();i++)
	{
		for (int j = 0;j < res.size() - arr[i].size();j++)
		{
			cout << " ";
		}
		cout << arr[i].substr(0, arr[i].size() - i) << "\n";
	}
	// ���Ը�λ���Ļ�ֱ�ӷ���
	if (arr.size() == 1)
	{
		return;
	}
	// ����м����
	for (int i = 0;i < res.size();i++)
	{
		cout << "-";
	}
	cout << "\n";
	// ������Ļ�
	cout << res << "\n";
}

string BigDecimal::format_string(const string& str)
{
	string res;
	// ��תΪ��ѧ��������decimal��ʾʵ�����֣�exp��ʾָ������
	string decimal;
	int exp = 0;
	// ���ҵ�С�����λ��
	auto position = str.find_first_of(".");
	// ����Ǵ���������1234.5678
	if (position != 1)
	{
		exp += position - 1;
		// ��1234.5678��Ϊ1 . 234 5678�ĸ�����
		decimal = str.substr(0, 1) + "." + str.substr(1, position - 1) + str.substr(position + 1);
	}
	cout << exp << "\n";
	cout << decimal << "\n";
	return "";
}
