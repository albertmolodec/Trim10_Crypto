#include <mpirxx.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

bool is_prime(int x) {
	for (int i = 2; i <= sqrt(x); i++) {
		if (x % i == 0) {
			return false;
		}
	}
	return true;
}


mpz_class NOD(mpz_class a, mpz_class b) {
	mpz_class nod = 1L;
	mpz_class tmp;
	if (a == 0L)
		return b;
	if (b == 0L)
		return a;
	if (a == b)
		return a;
	if (a == 1L || b == 1L)
		return 1L;
	while (a != 0 && b != 0) {
		if (a % 2L == 0L && b % 2L == 0L) {
			nod *= 2L;
			a /= 2L;
			b /= 2L;
			continue;
		}
		if (a % 2L == 0L && b % 2L != 0L) {
			a /= 2L;
			continue;
		}
		if (a % 2L != 0L && b % 2L == 0L) {
			b /= 2L;
			continue;
		}
		if (a > b) {
			tmp = a;
			a = b;
			b = tmp;
		}
		tmp = a;
		a = (b - a) / 2L;
		b = tmp;
	}
	if (a == 0)
		return nod * b;
	else
		return nod * a;
}

mpz_class NOK(mpz_class n1, mpz_class n2)
{
	return n1 * n2 / NOD(n1, n2);
}

mpz_class pow_mod(mpz_class a, mpz_class n, mpz_class mod)
{
	mpz_class res("1");
	if (n == 0) return 1;
	while (n>0)
	{
		if (n % 2 == 0)
		{
			n /= 2;
			a *= a;
			a %= mod;
		}
		else
		{
			n--;
			res *= a;
			res %= mod;
		}
	}
	return res % mod;
}

void print_vector(vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;
}

mpz_class get_k(vector<int> FB)
{
	mpz_class nk("1");
	for (int i = 0; i < FB.size(); i++) 
	{
		nk = NOK(nk, FB[i]);
	}
	return nk;
}


int main()
{
	vector<int> FB;
	int B = 7;

	int temp[100] = {2, 3, 4, 5, 7, 8, 9, 11, 13, 16, 17, 19, 23, 25, 27, 29, 31, 32, 37, 41, 43, 47, 49, 53, 59, 61, 64, 67, 71, 73};
	for (int i = 0; i < B; i++)
		FB.push_back(temp[i]);

	cout << "Factor base: ";
	print_vector(FB);

	mpz_class N("11970041221");
	mpz_class k(get_k(FB));
	cout << "k = " << k << endl;

	cout << endl << "N = " << N << endl;

	mpz_class ak;
	mpz_class a = 2;
	mpz_class f;
	bool flag = false;

	cout << endl << "Finding p..." << endl;

	while (a <= N && flag == false)
	{
		ak = pow_mod(a, k, N);
		f = NOD(ak - 1, N);
		if (f != 1)
			flag = true;
		a++;
	}
	cout << endl << "p = " << f << ", q = " << N / f << endl;
	system("pause");
}