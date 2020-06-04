#include "RSA.h"
#include "BigInt.h"

// 密钥初始化
void RSA::GetKeys()
{
	DataType prime1 = GetPrime();
	DataType prime2 = GetPrime();
	while (prime2 == prime1)
	{
		prime2 = GetPrime();
	}
	DataType orla = GetOrla(prime1, prime2);
	_key._pkey = GetPkey(prime1, prime2);
	_key._ekey = GetEkey(orla);
	_key._dkey = GetDkey(_key._ekey, orla);
}
// 加密
DataType RSA::Ecrept(const DataType data, DataType ekey, DataType pkey)
{
	DataType Ai = data;
	DataType msgE = 1;
	DataType key = ekey;
	// data ^ ekey % pkey
	while (key)
	{
		if (key & 1)
			msgE = (msgE * Ai) % pkey;
		key >>= 1;	// ekey = ekey >> 1
		Ai = (Ai * Ai) % pkey;
	}
	return msgE;
	// 直接计算, 数据会溢出
	// return (DataType)(data, ekey) % pkey;
}
// 解密
DataType RSA::Deecrpt(const DataType data, DataType dkey, DataType pkey)
{
	DataType Ai = data;
	DataType msgE = 1;
	DataType key = dkey;
	// data ^ dkey % pkey
	while (key)
	{
		if (key & 1)
			msgE = (msgE * Ai) % pkey;
		key >>= 1;
		Ai = (Ai * Ai) % pkey;
	}
	return msgE;
	//return (DataType)pow(data, dkey) % pkey;
}

DataType RSA::GetPrime()
{
	srand(time(NULL));
	DataType prime;
	while (true)
	{
		prime = rand() % 100 + 2;	// 2 ~ 1001
		while (!RSA::IsPrime(prime))
		{
			prime++;	// 如果每次都取随机数判断, 效率太低
		}
		break;
	}
	return prime;
}
bool RSA::IsPrime(DataType data)
{
	if (data < 2)
		return false;
	DataType tmp = sqrt(data);
	for (int i = 2; i <= tmp; i++)
	{
		if (data % i == 0)
		{
			return false;
		}
	}
	return true;
}
DataType RSA::GetPkey(DataType prime1, DataType prime2)
{
	return prime1 * prime2;
}
DataType RSA::GetOrla(DataType prime1, DataType prime2)
{
	return (prime1 - 1) * (prime2 - 1);
}
 // 加密密钥 e     1 < e < orla
DataType RSA::GetEkey(DataType orla)
{
	DataType ekey = orla - 1;
	for (; ekey > 1; ekey--)
	{
		if (1 == RSA::GetGcd(ekey, orla))
			break;
	}
	return ekey;
}
// 解密密钥 d
DataType RSA::GetDkey(DataType ekey, DataType orla)
{
	DataType dkey = orla / ekey;
	while (true)
	{
		if ((ekey * dkey) % orla == 1)
			return dkey;
		++dkey;
	}
}
// 获取两个数的最大公约数
/*
碾转相除法: 求 a, b 的最大公约数--> 用最大数除以较小数, 如果余数为0, 那么除数(较小数)就是最大公约数, 如果不为0, 就用除数除以余数, 依次循环, 直至余数为0
	1. 假设(a >= b)
	2. a % b = r
	3. 如果 r 为 0, 返回b
	4. r 不为 0 , 用 a = b, b = r 循环计算, 直至r = 0 
*/
DataType RSA::GetGcd(DataType data1, DataType data2)
{
	if (data2 > data1)
		std::swap(data1, data2);
	DataType r = data1 % data2;
	while (r != 0)
	{
		data1 = data2;
		data2 = r;
		r = data1 % data2;
	}
	return data2;
}
Key RSA::GetAllKey()
{
	Key key;
	key._ekey = _key._ekey;
	key._dkey = _key._dkey;
	key._pkey = _key._pkey;
	return key;
}

// 加密接口
void RSA::Ecrept(const char* filename, const char* fileout)
{
	std::ifstream fin(filename, std::ifstream::binary);
	std::ofstream fout(fileout, std::ifstream::binary);

	if (!fin.is_open())
	{
		perror("input file open failed!");
		return;
	}
	char* buffer = new char[NUMBER];
	DataType* bufferout = new DataType[NUMBER];
	while (!fin.eof())
	{
		// 每次都读 NUMBER大小, 可能会多读, 比如最后一次文件未读大小小于 NUMBER, 所以需要判断
		fin.read(buffer, NUMBER * sizeof(DataType));
		// 最近一次读取的字节数
		int curbytes = fin.gcount();
		for (int i = 0; i < curbytes; ++i)
		{
			bufferout[i] = Ecrept((DataType)buffer[i], _key._ekey, _key._pkey);
		}
		fout.write((char*)bufferout, curbytes * sizeof(DataType));
	}

	delete[] buffer;
	delete[] bufferout;

	fin.close();
	fout.close();

}
// 解密接口
void RSA::Deecrpt(const char* filename, const char* fileout)
{
	std::ifstream fin(filename, std::ifstream::binary);
	std::ofstream fout(fileout, std::ofstream::binary);
	if (!fin.is_open())
	{
		perror("output file open failed!");
		return;
	}
	DataType* buffer = new DataType[NUMBER];
	char* bufferout = new char[NUMBER];
	while (!fin.eof())
	{
		fin.read((char*)buffer, NUMBER * sizeof(DataType));
		// 最近一次读取的大小
		int curbytes = fin.gcount();
		curbytes /= sizeof(DataType);
		for (int i = 0; i < curbytes; ++i)
		{
			bufferout[i] = Deecrpt(buffer[i], _key._dkey, _key._pkey);
		}
		fout.write(bufferout, curbytes);
	}
	delete[] bufferout;
	delete[] buffer;
	fout.close();
	fin.close();
}

void Test()
{
	RSA test;
	using std::cout;
	using std::cin;
	using std::endl;
	/*
	for (int i = 0; i < 10; i++)
	{
	Sleep(1000);
	std::cout << test.GetPrime() << std::endl;
	}
	*/
	/*
	test.GetKeys();
	Key key = test.GetAllKey();
	DataType ecrpt = test.Ecrept(9, key._ekey, key._pkey);
	DataType decrpt = test.Deecrpt(ecrpt, key._dkey, key._pkey);

	std::cout << key._ekey << ' ' << key._dkey << ' ' << key._pkey << std::endl;
	std::cout<< ecrpt << '\n';
	std::cout << decrpt << std::endl;
	*/

	//// 文本形式打开, 按照空格或者换行读取数据
	//char c;
	//int a;
	//double d;
	//std::ifstream fin("test.txt");
	//fin >> c;
	//fin >> a;
	//fin >> d;
	//std::cout << "a: " << a << "c: " << "d: " << d << std::endl;

	//std::ifstream fin("test.txt", std::ifstream::binary);
	//char buffer[100] = { 0 };	// 不初始化数据, 直接输出(烫烫烫)
	//fin.read(buffer, 100);
	//std::cout << fin.gcount() << endl;
	//cout << buffer << endl;

	//struct A
	//{
	//	char a;
	//	int b;
	//	double c;
	//};
	//A a;
	//a.a = 'z';
	//a.b = 1;
	//a.c = 2.2;

	// 字符流操作
	/*std::ofstream fout("testout.txt");
	fout << a.a << endl;
	fout << a.c << " " << a.b << endl;*/

	//// 字节流操作
	//std::ofstream fout("testout2.txt", std::ofstream::binary);
	//fout.write((char*)&a, sizeof(A));
	//fout.close();
	//std::ifstream fin("testout2.txt", std::ifstream::binary);
	//A b;
	//fin.read((char*)&b, sizeof(A));
	//cout << b.a << ' ' << b.b << ' ' << b.c << endl;

	//test.GetKeys();
	//Key k = test.GetAllKey();
	//cout << k._dkey << endl;
	//cout << k._ekey << endl;
	//cout << k._pkey << endl;
	//std::ofstream fout("test4.txt", 'bw+');
	//char* buffer = new char[NUMBER];
	//DataType* bufferout = new DataType[NUMBER];
	//int i = 0;
	//while (i < 10)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		int tmp = rand() % 10;
	//		buffer[j] = tmp;
	//	}
	//	
	//	fout.write(buffer, 10 * sizeof(int));
	//	i++;
	//}
	////fout.close();
	////test.GetKeys();

	/*test.Ecrept("test4.txt", "test4e.txt");
	test.Deecrpt("test4e.txt", "test4de.txt");*/

	std::string s1("1011");
	std::string s2("22");
	std::string s3("44444");

	std::string s4;
	std::string s5;
	std::string s6;
	BigInt big;
	s4 = big.add(s1, s2);
	s5 = big.add(s1, s3);
	s6 = big.add(s2, s3);
	int a = 12324343;
	int b = 67678789;
	cout << a + b << "\n";
	cout << big.add("12324343", "67678789");
	cout << s4 << endl;
	cout << s5 << endl;
	cout << s6 << endl;
}
int main()
{
	Test();


	system("pause");
	return 0;
}