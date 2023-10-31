#include <iostream>
#include <random>
#include <sstream>
using namespace std;

const int Length = 2500;

struct bites
{
	unsigned short bit1 : 1;
	unsigned short bit2 : 1;
	unsigned short bit3 : 1;
	unsigned short bit4 : 1;
	unsigned short bit5 : 1;
	unsigned short bit6 : 1;
	unsigned short bit7 : 1;
	unsigned short bit8 : 1;

	bool operator[](int index) const
	{
		switch (index)
		{
			case 0: {return bit1; }
			case 1: {return bit2; }
			case 2: {return bit3; }
			case 3: {return bit4; }
			case 4: {return bit5; }
			case 5: {return bit6; }
			case 6: {return bit7; }
			case 7: {return bit8; }
		}
	}
};

union byte
{
	unsigned char symbol;
	bites bit;
};

void random_key(byte* arr) //Key generator
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 255);

	string randomBytes = "";
	for (int i = 0; i < Length; i++)
	{
		int randomInt = dis(gen); 
		
		randomBytes += (char)randomInt;
	}

	// Write the key in the array
	for (int i = 0; i < Length; i++)
	{
		arr[i].symbol = randomBytes[i];
	}
}

bool mono(byte* arr) // 2.1
{
	short one = 0;
	for (int i = 0; i < 2500; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arr[i].bit[j] == 1) one++;
		}
	}

	if (one >= 9654 && one <= 10346)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool max_lenght_bites(byte* arr) // 2.2
{
	short max = 0;
	bool now = arr[0].bit.bit8;
	for (int i = 0; i < Length; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			if (arr[i].bit[j] == now) max++;
			else
			{
				now = arr[i].bit[j];
				max = 1;
			}

			if (max == 36) return false;
		}
	}
	return true;
}

bool poker(byte* arr) // 2.3
{
	int summ = 0;
	for (int i = 0; i < pow(2, 4); i++)
	{
		char s = (char)i;
		short count = 0;
		for (int j = 0; j < Length; j++)
		{
			if (s == (arr[j].symbol >> 4))
			{
				count++;
			}

			if (s == (arr[j].symbol & 0x0F))
			{
				count++;
			}
		}
		summ += pow(count, 2);
	}
	double X3 = (pow(2, 4) / (Length * 2)) * summ - (Length * 2);

	if (X3 >= 1.03 && X3 <= 57.4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool count_series(byte* arr) //2.4
{
	short count = 0;
	short series[2][6];
	bool now = arr[0].bit.bit8;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			series[i][j] = 0;
		}
	}

	for (int i = 0; i < Length; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			if (arr[i].bit[j] == now) count++;
			else
			{
				switch (count)
				{
				case 1: {series[now][0]++; break; }
				case 2: {series[now][1]++; break; }
				case 3: {series[now][2]++; break; }
				case 4: {series[now][3]++; break; }
				case 5: {series[now][4]++; break; }
				default: {series[now][5]++; break; }
				}
				now = arr[i].bit[j];
				count = 1;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			switch (j)
			{
			case 0: {if (series[i][j] < 2267 || series[i][j] > 2733) return false; break; }
				case 1: {if (series[i][j] < 1079 || series[i][j] > 1421) return false; break; }
				case 2: {if (series[i][j] < 502 || series[i][j] > 748) return false; break; }
				case 3: {if (series[i][j] < 223 || series[i][j] > 402) return false; break; }
				case 4: {if (series[i][j] < 90 || series[i][j] > 223) return false; break; }
				case 5: {if (series[i][j] < 90 || series[i][j] > 223) return false; break; }
			}
		}
	}
	return true;
}

int main()
{
	byte arr[Length];
	random_key(arr);
	cout << (mono(arr) == 1 ? "Test 1: successful" : "Test 1: fail") << endl;
	cout << (max_lenght_bites(arr) == 1 ? "Test 2: successful" : "Test 2: fail") << endl;
	cout << (count_series(arr) == 1 ? "Test 4: successful" : "Test 4: fail") << endl;
	cout << (poker(arr) == 1 ? "Test 4: successful" : "Test 4: fail") << endl;
	cout << endl;

	if (mono(arr) && max_lenght_bites(arr) && count_series(arr) && poker(arr))
	{
		cout << "Correct key!" << endl;
	}
	else
	{
		cout << "Key isn't correct!" << endl;
	}

	return 0;
}