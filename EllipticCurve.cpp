#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

int pow(int base, int exp)
{
	int result = base;
	for (int i = 1; i < exp; i++)
		result *= base;
	return result;
}

int mod(int a, int N)
{
	if (a >= 0)
		return a % N;
	else
		return N - ((-a) % N);
}

int ext_ev(int a, int b)
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

int get_lambda(int x1, int x2, int y1, int y2, int a, int N)
{
	if (x1 == x2 && y1 == y2)
	{
		// cout << "== " << ext_ev(2*y1, N) << " ";
		return mod((3 * x1 * x1 + a) * ext_ev(2 * y1, N), N);
	}
	else
	{
		// cout << "!= " << ext_ev(x2-x1, N) << " ";
		return mod((y2 - y1) * ext_ev(x2 - x1, N), N);
	}
}

int get_x3(int x1, int x2, int y1, int y2, int a, int N)
{
	int lambda = get_lambda(x1, x2, y1, y2, a, N);
	return mod((pow(lambda, 2) - x1 - x2), N);
}

int get_y3(int x1, int x2, int y1, int y2, int a, int N)
{
	int lambda = get_lambda(x1, x2, y1, y2, a, N);
	int x3 = get_x3(x1, x2, y1, y2, a, N);
	return mod((lambda * mod((x1 - x3), N) - y1), N);
}

void multi_point(int &result_x, int &result_y, int x, int y, int a, int N, int num)
{
	int x3 = x;
	int y3 = y;
	for (int i = 0; i < num; i++)
	{
		x3 = get_x3(x3, x, y3, y, a, N);
		y3 = get_y3(x3, x, y3, y, a, N);
	}
	result_x = x3;
	result_y = y3;
}

void get_points(vector<int> &p, int a, int b, int N)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (((j * j) % N) == ((i * i * i + a * i + b) % N))
			{
				p.push_back(i);
				p.push_back(j);
			}
}

void print_points(vector<int> p)
{
	for (int i = 0; i < p.size(); i += 2)
		cout << "(" << p[i] << "," << p[i + 1] << ")" << endl;
}

int main()
{
	srand(time(NULL));
	int a = 1;
	int b = 3;
	int n = 41;
	vector<int> p;
	// int nA = rand() % (n-2) + 2;
	// int nB = rand() % (n-2) + 2;
	int nA = 3;
	int nB = 4;
	int pA_x, pA_y, pB_x, pB_y;
	
	cout << "Curve:\ny^2 = x^3 + x + 3 (mod 41)" << endl;
	cout << "a = " << a << ", b = " << b << ", N = " << n << endl;

	get_points(p, a, b, n);
	// cout << "Points:" << endl;
	// print_points(p);
	cout << "Group order: " << p.size() / 2 + 1 << endl << endl ; // +1, because O
	//int iG = rand() % (p.size() / 2); // genarate random G point
	int iG = 2;
	cout << "Generating point G = (" << p[iG * 2] << ", " << p[iG * 2 + 1] << ")" << endl;

	cout << "Alice randomly selects private key (nA < N): " << nA << endl;
	cout << "Bob randomly selects private key (nB < N): " << nB << endl << endl;

	multi_point(pA_x, pA_y, p[iG * 2], p[iG * 2 + 1], a, n, nA);
	multi_point(pB_x, pB_y, p[iG * 2], p[iG * 2 + 1], a, n, nB);
 
	cout << "Alice calculates her public key: (" << pA_x << ", " << pA_y << ")" << endl;
	cout << "Bob calculates his public key: (" << pB_x << ", " << pB_y << ")" << endl << endl;

	int KA_x, KA_y, KB_x, KB_y;

	multi_point(KA_x, KA_y, pA_x, pA_y, a, n, nB);
	multi_point(KB_x, KB_y, pB_x, pB_y, a, n, nB);

	cout << "Alice sends Bob her public key. Bob does the same." << endl;
	cout << "Alice calculates common secret key: (" << KA_x << ", " << KA_y << ")" << endl;
	cout << "Bob calculates common secret key: (" << KB_x << ", " << KB_y << ")" << endl << endl;

	if (KA_x == KB_x && KA_y == KB_y)
		cout << "Keys are the same. Success!" << endl;
	else
		cout << "Keys are the different. Wrong!" << endl;




	cout << get_x3(3,3,19,19,1,41) << endl;
	cout << get_y3(3,3,19,19,1,41) << endl;
}