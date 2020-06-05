#include "RSA.h"
#include "BigInt.h"

// ��Կ��ʼ��
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
// ����
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
	// ֱ�Ӽ���, ���ݻ����
	// return (DataType)(data, ekey) % pkey;
}
// ����
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
			prime++;	// ���ÿ�ζ�ȡ������ж�, Ч��̫��
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
 // ������Կ e     1 < e < orla
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
// ������Կ d
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
// ��ȡ�����������Լ��
/*
��ת�����: �� a, b �����Լ��--> ����������Խ�С��, �������Ϊ0, ��ô����(��С��)�������Լ��, �����Ϊ0, ���ó�����������, ����ѭ��, ֱ������Ϊ0
	1. ����(a >= b)
	2. a % b = r
	3. ��� r Ϊ 0, ����b
	4. r ��Ϊ 0 , �� a = b, b = r ѭ������, ֱ��r = 0 
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

// ���ܽӿ�
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
		// ÿ�ζ��� NUMBER��С, ���ܻ���, �������һ���ļ�δ����СС�� NUMBER, ������Ҫ�ж�
		fin.read(buffer, NUMBER * sizeof(DataType));
		// ���һ�ζ�ȡ���ֽ���
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
// ���ܽӿ�
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
		// ���һ�ζ�ȡ�Ĵ�С
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

	//// �ı���ʽ��, ���տո���߻��ж�ȡ����
	//char c;
	//int a;
	//double d;
	//std::ifstream fin("test.txt");
	//fin >> c;
	//fin >> a;
	//fin >> d;
	//std::cout << "a: " << a << "c: " << "d: " << d << std::endl;

	//std::ifstream fin("test.txt", std::ifstream::binary);
	//char buffer[100] = { 0 };	// ����ʼ������, ֱ�����(������)
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

	// �ַ�������
	/*std::ofstream fout("testout.txt");
	fout << a.a << endl;
	fout << a.c << " " << a.b << endl;*/

	//// �ֽ�������
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