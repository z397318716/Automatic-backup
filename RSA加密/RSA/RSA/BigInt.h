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
	// ����Ӧ�÷���������----������, ������
	std::pair<std::string, std::string> dev(std::string num1, std::string num2);


	// ͨ���ַ�����ʾ
	std::string _number;

};