#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <bitset>

using namespace std;

// 1 symbol = 1 byte
// https://ru.wikipedia.org/wiki/√Œ—“_28147-89

int blocks_count(string s)
{
	if (s.size() % 8 != 0)
		return s.size() / 8 + 1;
	else
		return s.size() / 8;
}

void complete_string(string &s)
{
	if (s.size() % 8 != 0)
		for (int i = s.size(); i < blocks_count(s) * 8; i++)
			s += ' ';
}

void generate_key(vector<unsigned long> &key)
{
	for (int i = 0; i < 8; i++)
	{
		key[i] = rand() * rand() * (rand() % 4 + 1);
		key[i + 8] = key[i];
		key[i + 16] = key[i];
		key[31 - i] = key[i];
	}
}

void reverse_key(vector<unsigned long> &key)
{
	vector<unsigned long> temp_key(key.size());
	temp_key = key;
	for (int i = 0; i < 32; i++)
	{
		key[i] = temp_key[31 - i];
	}
}

void print_vector(vector<unsigned long> a)
{
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
		if (i % 8 == 7)
			cout << endl;
	}
	cout << endl;
}

void shuffle(unsigned char *N)
{
	unsigned char S[8][16] = // Table id-GostR3411-94-TestParamSet. Using in the Central Bank of the Russian Federation
	{
		0x4,0xA,0x9,0x2,0xD,0x8,0x0,0xE,0x6,0xB,0x1,0xC,0x7,0xF,0x5,0x3,
		0xE,0xB,0x4,0xC,0x6,0xD,0xF,0xA,0x2,0x3,0x8,0x1,0x0,0x7,0x5,0x9,
		0x5,0x8,0x1,0xD,0xA,0x3,0x4,0x2,0xE,0xF,0xC,0x7,0x6,0x0,0x9,0xB,
		0x7,0xD,0xA,0x1,0x0,0x8,0x9,0xF,0xE,0x4,0x6,0xC,0xB,0x2,0x5,0x3,
		0x6,0xC,0x7,0x1,0x5,0xF,0xD,0x8,0x4,0xA,0x9,0xE,0x0,0x3,0xB,0x2,
		0x4,0xB,0xA,0x0,0x7,0x2,0x1,0xD,0x3,0x6,0x8,0x5,0x9,0xC,0xF,0xE,
		0xD,0xB,0x4,0x1,0x3,0xF,0x5,0x9,0x0,0xA,0xE,0x7,0x6,0x8,0x2,0xC,
		0x1,0xF,0xD,0x0,0x5,0x7,0xA,0x4,0x9,0x2,0x3,0xE,0x6,0xB,0x8,0xC
	};
	for (int i = 0; i < 8; i++)
		N[i] = S[i][(int)N[i]];
}

void EncryptDecrypt(string s)
{
	const int key_size = 32;
	vector<unsigned long> key(key_size);

	string d[8];
	unsigned char dest[8];

	int blocks = blocks_count(s);
	cout << "Number of blocks: " << blocks << endl << endl;
	complete_string(s);

	generate_key(key);
	cout << "Key: " << endl;
	print_vector(key);

	unsigned long temp_right;
	unsigned long temp;
	unsigned char L[8];
	unsigned char R[8];
	unsigned long left;
	unsigned long right;

	for (int i = 0; i < blocks; i++)
	{
		left = s[i * 8] * 256 * 256 * 256 + s[i * 8 + 1] * 256 * 256 + s[i * 8 + 2] * 256 + s[i * 8 + 3];
		right = s[i * 8 + 4] * 256 * 256 * 256 + s[i * 8 + 5] * 256 * 256 + s[i * 8 + 6] * 256 + s[i * 8 + 7];

		for (int j = 0; j < 32; j++)
		{
			// REMEMBER THIS
			temp_right = right;

			// + MOD 2^32
			right = (right + key[j]) % 4294967296;

			// TO BLOCKS 
			R[0] = right >> 28;
			temp = right & 0x0F000000;
			R[1] = temp >> 24;
			temp = right & 0x00F00000;
			R[2] = temp >> 20;
			temp = right & 0x000F0000;
			R[3] = temp >> 16;
			temp = right & 0x0000F000;
			R[4] = temp >> 12;
			temp = right & 0x00000F00;
			R[5] = temp >> 8;
			temp = right & 0x000000F0;
			R[6] = temp >> 4;
			temp = right & 0x0000000F;
			R[7] = temp;

			// SHUFFLE
			shuffle((unsigned char*)R);

			// CONCATENATION
			right = R[0] << 28;
			right = right | (R[1] << 24);
			right = right | (R[2] << 20);
			right = right | (R[3] << 16);
			right = right | (R[4] << 12);
			right = right | (R[5] << 8);
			right = right | (R[6] << 4);
			right = right | R[7];

			// CYCLICAL SHIFT
			right = (right << 11) | (right >> (32 - 11));

			// XOR
			right = left ^ right;
			left = temp_right;
		}

		temp = left & 0xFF000000;
		dest[0] = temp >> 24;
		temp = left & 0x00FF0000;
		dest[1] = temp >> 16;
		temp = left & 0x0000FF00;
		dest[2] = temp >> 8;
		temp = left & 0x000000FF;
		dest[3] = temp;
		temp = right & 0xFF000000;
		dest[4] = temp >> 24;
		temp = right & 0x00FF0000;
		dest[5] = temp >> 16;
		temp = right & 0x0000FF00;
		dest[6] = temp >> 8;
		temp = right & 0x000000FF;
		dest[7] = temp;

		cout << "Cipher: " << (char)dest[0] << " " << (char)dest[1] << " " << (char)dest[2] << " " << (char)dest[3] << " " <<
			(char)dest[4] << " " << (char)dest[5] << " " << (char)dest[6] << " " << (char)dest[7] << endl << endl;
	}

	reverse_key(key);
	cout << "Reverse key: " << endl;
	print_vector(key);

	for (int i = 0; i < blocks; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			// REMEMBER THIS
			temp_right = right;

			// + MOD 2^32
			right = (right + key[j]) % 4294967296;

			// TO BLOCKS 
			R[0] = right >> 28;
			temp = right & 0x0F000000;
			R[1] = temp >> 24;
			temp = right & 0x00F00000;
			R[2] = temp >> 20;
			temp = right & 0x000F0000;
			R[3] = temp >> 16;
			temp = right & 0x0000F000;
			R[4] = temp >> 12;
			temp = right & 0x00000F00;
			R[5] = temp >> 8;
			temp = right & 0x000000F0;
			R[6] = temp >> 4;
			temp = right & 0x0000000F;
			R[7] = temp;

			// SHUFFLE
			shuffle((unsigned char*)R);
			
			// CONCATENATION
			right = R[0] << 28;
			right = right | (R[1] << 24);
			right = right | (R[2] << 20);
			right = right | (R[3] << 16);
			right = right | (R[4] << 12);
			right = right | (R[5] << 8);
			right = right | (R[6] << 4);
			right = right | R[7];

			// CYCLICAL SHIFT
			right = (right << 11) | (right >> (32 - 11));

			// XOR
			right = left ^ right;
			left = temp_right;
 		}

		temp = left & 0xFF000000;
		dest[0] = temp >> 24;
		temp = left & 0x00FF0000;
		dest[1] = temp >> 16;
		temp = left & 0x0000FF00;
		dest[2] = temp >> 8;
		temp = left & 0x000000FF;
		dest[3] = temp;
		temp = right & 0xFF000000;
		dest[4] = temp >> 24;
		temp = right & 0x00FF0000;
		dest[5] = temp >> 16;
		temp = right & 0x0000FF00;
		dest[6] = temp >> 8;
		temp = right & 0x000000FF;
		dest[7] = temp;

		cout << "Decrypted message: " << (char)dest[0] << " " << (char)dest[1] << " " << (char)dest[2] << " " << (char)dest[3] << " " <<
		(char)dest[4] << " " << (char)dest[5] << " " << (char)dest[6] << " " << (char)dest[7] << endl << endl;
	}
}

int main()
{
	srand(time(NULL));
	string plaintext;

	cout << "Enter string: ";
	getline(cin, plaintext);

	EncryptDecrypt(plaintext);

	system("pause");
}