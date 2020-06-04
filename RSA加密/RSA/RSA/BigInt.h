#pragma once
#include<iostream>
#include<string>
class BigInt
{

private:

public:
	std::string add(std::string num1, std::string num2);
	std::string sub(std::string &num1, std::string &num2);
	std::string mul(std::string &num1, std::string &num2);
	// 除法应该返回两个数----返回商, 和余数
	std::pair<std::string, std::string> dev(std::string num1, std::string num2);


	// 通过字符串表示
	std::string _number;

};