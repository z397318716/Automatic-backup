#include "BigInt.h"


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

	for (int i = 0; i < sum.length(); i++)
	{
		if (sum[i] != '0')
		{
			sum = sum.substr(i, sum.length() - i);
			break;
		}
	}
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
	for (int i = 0; i < num1.length(); i++)
	{
		if (num1[i] != '0')
		{
			num1 = num1.substr(i, num1.length() - i);
			break;
		}
	}
	for (int i = 0; i < num2.length(); i++)
	{
		if (num2[i] != '0')
		{
			num2 = num2.substr(i, num2.length() - i);
			break;
		}
	}
	std::string high;
	std::string low;
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
	
}