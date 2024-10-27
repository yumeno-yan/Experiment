#include "BigDecimal.h"

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
	if (minus)
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
	return str1.compare(str2);
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
