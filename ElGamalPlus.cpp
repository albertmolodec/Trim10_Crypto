#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

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

long long pow_mod(long long a, int n,
	int mod)
{
	long long res = 1;
	if (n == 0) return 1;
	while (n)
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

int inverse(int a, int b)
{
	int mod = b;
	int q, r, x1, x2, result;
	x2 = 1, x1 = 0;
	while (b > 0)
	{
		q = a / b, r = a % b;
		result = x2 - q * x1;
		a = b, b = r;
		x2 = x1, x1 = result;
	}
	if (x2 < 0)
	{
		result = x2 + mod;
	}
	else
	{
		result = x2;
	}
	return result;
}

vector<int> to_ascii_vector(string s)
{
	vector<int> s_ascii;
	for (int i = 0; i < s.length(); i++)
		s_ascii.push_back((int)s[i]);
	return s_ascii;
}

void print_ascii_vector(vector<int> s_ascii)
{
	for (int i = 0; i < s_ascii.size(); i++)
		cout << s_ascii[i] << " ";
	cout << endl;
}

bool is_simple(int n)
{

	for (int i = 2; i <= sqrt(n); i++)
		if (n%i == 0)
			return false;
	return true;
}

int get_simple_rand(int min, int max)
{
	vector<int> simple_numbers;
	for (int i = min; i < max; i++)
		if (is_simple(i))
			simple_numbers.push_back(i);
	int n = rand() % simple_numbers.size() + 0;
	return simple_numbers[n];
}

void print_ab(vector<int> ab)
{
	for (int i = 0; i < ab.size(); i++)
	{
		cout << ab[i] << " ";
		if (i % 2 == 1)
			cout << endl;
	}
}

int primitive_root_generator(int p) {
	vector<int> fact;
	int phi = p - 1, n = phi;
	for (int i = 2; i*i <= n; ++i)
		if (n % i == 0) {
			fact.push_back(i);
			while (n % i == 0)
				n /= i;
		}
	if (n > 1)
		fact.push_back(n);

	for (int res = 2; res <= p; ++res) {
		bool ok = true;
		for (size_t i = 0; i < fact.size() && ok; ++i)
			ok &= pow_mod(res, phi / fact[i], p) != 1;
		if (ok)  return res;
	}
	return -1;
}

int get_hash(string s, int mod)
{
	int h = 0;
	for (int i = 0; i < s.size(); i++)
		h += (int)s[i];
	return (h % mod);
}

vector<int> encrypt(int p, int g, int x, int y, string m)
{
	vector<int> m_ascii_vector;
	m_ascii_vector = to_ascii_vector(m);
	//cout << "ASCII-vector: ";
	//print_ascii_vector(m_ascii_vector);
	cout << "Size = " << m_ascii_vector.size() << endl;

	vector<int> ab;
	int a;
	int b;
	int k;
	for (int i = 0; i < m.size(); i++)
	{
		k = get_simple_rand(1, p - 1);
		a = pow_mod(g, k, p);
		b = (pow_mod(y, k, p) * m[i]) % p;
		ab.push_back(a);
		ab.push_back(b);
	}
	return ab;
}

string decrypt(vector<int> c, int x, int p)
{
	string s;
	int res;
	int a;
	int b;
	for (int i = 0; i < c.size(); i += 2)
	{
		a = c[i];
		b = c[i + 1];
		res = ((inverse(pow_mod(a, x, p), p)) * b) % p;
		s += (char)res;
	}
	return s;
}

vector<int> sign(int p, int g, int x, int y, string m)
{
	vector<int> m_ascii_vector;
	m_ascii_vector = to_ascii_vector(m);
	//print_ascii_vector(m_ascii_vector);
	int h = get_hash(m, p);
	cout << endl << "Message is signing...\n";

	vector<int> hrs;
	int r;
	int s;
	int k;

	k = get_simple_rand(1, p - 1);
	//cout << "\nk = " << k << endl;
	r = pow_mod(g, k, p);
	s = ( (h - x * r) * inverse(k, p - 1) ) % (p - 1);
	if (s < 0)
		s = s + p - 1;
	hrs.push_back(r);
	hrs.push_back(s);

	//cout << "Sign: r = " << hrs[0] << ", s = " << hrs[1] << endl;
	return hrs;
}

void check_sign(string m, int p, int g, int y, vector<int> hrs)
{
	int h = get_hash(m, p);
	cout << endl << "Sign is checking...\n";
	int left = pow_mod(y, hrs[0], p) * pow_mod(hrs[0],hrs[1],p) % p;
	int right = pow_mod(g,h,p);
	//cout << "Left = " << left << ". Right = " << right << "." << endl;;
	if (left == right)
		cout << "\nAll's good. You can trust this message." << endl << endl;
	else
		cout << "\nAlarm! You can't trust this message." << endl << endl;
}





int main()
{
	srand(time(NULL));
	int p = get_simple_rand(257, 1000); // random simple number, that more than M's	
	int g = primitive_root_generator(p); // primitive root of p
	int x = rand() % 10 + 1; // private key
	int y = pow_mod(g, x, p); // (p,g,y) - open key

	cout << "p = " << p << endl;
	cout << "g = " << g << endl;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;

	string m;
	cout << "Enter string: ";
	std::getline(std::cin, m);
	vector<int> ab = encrypt(p, g, x, y, m);

	//cout << "\nCipher text: " << endl;
	//print_ab(ab);

	string dec;
	dec = decrypt(ab, x, p);
	cout << "\nDecrypted text: " << dec << endl;

	vector<int> sign_of_m = sign(p, g, x, y, m);
	check_sign(m, p, g, y, sign_of_m);
	
	system("pause");
}