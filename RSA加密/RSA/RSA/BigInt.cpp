#include "BigInt.h"


// 去掉大数 高位无效的0
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
// 大数加法, 模拟加法过程
std::string BigInt::add(std::string &num1, std::string &num2)
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

	// 去掉高位无效的 0
	sum = Remove_0(sum);
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
	// 去掉高无效位的0
	num1 = Remove_0(num1);
	num2 = Remove_0(num2);

	std::string high;
	std::string low;
	// 较长的数大
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
	// 正负号标记, 如果 num1 > num2 为正, 否则为负
	bool tag = true;
	if (num1 == low)
		tag = false;

	// 将两个大数, 通过高位补0 的方式, 变成一样长
	int differencelength = high.length() - low.length();
	low.insert(0, differencelength, '0');
	std::string result;
	result.resize(high.size());
	for (int i = high.size() - 1; i >= 0; --i)
	{
		int tmp = (high[i] - '0') - (low[i] - '0');
		// 当前位不够减, 向上一位 借1
		if (tmp < 0)
		{
			high[i - 1] -= 1;
			tmp += 10;
		}
		result[i] = tmp + '0';
	}
	
	// 去掉result 高位无效的0
	result = Remove_0(result);
	// 如果是负数, 添加符号
	if (!tag)
		result.insert(0, 1,'-');
	return result;
}
// 大数乘法---模拟乘法运算操作
std::string BigInt::mul(std::string &num1, std::string &num2)
{
	// 去掉高位无效的 0 
	num1 = Remove_0(num1);
	num2 = Remove_0(num2);
	if (num1.size() > num2.size())
	{
		swap(num1, num2);
	}
	std::string res = "0";
	int tag = 0;
	for (int i = num1.size() - 1; i >= 0; --i)
	{
		std::string tmp = num2;
		
		for (int j = num2.size() - 1; j >= 0; --j)
		{
			int n = (num2[j] - '0') * (num1[i] - '0') + tag;
			// 当前位的值
			int g = n % 10 ;
			// 进位值更新
			tag = n / 10;
			tmp[j] = g + '0';
		
		}
		if (tag != 0)
		{
			tmp.insert(0, 1, (tag + '0'));
			tag = 0;
		}
		tmp.append(num1.size() - 1 - i, '0');
		res = add(res, tmp);
	}

	res = Remove_0(res);

	return res;
}

// 大数除法---模拟除法运算操作
// 除法用减法来实现
/*
	如果直接循环开始减, 效率可能会十分低下-----比如   2400 / 2 循环的次数过多,
	可以考虑  把 除数与被除数的位数改为一致的, 2400 / 2000 ---最大减被除数的位差倍, 最小减被除数的大小

*/
std::pair<std::string, std::string> BigInt::dev(std::string &num1, std::string &num2)
{
	// 默认使用 num1 / num2
	std::pair<std::string, std::string> result;
	// 去掉高位的0
	num1 = Remove_0(num1);
	num2 = Remove_0(num2);
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1 < len2)
		return make_pair("0", num2);

	int lengthdiff = len1 - len2;
	if (lengthdiff > 1)
	{
		//num2.insert(len2, lengthdiff, '0');
		num2.append(lengthdiff, '0');
	}
	// 此时,记录 num2 补0 后的长度
	int newlen2 = len1;

	// 余数初始化
	result.second = num1;
	char tmp = ' ';
	for (int i = 0; i <= lengthdiff; ++i)
	{
		// 记录减法执行的次数
		char count = '0';
		while (true)
		{
			if (less(result.second, num2))
				break;
			result.second = sub(result.second, num2);
			++count;
		}
		result.first += count;
		
		// 除数减少10倍
		tmp = *(num2.rbegin());
		num2.pop_back();
	}
	num2.push_back(tmp);
	// 删除前置的0
	result.first = Remove_0(result.first);
	return result;

}

bool BigInt::less(std::string &num1, std::string &num2)
{
	// 去掉高位无效的 0
	Remove_0(num1);
	Remove_0(num2);
	if (num1.size() < num2.size())
		return true;
	if (num1.size() > num2.size())
		return false;

	return num1 < num2;
}
BigInt BigInt::operator+(BigInt & bi)
{
	std::string ret = add(_number, bi._number);
	return BigInt(ret);
}
BigInt BigInt::operator-(BigInt & bi)
{
	std::string ret = sub(_number, bi._number);
	return BigInt(ret);
}
BigInt BigInt::operator*(BigInt & bi)
{
	std::string ret = mul(_number, bi._number);
	return BigInt(ret);
}
BigInt BigInt::operator/(BigInt & bi)
{
	std::pair<std::string, std::string> ret = dev(_number, bi._number);
	return BigInt(ret.first);
}
BigInt BigInt::operator % (BigInt & bi)
{
	std::pair<std::string, std::string> ret = dev(_number, bi._number);
	return BigInt(ret.second);
}
std::ostream &operator<<(std::ostream &_cout, BigInt &bi)
{
	_cout << bi._number << std::endl;
	return _cout;
}
BigInt& BigInt::operator+=(BigInt &bi)
{
	std::string ret = add(_number, bi._number);
	return BigInt(ret);
}
BigInt &BigInt::operator-=(BigInt &bi)
{
	std::string ret = sub(_number, bi._number);
	return BigInt(ret);
}
BigInt &BigInt::operator*=(BigInt &bi)
{
	std::string ret = mul(_number, bi._number);
	return BigInt(ret);
}
BigInt &BigInt::operator/=(BigInt &bi)
{
	std::string ret = dev(_number, bi._number).first;
	return BigInt(ret);
}
BigInt &BigInt::operator%=(BigInt &bi)
{
	std::string ret = dev(_number, bi._number).second;
	return BigInt(ret);
}