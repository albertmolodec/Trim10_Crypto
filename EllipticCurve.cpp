#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

class ePoint
{
public:
	int x;
	int y;
	int a;
	int b;
	int n;

	ePoint()
	{

	}

	ePoint(int x, int y, int a, int b, int n)
	{
		this->x = x;
		this->y = y;
		this->a = a;
		this->b = b;
		this->n = n;
	}

	ePoint operator = (ePoint p1)
	{
		return ePoint(this->x = p1.x, this->y = p1.y, this->a = p1.a, this->b = p1.n, this->x = p1.n);
	}

	ePoint operator + (ePoint &p)
	{
		return ;
	}

	int mod(int a, int N)
	{
		if (a >= 0)
			return a % N;
		else
			return N - ((-a) % N);
	}

	int ext_ev(int a, int mod)
	{
		int q, r, x1, x2, result;
		x2 = 1, x1 = 0;
		while (mod > 0)
		{
			q = a / mod, r = a % mod;
			result = x2 - q * x1;
			a = mod, mod = r;
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
};


int pow(int base, int exp)
{
	int result = base;
	for (int i = 1; i < exp; i++)
		result *= base;
	return result;
}



int get_lambda(int x1, int x2, int y1, int y2, int a, int N)
{
	if (x1 == x2 && y1 == y2)
		return mod((3 * x1 * x1 + a) * ext_ev(2 * y1, N), N);
	else
		return mod((y2 - y1) * ext_ev(x2 - x1, N), N);
}

int get_x3(int x1, int x2, int y1, int y2, int a, int N)
{
	int lambda = get_lambda(x1, x2, y1, y2, a, N);
	return mod((pow(lambda, 2) - x1 - x2), N);
}

int get_y3(int x1, int x2, int y1, int y2, int a, int N)
{
	int lambda = get_lambda(x1, x2, y1, y2, a, N);
	cout << "lambda = " << lambda << endl;
	return mod((lambda * mod((x1 - x2), N) - y1), N);
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
	int n = 7;
	vector<int> p;
	int nA = 3; // private key of Alice
	int nB = 5; // private key of Bob

	cout << "a = " << a << ", b = " << b << ", N = " << n << endl;
	
	get_points(p, a, b, n);
	cout << "Points:" << endl;
	print_points(p);
	cout << "Group order: " << p.size() / 2 + 1 << endl; // +1, because O

	int iG = rand() % (p.size() / 2);
	cout << "G = (" << p[iG * 2] << ";" << p[iG * 2 + 1] << ")" << endl;

	cout << "Q = (4,1) + (6,6) = (" << get_x3(4, 6, 1, 6, a, n) << ";" << get_y3(4, 6, 1, 6, a, n) << ")" << endl;



	


	system("pause");
}