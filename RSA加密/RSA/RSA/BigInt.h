#pragma once
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<functional>
#include<boost/multiprecision/cpp_int.hpp>
class BigInt
{

public:
	void Test();
	BigInt()
	{}
	BigInt(const std::string& num) :
		_number(num)
	{}
	BigInt(const int num);
	BigInt operator+(BigInt & bi);
	BigInt operator-(BigInt & bi);
	BigInt operator*(BigInt & bi);
	BigInt operator/(BigInt & bi);
	BigInt operator%(BigInt & bi);
	friend std::ostream &operator<<(std::ostream &_cout, BigInt &bi);

	BigInt &operator+=(BigInt &bi);
	BigInt &operator-=(BigInt &bi);
	BigInt &operator*=(BigInt &bi);
	BigInt &operator/=(BigInt &bi);
	BigInt &operator%=(BigInt &bi);

	// ++n
	BigInt& operator++();
	// n++
	BigInt& operator++(int);
	// --n
	BigInt& operator--();
	// n--
	BigInt& operator--(int);
private:

	std::string add(std::string &num1, std::string &num2);
	std::string sub(std::string &num1, std::string &num2);
	std::string mul(std::string &num1, std::string &num2);
	// 除法应该返回两个数----返回商, 和余数
	std::pair<std::string, std::string> dev(std::string &num1, std::string &num2);
	bool less(std::string &num1, std::string &num2);


	// 通过字符串表示
	std::string _number;

};