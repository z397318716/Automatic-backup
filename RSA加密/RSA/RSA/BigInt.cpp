#include "BigInt.h"


// 大数加法, 模拟加法过程
std::string BigInt::add(std::string num1, std::string num2)
{
	// sum为存放最终结果的字符串, 此处直接使其等于较长的字符串,最终的结果覆盖掉现在的值
	std::string sum = (num1.size() > num2.size()) ? num1 : num2;
	int differencelength = abs((int)(num1.size() - num2.size()));
	if (num1.size() < num2.size())
		num1.insert(0, differencelength, '0');
	else
		num2.insert(0, differencelength, '0');
	
	int i = sum.size() -1;
	// 进位标签, 有进位为 1 无进位为 0
	int tag = 0;
	for (; i >= 0; i--)
	{
		// 保存每一位相加后不超过10的部分,
		int tmp = (int)(num1[i] - '0') + (int)(num2[i] - '0') + tag;
			sum[i] = (tmp % 10) + '0';
			if (tmp > 9)
				tag = 1;
			else
				tag = 0;
	}
	// 加到最高位,跳出循环后, 如果还有进位, 就向最高位之前插入进位 1
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

// 大数减法---模拟减法操作
std::string BigInt::sub(std::string &num1, std::string &num2)
{
/*
	判断两个数大小---保证大数减小数----如果num1 - num2 小于0 给最终结果前加上 负号即可.
	1. 去掉高位可能存在的0 (比如传入 00023)
	2. 较长的数大
	3. 一样长的数, 从高位开始一位一位逐位进行比较

	// 相减操作
	1.	从低位开始相减
	2. 判断被减数的对应位是否大于减数的对应位, 如果大于, 需要借位, 如果发生借位, 需要更新高位的值
	3. 进行对应位的减操作
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
	// 两个进行相减的大数有效位相同
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
		// 说明两个大数相等
		if (high.size() == 0)
			return "0";
	}
	
}