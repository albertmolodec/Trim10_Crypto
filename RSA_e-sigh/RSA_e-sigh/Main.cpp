#include <iostream>
#include <cmath>
#include <string>
#include <vector>


using namespace std;

void extended_euclid(long a, long b, long *x, long *y, long *d)
/* вычисление a * *x + b * *y = gcd(a, b) = *d */
{
	long q, r, x1, x2, y1, y2;
	if (b == 0) {
		*d = a, *x = 1, *y = 0;
		return;
	}

	x2 = 1, x1 = 0, y2 = 0, y1 = 1;
	while (b > 0) {
		q = a / b, r = a - q * b;
		*x = x2 - q * x1, *y = y2 - q * y1;
		a = b, b = r;
		x2 = x1, x1 = *x, y2 = y1, y1 = *y;
	}

	*d = a, *x = x2, *y = y2;
}

long inverse(long a, long n)
/* вычисление инверсии модуля n */
{
	long d, x, y;
	extended_euclid(a, n, &x, &y, &d);
	if (d == 1) return x;
	return 0;
}

long new_pow(long a, long d, long n)
{
	long b = 1;

	while (d)
	{
		if (d % 2 == 0)
		{
			d /= 2;
			a = (a * a) % n;
		}
		else
		{
			d--;
			b = (b * a) % n;
		}
	}
	return b;
}



int main()
{
	int p = 311;
	int q = 217;
	int n = p * q;
	int fi = (p - 1)*(q - 1);
	int e = 319;
	int d = inverse(e, fi);
	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "n = " << n << endl;
	cout << "fi = " << fi << endl;
	cout << "e = " << e << endl;
	cout << "d = " << d << endl;

	cout << "Enter string: ";
	string m;
	cin >> m;
	int m_size = m.length();
	std::vector<int> m_ascii;
	std::vector<int> c_ascii;

	cout << "Cipher text: ";
	for (int i = 0; i < m_size; i++)
	{
		m_ascii.push_back((int)m[i]);
		int temp = new_pow(m_ascii.back(), e, n);
		c_ascii.push_back(temp);
		cout << (char)c_ascii.back();
	}
	cout << endl;


	/*for (int i = 0; i < m_ascii.size(); i++)
	{
	cout << (char)c_ascii[i];
	}*/


	/*int m_new = new_pow(c, d, n);
	cout << "m_new = " << m_new << endl;*/




	system("pause");
}
