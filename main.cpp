#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <string>

#include <stdio.h>
#include <string.h>
#include <thread>
#include <unistd.h>
#include <chrono>

#include <cstdio>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
using namespace chrono;

const int EVERY = 700; //每个线程读取的数据量
const int TEST0 = 200; //阈值区间范围置1,其余算法
const int TEST1 = 1100;
const char CLASS = '1';

// string trainDataPwd = "/data/train_data.txt";
// string testFile = "/data/test_data.txt";
// string predictFile = "/projects/student/result.txt";
// string answerFile = "/projects/student/answer.txt";

string trainDataPwd = "./data/train_data.txt";
string testFile = "./data/test_data.txt";
string predictFile = "./result.txt";
string answerFile = "./data/answer.txt";

signed int zeroNumZero = 0, oneNumZero = 0, zeroNumThree = 0, oneNumThree = 0,
		   zeroNumOne = 0, oneNumOne = 0, zeroNumTwo = 0, oneNumTwo = 0;

signed int zeroClassOne[1000];

signed int oneClassOne[1000];

signed int zeroClassTwo[1000];

signed int oneClassTwo[1000];

signed int zeroClassThree[1000];

signed int oneClassThree[1000];

signed int zeroClassZero[1000];

signed int oneClassZero[1000];


inline signed int myatof(char *s)
{
	return (s[0] == '-') ? -1 * (1000 * (s[1] - '0') + 100 * (s[3] - '0') + 10 * (s[4] - '0') +
								 (s[5] - '0'))
						 : (1000 * (s[0] - '0') + 100 * (s[2] - '0') + 10 * (s[3] - '0') + (s[4] - '0'));
}

void readAndCal0(char *buf)
{
	char *p = buf;

	char tmp5[5];
	char tmp6[6];

	signed int mmtmp[1000];

	int pthnum = 0;

	while (pthnum < EVERY)
	{
		//将这一行的数据转码
		int i = 0;
		while (i <= 999)
		{
			//找到逗号,然后跳过数据,+1跳过逗号
			//两种情况,一种是0.123,一种是-0.123
			switch (*(p + 5) == ',')
			{
			case 0:
				memcpy(tmp6, p, 6);
				mmtmp[i] = myatof(tmp6);
				p = p + 7;
				break;
			case 1:
				memcpy(tmp5, p, 5);
				mmtmp[i] = myatof(tmp5);
				p = p + 6;
				break;
			}

			++i;
			//将类别找到,然后数据,再跳过\n,到下一行的开始
		}
		++pthnum;

		switch ((*p - '0') == 0)
		{
		case 0:
			++oneNumOne;
			for (signed int j = 0; j < 1000; ++j)
			{
				oneClassOne[j] = oneClassOne[j] +  mmtmp[j];
			}
			break;
		case 1:
			++zeroNumOne;
			for (signed int j = 0; j < 1000; ++j)
			{
				zeroClassOne[j] = zeroClassOne[j] + mmtmp[j];
			}
			break;
		}
		p = p + 2;
	}
}

void readAndCal1(int sum, char *buf)
{

	int offset = sum * 0.25;
	char *p = buf + offset;

	//将开头偏移到一行数据的起始位置
	if (*(p - 1) != '\n')
	{
		while (*p != '\n')
		{
			++p;
		}
		p = p + 1;
	}
	char tmp5[5];
	char tmp6[6];


	int pthnum = 0;
	signed int mmtmp[1000];

	while (pthnum < EVERY)
	{

		//将这一行的数据转码
		int i = 0;
		while (i <= 999)
		{
			//找到逗号,然后跳过数据,+1跳过逗号
			//两种情况,一种是0.123,一种是-0.123
			switch (*(p + 5) == ',')
			{
			case 0:
				memcpy(tmp6, p, 6);
				mmtmp[i] = myatof(tmp6);
				p = p + 7;
				break;
			case 1:
				memcpy(tmp5, p, 5);
				mmtmp[i] = myatof(tmp5);
				p = p +  6;
				break;
			}
			++i;
			//将类别找到,然后数据,再跳过\n,到下一行的开始
		}

		++pthnum;
		switch ((*p - '0') == 0)
		{
		case 0:
			++oneNumZero;
			for (signed int j = 0; j < 1000; ++j)
			{
				oneClassZero[j] = oneClassZero[j] + mmtmp[j];
			}
			break;
		case 1:
			++zeroNumZero;
			for (signed int j = 0; j < 1000; ++j)
			{
				zeroClassZero[j] = zeroClassZero[j] + mmtmp[j];
			}
			break;
		}

		p = p + 2;
	}
}

void readAndCal2(int sum, char *buf)
{
	int offset = sum * 0.5;
	char *p = buf + offset;

	//将开头偏移到一行数据的起始位置
	if (*(p - 1) != '\n')
	{
		while (*p != '\n')
		{
			++p;
		}
		p = p + 1;
	}

	char tmp5[5];
	char tmp6[6];

	int num = 0;
	int pthnum = 0;
	signed int mmtmp[1000];

	while (pthnum < EVERY)
	{

		//将这一行的数据转码
		int i = 0;
		while (i <= 999)
		{
			//找到逗号,然后跳过数据,+1跳过逗号
			//两种情况,一种是0.123,一种是-0.123
			switch (*(p + 5) == ',')
			{
			case 0:
				memcpy(tmp6, p, 6);
				mmtmp[i] = myatof(tmp6);
				p = p + 7;
				break;
			case 1:
				memcpy(tmp5, p, 5);
				mmtmp[i] = myatof(tmp5);
				p = p+ 6;
				break;
			}
			++i;
			//将类别找到,然后数据,再跳过\n,到下一行的开始
		}

		++pthnum;

		switch ((*p - '0') == 0)
		{
		case 0:
			++oneNumTwo;
			for (signed int j = 0; j < 1000; ++j)
			{
				oneClassTwo[j] = oneClassTwo[j] + mmtmp[j];
			}
			break;

		case 1:
			++zeroNumTwo;
			for (signed int j = 0; j < 1000; ++j)
			{
				zeroClassTwo[j] = zeroClassTwo[j] + mmtmp[j];
			}
			break;
		}

		p = p+ 2;
	}
}

void readAndCal3(int sum, char *buf)
{
	int offset = sum * 0.75;
	char *p = buf + offset;

	//将开头偏移到一行数据的起始位置
	if (*(p - 1) != '\n')
	{
		while (*p != '\n')
		{
			++p;
		}
		p = p + 1;
	}

	char tmp5[5];
	char tmp6[6];

	int pthnum = 0;
	signed int mmtmp[1000];

	while (pthnum < EVERY)
	{

		//将这一行的数据转码
		int i = 0;
		while (i <= 999)
		{
			//找到逗号,然后跳过数据,+1跳过逗号
			//两种情况,一种是0.123,一种是-0.123
			switch (*(p + 5) == ',')
			{
			case 0:
				memcpy(tmp6, p, 6);
				mmtmp[i] = myatof(tmp6);
				p = p+ 7;
				break;
			case 1:
				memcpy(tmp5, p, 5);
				mmtmp[i] = myatof(tmp5);
				p = p+ 6;
				break;
			}
			++i;
		}

		//将类别找到,然后数据,再跳过\n,到下一行的开始
		++pthnum;
		switch ((*p - '0') == 0)
		{
		case 0:
			++oneNumThree;
			for (signed int j = 0; j < 1000; ++j)
			{
				oneClassThree[j] = oneClassThree[j] + mmtmp[j];
			}
			break;
		case 1:
			++zeroNumThree;
			for (signed int j = 0; j < 1000; ++j)
			{
				zeroClassThree[j] = zeroClassThree[j] + mmtmp[j];
			}
			break;
		}

		p = p + 2;
	}
}

inline int myabs(int n){
	return (n ^ (n >> 31)) - (n >> 31);
}

char mmclass(signed int *zeroClass, signed int *oneClass, signed int *test_item)
{
	signed int eulerDisZero = 0, eulerDisOne = 0;
	signed int tmp1 = 0, tmp2 = 0;
	for (signed int i = 0; i < 1000; ++i)
	{
		tmp1 = myabs(zeroClass[i] - test_item[i]);
		tmp2 = myabs(oneClass[i] - test_item[i]);
		eulerDisZero = eulerDisZero + tmp1 * tmp1;
		eulerDisOne = eulerDisOne + tmp2 * tmp2;
	}
	return eulerDisZero < eulerDisOne ? '0' : '1';
}


char predict0[12500];
char predict1[12500];
char predict2[12500];
char predict3[12500];

int addr = 0, addr1 = 0, addr2 = 0, addr3 = 0;

void readAndCla0(int sum, char *buf, signed int *zeroClassOne, signed int *oneClassOne)
{
	int len = sum * 0.25;
	char *p = buf;
	char tmp5[5];
	char tmp6[6];

	signed int mmtmp[1000];

	char *result0 = predict0;
	char result[2];
	result[1] = '\n';

	while (*p && p - buf < len)
	{
		//将这一行的数据转码
		int i = 0;

		switch (*(p + 5) == ',')
		{
		case 0:
			memcpy(tmp6, p, 6);
			mmtmp[i] = myatof(tmp6);
			p = p + 7;
			break;
		case 1:
			memcpy(tmp5, p, 5);
			mmtmp[i] = myatof(tmp5);
			p = p+ 6;
			break;
		}

		//第一维度数据小于600,直接赋值1,跳过这一行
		switch (i == 0 && mmtmp[i] > TEST0 && mmtmp[i] < TEST1)
		{
		case 0:
			++i;
			while (i <= 998)
			{
				//找到逗号,然后跳过数据,+1跳过逗号
				//两种情况,一种是0.123,一种是-0.123
				switch (*(p + 5) == ',')
				{
				case 0:
					memcpy(tmp6, p, 6);
					mmtmp[i] = myatof(tmp6);
					p = p+ 7;
					break;
				case 1:
					memcpy(tmp5, p, 5);
					mmtmp[i] = myatof(tmp5);
					p = p+ 6;
					break;
				}
				++i;
			}
			memcpy(tmp5, p, 5);
			mmtmp[i] = myatof(tmp5);

			p = p+ 6;
			result[0] = mmclass(zeroClassOne, oneClassOne, mmtmp);
			memcpy(result0, result, 2);
			++addr;
			result0 = result0 + 2;
			break;
		case 1:
			p = p+ 5990;
			while (p - buf < len && *p != '\n')
			{
				++p;
			}
			p = p+ 1;

			result[0] = CLASS;
			memcpy(result0, result, 2);
			++addr;
			result0 = result0 + 2;
			break;
		}
	}
}

void readAndCla1(int sum, char *buf_, signed int *zeroClassOne, signed int *oneClassOne)
{
	int len = sum * 0.25;
	int offset = sum * 0.25;
	char *p = buf_ + offset;
	char *buf = buf_ + offset;

	char tmp5[5];
	char tmp6[6];
	int num = 0;

	signed int mmtmp[1000];
	char *result1 = predict1;
	char result[2];
	result[1] = '\n';
	while (*p && p - buf < len)
	{
		//将这一行的数据转码
		int i = 0;

		switch (*(p + 5) == ',')
		{
		case 0:
			memcpy(tmp6, p, 6);
			mmtmp[i] = myatof(tmp6);
			p =p+ 7;
			break;
		case 1:
			memcpy(tmp5, p, 5);
			mmtmp[i] = myatof(tmp5);
			p =p+ 6;
			break;
		}
		//第一维度数据小于600,直接赋值1,跳过这一行
		switch (i == 0 && mmtmp[i] > TEST0 && mmtmp[i] < TEST1)
		{
		case 0:
			++i;
			while (i <= 998)
			{
				//找到逗号,然后跳过数据,+1跳过逗号
				//两种情况,一种是0.123,一种是-0.123
				switch (*(p + 5) == ',')
				{
				case 0:
					memcpy(tmp6, p, 6);
					mmtmp[i] = myatof(tmp6);
					p =p+ 7;
					break;
				case 1:
					memcpy(tmp5, p, 5);
					mmtmp[i] = myatof(tmp5);
					p =p+ 6;
					break;
				}

				++i;
			}
			memcpy(tmp5, p, 5);
			mmtmp[i] = myatof(tmp5);

			p =p+ 6;
			result[0] = mmclass(zeroClassOne, oneClassOne, mmtmp);
			memcpy(result1, result, 2);
			++addr1;
			result1 =result1+ 2;
			break;
		case 1:
			p =p+ 5990;
			while (p - buf < len && *p != '\n')
			{
				++p;
			}
			p =p+ 1;

			result[0] = CLASS;
			memcpy(result1, result, 2);
			++addr1;
			result1 =result1+ 2;
			break;
		}
	}
}

void readAndCla2(int sum, char *buf_, signed int *zeroClassOne, signed int *oneClassOne)
{
	int len = sum * 0.25;
	int offset = sum * 0.5;
	char *p = buf_ + offset;
	char *buf = buf_ + offset;

	char tmp5[5];
	char tmp6[6];
	int num = 0;

	signed int mmtmp[1000];
	char *result2 = predict2;
	char result[2];
	result[1] = '\n';

	while (*p && p - buf < len)
	{
		//将这一行的数据转码
		int i = 0;

		switch (*(p + 5) == ',')
		{
		case 0:
			memcpy(tmp6, p, 6);
			mmtmp[i] = myatof(tmp6);
			p =p+ 7;
			break;
		case 1:
			memcpy(tmp5, p, 5);
			mmtmp[i] = myatof(tmp5);
			p =p+ 6;
			break;
		}
		//第一维度数据小于600,直接赋值1,跳过这一行
		switch (i == 0 && mmtmp[i] > TEST0 && mmtmp[i] < TEST1)
		{
		case 0:
			++i;
			while (i <= 998)
			{
				//找到逗号,然后跳过数据,+1跳过逗号
				//两种情况,一种是0.123,一种是-0.123
				switch (*(p + 5) == ',')
				{
				case 0:
					memcpy(tmp6, p, 6);
					mmtmp[i] = myatof(tmp6);
					p =p+ 7;
					break;
				case 1:
					memcpy(tmp5, p, 5);
					mmtmp[i] = myatof(tmp5);
					p =p+ 6;
					break;
				}

				++i;
			}
			memcpy(tmp5, p, 5);
			mmtmp[i] = myatof(tmp5);

			p =p+ 6;
			result[0] = mmclass(zeroClassOne, oneClassOne, mmtmp);
			memcpy(result2, result, 2);
			++addr2;
			result2 =result2+ 2;
			break;
		case 1:
			p =p+ 5990;
			while (p - buf < len && *p != '\n')
			{
				++p;
			}
			p =p+ 1;

			result[0] = CLASS;
			memcpy(result2, result, 2);
			++addr2;
			result2 =result2+ 2;
			break;
		}
	}
}

void readAndCla3(int sum, char *buf_, signed int *zeroClassOne, signed int *oneClassOne)
{
	int len = sum * 0.25;
	int offset = sum * 0.75;
	char *p = buf_ + offset;
	char *buf = buf_ + offset;

	char tmp5[5];
	char tmp6[6];
	int num = 0;
	signed int mmtmp[1000];

	char *result3 = predict3;
	char result[2];
	result[1] = '\n';

	while (*p && p - buf < len)
	{
		//将这一行的数据转码
		int i = 0;

		switch (*(p + 5) == ',')
		{
		case 0:
			memcpy(tmp6, p, 6);
			mmtmp[i] = myatof(tmp6);
			p =p+ 7;
			break;
		case 1:
			memcpy(tmp5, p, 5);
			mmtmp[i] = myatof(tmp5);
			p =p+ 6;
			break;
		}

		//第一维度数据小于600,直接赋值1,跳过这一行
		switch (i == 0 && mmtmp[i] > TEST0 && mmtmp[i] < TEST1)
		{
		case 0:
			++i;
			while (i <= 998)
			{
				//找到逗号,然后跳过数据,+1跳过逗号
				//两种情况,一种是0.123,一种是-0.123
				switch (*(p + 5) == ',')
				{
				case 0:
					memcpy(tmp6, p, 6);
					mmtmp[i] = myatof(tmp6);
					p =p+ 7;
					break;
				case 1:
					memcpy(tmp5, p, 5);
					mmtmp[i] = myatof(tmp5);
					p =p+ 6;
					break;
				}

				++i;
			}
			memcpy(tmp5, p, 5);
			mmtmp[i] = myatof(tmp5);

			p =p+ 6;
			result[0] = mmclass(zeroClassOne, oneClassOne, mmtmp);
			memcpy(result3, result, 2);
			++addr3;
			result3 =result3+ 2;
			break;
		case 1:
			p =p+ 5990;
			while (p - buf < len && *p != '\n')
			{
				++p;
			}
			p =p+ 1;

			result[0] = CLASS;
			memcpy(result3, result, 2);
			++addr3;
			result3 =result3+ 2;
			break;
		}
	}
}

signed int main(signed int argc, char *argv[])
{
	//mmap映射文件
	int fd = open(trainDataPwd.c_str(), O_RDONLY);
	int len = lseek(fd, 0, SEEK_END);
	char *buf = (char *)mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);


	std::thread thread0(readAndCal0, buf);

	std::thread thread1(readAndCal1, len, buf);

	std::thread thread2(readAndCal2, len, buf);

	std::thread thread3(readAndCal3, len, buf);

	thread0.join();
	thread1.join();
	thread2.join();
	thread3.join();

	int zeronum = zeroNumZero + zeroNumThree + zeroNumOne + zeroNumTwo;
	int onenum = oneNumOne + oneNumTwo + oneNumZero + oneNumThree;

	for (int i = 0; i < 1000; ++i)
	{
		zeroClassOne[i] = (zeroClassZero[i] + zeroClassThree[i] + zeroClassTwo[i] + zeroClassOne[i]) / zeronum;
		oneClassOne[i] = (oneClassZero[i] + oneClassThree[i] + oneClassTwo[i] + oneClassOne[i]) / onenum;
	}


	//输出
	int fd0 = open(testFile.c_str(), O_RDONLY);
	int len0 = lseek(fd0, 0, SEEK_END);
	char *buf0 = (char *)mmap(NULL, len0, PROT_READ, MAP_PRIVATE, fd0, 0);

	FILE *stream = fopen(predictFile.c_str(), "wb");
	std::thread thread4(readAndCla0, len0, buf0, zeroClassOne, oneClassOne);

	std::thread thread5(readAndCla1, len0, buf0, zeroClassOne, oneClassOne);

	std::thread thread6(readAndCla2, len0, buf0, zeroClassOne, oneClassOne);

	std::thread thread7(readAndCla3, len0, buf0, zeroClassOne, oneClassOne);

	thread4.join();
	fwrite(predict0, sizeof(char), addr * 2, stream);

	thread5.join();
	fwrite(predict1, sizeof(char), addr1 * 2, stream);

	thread6.join();
	fwrite(predict2, sizeof(char), addr2 * 2, stream);

	thread7.join();
	fwrite(predict3, sizeof(char), addr3 * 2, stream);

	/* 
	//test
	vector<int> result;
	char *tmp = new char[1];
	for (int i = 0; i < addr * 2; i += 2)
	{
		tmp[0] = predict0[i];
	 	result.push_back(atoi(tmp));
	}
	for (int i = 0; i < addr1 * 2; i += 2)
	{
		tmp[0] = predict1[i];
	 	result.push_back(atoi(tmp));
	}
	for (int i = 0; i < addr2 * 2; i += 2)
	{
		tmp[0] = predict2[i];
		result.push_back(atoi(tmp));
	}
	for (int i = 0; i < addr3 * 2; i += 2)
	{
		tmp[0] = predict3[i];
		result.push_back(atoi(tmp));
	}

	vector<float> answer_item;
	ifstream in_answerfile(answerFile.c_str());
	string answerlineStr;
	while (getline(in_answerfile, answerlineStr))
	{
		answer_item.push_back(stoi(answerlineStr));
	}

	signed int corretItem = 0;
	for (signed int i = 0; i < answer_item.size(); ++i)
	{
		if (answer_item[i] == result[i])
	 		++corretItem;
	}

	cout << "the prediction accuracy is" << ((float)corretItem) / answer_item.size() << endl;
	*/
	return 0;
}
