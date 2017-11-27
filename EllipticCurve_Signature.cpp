#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

class ePoint
{
private:
	int x;
	int y;
	int a;
	int b;
	int n;

public:
	bool is_good;

	void set_xy(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void set_x(int x) { this->x = x; }
	void set_y(int y) { this->y = y; }
	void set_n(int n) { this->n = n; }
	void set_ab(int a, int b)
	{
		this->a = a;
		this->b = b;
	}

	int get_x() { return this->x; }
	int get_y() { return this->y; }
	int get_a() { return this->a; }
	int get_b() { return this->b; }
	int get_n() { return this->n; }

	ePoint(int x, int y, int n, bool good, int a = 1, int b = 3)
	{
		set_xy(x, y);
		set_n(n);
		set_ab(a, b);
		this->is_good = good;
	}
	ePoint()
	{
		set_ab(1, 3);
		set_n(109);
		this->is_good = false;
	}
	~ePoint() {}

	ePoint operator = (ePoint p1)
	{
		return ePoint(this->x = p1.x, this->y = p1.y, this->n = p1.n, this->is_good = p1.is_good, this->a = p1.a, this->b = p1.b);
	}

	bool operator == (ePoint &p)
	{
		if (this->x == p.x && this->y == p.y && this->a == p.a && this->b == p.b && this->n == p.n)
			return true;
		else
			return false;
	}

	ePoint operator + (ePoint &p2)
	{
		ePoint p3;
		bool is_good = false;
		int lambda = get_lambda(*this, p2, is_good);

		int x1 = this->get_x();
		int x2 = p2.get_x();
		int y1 = this->get_y();
		int N = this->get_n();

		p3.set_x(mod(lambda * lambda - x1 - x2, N));
		p3.set_y(mod((lambda*(x1 - p3.get_x()) - y1), N));
		p3.set_n(N);
		p3.is_good = is_good;

		return p3;
	}

	ePoint operator * (int count)
	{
		ePoint p3 = *this;
		for (int i = 1; i < count; i++)
		{
			p3 = p3 + *this;
		}
		return p3;
	}

	int mod(int a, int N)
	{
		if (a >= 0)
			return a % N;
		else
			return N - ((-a) % N);
	}

	int get_lambda(ePoint &p1, ePoint &p2, bool &is_good)
	{
		int x1 = p1.get_x();
		int x2 = p2.get_x();
		int y1 = p1.get_y();
		int y2 = p2.get_y();
		int n = p1.get_n();
		int a = p1.get_a();

		if (p1 == p2)
		{
			int inv = ext_ev(2 * y1, n);
			if (2 * y1 == 0)
			{
				is_good = true;
			}
			return (mod(((3 * x1 * x1 + a) * inv), n));
		}
		else
		{
			int inv = ext_ev(x2 - x1, n);
			if (x2 - x1 == 0)
			{
				is_good = true;
			}
			return (mod(((y2 - y1) * inv), n));
		}
	}

	int ext_ev(int a, int b)
	{
		if (a < 0)
			a = mod(a, b);

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
			result = x2 + mod;
		else
			result = x2;

		return result;
	}

	static void make_points(vector<ePoint> &pts, int a, int b, int n)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (mods((j * j), n) == mods((i * i * i + a * i + b), n))
				{
					ePoint pt(i, j, n, false);
					pts.push_back(pt);
				}
	}

	static void print_points(vector<ePoint> pts)
	{
		for (int i = 0; i < pts.size(); i++)
			print_point(pts[i]);
		cout << endl;
	}

	static void print_point(ePoint p)
	{
		cout << "(" << p.get_x() << "," << p.get_y() << ") ";
	}

	static int get_iG(vector<ePoint> &pts, int &max_suborder)
	{
		int order = pts.size() + 1;
		int max = 1;
		vector<int> good_pts;

		for (int i = 1; i < pts.size(); i++)
			if (order % i == 0)
				max = i;
		max_suborder = max;

		for (int i = 0; i < pts.size(); i++)
		{
			ePoint temp = pts[i] * max;
			if (temp.is_good == true)
				good_pts.push_back(i);
		}

		int iG = rand() % good_pts.size();

		return good_pts[iG];
	}

	static int mods(int a, int N)
	{
		if (a >= 0)
			return a % N;
		else
			return N - ((-a) % N);
	}
};

int mod(int a, int N)
{
	if (a >= 0)
		return a % N;
	else
		return N - ((-a) % N);
}

int ext_ev(int a, int b)
{
	if (a < 0)
		a = mod(a, b);

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
		result = x2 + mod;
	else
		result = x2;

	return result;
}


int get_hash(string s, int mod)
{
	int h = 0;
	for (int i = 0; i < s.size(); i++)
		h += (int)s[i];
	return (h % mod);
}

int main()
{
	srand(time(NULL));
	int p = 109; // Field
	int n; // PUBLIC KEY
	vector<ePoint> pts; // PUBLIC KEY
	ePoint::make_points(pts, 1, 3, p);
	int iP = ePoint::get_iG(pts, n);
	ePoint P = pts[iP]; // PUBLIC KEY
	int d = rand() % (n - 1) + 1; // PRIVATE KEY
	ePoint Q = P * d; // PUBLIC KEY

	cout << "Public key:  ";
	cout << "Ep on field = " << p << endl;
	cout << "             n = " << n << endl;
	cout << "             P = ";
	ePoint::print_point(P);
	cout << "\n             Q = ";
	ePoint::print_point(Q);
	cout << "\nPrivate key: ";
	cout << "d = " << d << endl << endl;

	string name = "Albert";
	cout << "Author: " << name << endl << endl;

	cout << "=== SIGN ===" << endl << endl;
	
	int r;
	int s;
	int k;
	ePoint point1;
	do
	{
		k = rand() % (n - 1) + 1;
		point1 = P * k;
		int x1 = point1.get_x();
		r = mod(x1, n);
		s = mod(ext_ev(k, n) * (get_hash(name, n) + d * r), n);
	} while (r == 0 || s == 0);
	
	cout << "Session key k = " << k << endl;
	cout << "Hash = " << get_hash(name, n) << endl;
	cout << "point1 = ";
	ePoint::print_point(point1);
	cout << "\nr = " << r << endl;
	cout << "s = " << s << endl << endl;

	cout << "=== CHECK SIGN ===" << endl << endl;

	if (r >= 0 && r <= n - 1 && s >= 0 && s <= n - 1)
	{
		int w = ext_ev(s, n);
		int hash = get_hash(name, n);
		int u1 = mod(w * hash, n);
		int u2 = mod(w * r, n);
		ePoint x0y0 = P * u1 + Q * u2;
		int v = mod(x0y0.get_x(), n);

		cout << "w = " << w << endl;
		cout << "Hash = " << hash << endl;
		cout << "u1 = " << u1 << endl;
		cout << "u2 = " << u2 << endl;
		cout << "x0, y0 = ";
		ePoint::print_point(x0y0);

		if (v == r)
			cout << endl << endl << "v = " << v << ", r = " << r << "." << endl << "Sign is valid. Congrats!" << endl << endl;
		else
			cout << endl << endl << "Error 2. Sign is not valid. Try again." << endl << endl;
	}
	else
		cout << endl << endl << "Error 1. Sign is not valid. Try again." << endl << endl;
	


	system("pause");
}