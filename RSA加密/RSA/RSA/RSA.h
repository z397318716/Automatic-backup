#pragma once
#include<iostream>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<windows.h>
#include<fstream>

#define NUMBER 256
typedef long DataType;



struct Key
{
	DataType _ekey;
	DataType _dkey;
	DataType _pkey;

};

/*
RSA秘钥产生过程
	1. 随机选择两个不相等的质数 p 和 q (实际应用中，这两个质数越大，就越难破解)。
	2. 计算p和q的乘积n，n = pq。
	3. 计算n的欧拉函数 φ(n)
	4. 随机选择一个整数e，条件是 1 < e < φ(n)，且 e 与 φ(n) 互质。
	5. 计算 e 对于 φ(n) 的模反元素 d，使得 d * e ≡ 1 mod φ(n)，即 d * e % φ(n) = 1
	6. 公钥(e, n)  私钥(d, n)
*/

class RSA
{
public:
	RSA()
	{
		// 初始化所有的密钥
		GetKeys();
	}
	// 加密接口
	void Ecrept(const char* filename, const char* fileout);
	// 解密接口
	void Deecrpt(const char* filename, const char* fileout);

	// 获取素数
	DataType GetPrime();
	// 获取公钥与私钥的公共部分
	DataType GetPkey(DataType prime1, DataType prime2);
	// 获取欧拉函数
	DataType GetOrla(DataType prime1, DataType prime2);
	// 获取公钥 e
	DataType GetEkey(DataType orla);
	// 获取私钥 d
	DataType GetDkey(DataType ekey, DataType orla);
	// 获取两个数的最大公约数
	DataType GetGcd(DataType data1, DataType data2);
	// 判断一个数是否是素数
	bool IsPrime(DataType data);
	// 对数据加密
	DataType Ecrept(DataType data, DataType ekey, DataType pkey);
	// 对数据解密
	DataType Deecrpt(DataType data, DataType dkey, DataType pkey);
	// 初始化密钥函数
	void GetKeys();
	// 测试函数
	void Test();
	Key RSA::GetAllKey();
private:
	Key _key;
};