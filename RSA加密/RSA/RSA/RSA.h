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
RSA��Կ��������
	1. ���ѡ����������ȵ����� p �� q (ʵ��Ӧ���У�����������Խ�󣬾�Խ���ƽ�)��
	2. ����p��q�ĳ˻�n��n = pq��
	3. ����n��ŷ������ ��(n)
	4. ���ѡ��һ������e�������� 1 < e < ��(n)���� e �� ��(n) ���ʡ�
	5. ���� e ���� ��(n) ��ģ��Ԫ�� d��ʹ�� d * e �� 1 mod ��(n)���� d * e % ��(n) = 1
	6. ��Կ(e, n)  ˽Կ(d, n)
*/

class RSA
{
public:
	RSA()
	{
		// ��ʼ�����е���Կ
		GetKeys();
	}
	// ���ܽӿ�
	void Ecrept(const char* filename, const char* fileout);
	// ���ܽӿ�
	void Deecrpt(const char* filename, const char* fileout);

	// ��ȡ����
	DataType GetPrime();
	// ��ȡ��Կ��˽Կ�Ĺ�������
	DataType GetPkey(DataType prime1, DataType prime2);
	// ��ȡŷ������
	DataType GetOrla(DataType prime1, DataType prime2);
	// ��ȡ��Կ e
	DataType GetEkey(DataType orla);
	// ��ȡ˽Կ d
	DataType GetDkey(DataType ekey, DataType orla);
	// ��ȡ�����������Լ��
	DataType GetGcd(DataType data1, DataType data2);
	// �ж�һ�����Ƿ�������
	bool IsPrime(DataType data);
	// �����ݼ���
	DataType Ecrept(DataType data, DataType ekey, DataType pkey);
	// �����ݽ���
	DataType Deecrpt(DataType data, DataType dkey, DataType pkey);
	// ��ʼ����Կ����
	void GetKeys();
	// ���Ժ���
	void Test();
	Key RSA::GetAllKey();
private:
	Key _key;
};