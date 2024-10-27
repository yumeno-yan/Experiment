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
