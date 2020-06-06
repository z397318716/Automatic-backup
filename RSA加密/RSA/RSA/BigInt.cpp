#include "BigInt.h"


// ȥ������ ��λ��Ч��0
std::string Remove_0(std::string num)
{
	for (int i = 0; i < num.length(); i++)
	{
		if (num[i] != '0')
		{
			num = num.substr(i, num.length() - i);
			break;
		}
	}
	return num;
}
// �����ӷ�, ģ��ӷ�����
std::string BigInt::add(std::string num1, std::string num2)
{
	// sumΪ������ս�����ַ���, �˴�ֱ��ʹ����ڽϳ����ַ���,���յĽ�����ǵ����ڵ�ֵ
	std::string sum = (num1.size() > num2.size()) ? num1 : num2;
	int differencelength = abs((int)(num1.size() - num2.size()));
	if (num1.size() < num2.size())
		num1.insert(0, differencelength, '0');
	else
		num2.insert(0, differencelength, '0');
	
	int i = sum.size() -1;
	// ��λ��ǩ, �н�λΪ 1 �޽�λΪ 0
	int tag = 0;
	for (; i >= 0; i--)
	{
		// ����ÿһλ��Ӻ󲻳���10�Ĳ���,
		int tmp = (int)(num1[i] - '0') + (int)(num2[i] - '0') + tag;
			sum[i] = (tmp % 10) + '0';
			if (tmp > 9)
				tag = 1;
			else
				tag = 0;
	}
	// �ӵ����λ,����ѭ����, ������н�λ, �������λ֮ǰ�����λ 1
	if (tag == 1)
		sum.insert(0, 1, '1');

	// ȥ����λ��Ч�� 0
	sum = Remove_0(sum);
	return sum;
}

// ��������---ģ���������
std::string BigInt::sub(std::string &num1, std::string &num2)
{
/*
	�ж���������С---��֤������С��----���num1 - num2 С��0 �����ս��ǰ���� ���ż���.
	1. ȥ����λ���ܴ��ڵ�0 (���紫�� 00023)
	2. �ϳ�������
	3. һ��������, �Ӹ�λ��ʼһλһλ��λ���бȽ�

	// �������
	1.	�ӵ�λ��ʼ���
	2. �жϱ������Ķ�Ӧλ�Ƿ���ڼ����Ķ�Ӧλ, �������, ��Ҫ��λ, ���������λ, ��Ҫ���¸�λ��ֵ
	3. ���ж�Ӧλ�ļ�����
*/
	// ȥ������Чλ��0
	num1 = Remove_0(num1);
	num2 = Remove_0(num2);

	std::string high;
	std::string low;
	// �ϳ�������
	if (num1.length() > num2.length())
	{
		high = num1;
		low = num2;
	}
	else if (num1.length() < num2.length())
	{
		high = num2;
		low = num1;;
	}
	// ������������Ĵ�����Чλ��ͬ
	else
	{
		for (int i = 0; i < num1.length(); ++i)
		{
			if (num1[i] > num2[i])
			{
				high = num1;
				low = num2;
				break;
			}
			else if (num1[i] < num2[i])
			{
				high = num2;
				low = num1;
				break;
			}
		}
		// ˵�������������
		if (high.size() == 0)
			return "0";
	}
	// �����ű��, ��� num1 > num2 Ϊ��, ����Ϊ��
	bool tag = true;
	if (num1 == low)
		tag = false;

	// ����������, ͨ����λ��0 �ķ�ʽ, ���һ����
	int differencelength = high.length() - low.length();
	low.insert(0, differencelength, '0');
	std::string result;
	result.resize(high.size());
	for (int i = high.size() - 1; i >= 0; --i)
	{
		int tmp = (high[i] - '0') - (low[i] - '0');
		// ��ǰλ������, ����һλ ��1
		if (tmp < 0)
		{
			high[i - 1] -= 1;
			tmp += 10;
		}
		result[i] = tmp + '0';
	}
	
	// ȥ��result ��λ��Ч��0
	result = Remove_0(result);
	// ����Ǹ���, ��ӷ���
	if (!tag)
		result.insert(0, 1,'-');
	return result;
}
// �����˷�---ģ��˷��������
std::string BigInt::mul(std::string &num1, std::string &num2)
{
	// ȥ����λ��Ч�� 0 
	num1 = Remove_0(num1);
	num2 = Remove_0(num2);
	if (num1.size() > num2.size())
	{
		swap(num1, num2);
	}
	std::string res("0");
	int tag = 0;
	for (int i = num1.size() - 1; i >= 0; --i)
	{
		std::string tmp = num2;
		
		for (int j = num2.size() - 1; i >= 0; --i)
		{
			int n = (num2[j] - '0') * (num1[i] - '0');
			// ��ǰλ��ֵ
			int g = n % 10 + tag;
			// ��λֵ����
			tag = n / 10;
			if (g < 10)
			{
				tmp[j] = g + '0';
			}
			else
			{
				tmp[j] = g % 10 + '0';
				tag++;
			}
		}
		if (tag != 0)
			tmp.insert(0, 1, tag + '0');
		tmp.append(num1.size() - 1 - i, '0');
		res = add(res, tmp);
	}

	res = Remove_0(res);

	return res;
}

// ��������---ģ������������

