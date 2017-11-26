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
	bool is_O;

public:
	void set_is_O(bool is_O) { this->is_O = is_O; }
	int get_is_O() { return this->is_O; }

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

	ePoint(int x, int y, int n, bool is_O, int a = 1, int b = 3)
	{
		set_xy(x, y);
		set_n(n);
		set_ab(a, b);
		set_is_O(is_O);
	}
	ePoint()
	{
		set_ab(1, 3);
		set_is_O(false);
	}
	~ePoint() {}

	ePoint operator = (ePoint p1)
	{
		return ePoint(this->x = p1.x, this->y = p1.y, this->n = p1.n, this->is_O = p1.is_O, this->a = p1.a, this->b = p1.b);
	}

	ePoint operator + (ePoint &p2)
	{
		ePoint p3;
		/*cout << "plus: ";
		print_point(*this);
		print_point(p2);*/
		int lambda = get_lambda(*this, p2);
		//cout << "lambda = " << lambda << endl;

		int x1 = this->get_x();
		int x2 = p2.get_x();
		int y1 = this->get_y();
		int N = this->get_n();		

		p3.set_x( mod(lambda * lambda - x1 - x2, N) );
		p3.set_y( mod((lambda*(x1-p3.get_x())-y1), N) );
		p3.set_n(N);

		return p3;
	}

	ePoint operator * (int count)
	{
		ePoint p3 = *this;
		for (int i = 1; i < count; i++)
			p3 = p3 + *this;
		return p3;
	}

	int mod(int a, int N)
	{
		if (a >= 0)
			return a % N;
		else
			return N - ((-a) % N);
	}

	int get_lambda(ePoint &p1, ePoint &p2)
	{
		int x1 = p1.get_x();
		int x2 = p2.get_x();
		int y1 = p1.get_y();
		int y2 = p2.get_y();
		int n = p1.get_n();
		int a = p1.get_a();	
		
		// TO DO: realize function "==" to compare points p1 and p2
		if (x1 == x2 && y1 == y2)
		{
			int inv = ext_ev(2 * y1, n);
			return (((3 * x1 * x1 + a) * inv) % n);
		}
		else
		{
			int inv = ext_ev(x2 - x1, n);
			return(((y2 - y1) * inv) % n);
		}
	}	

	int ext_ev(int a, int b)
	{
		if (a == 0)
		{
			this->set_is_O(true);
			cout << get_is_O() << " ";
		}

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

	static void get_points(vector<ePoint> &pts, int a, int b, int n)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (((j * j) % n) == ((i * i * i + a * i + b) % n))
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
		cout << "(" << p.get_x() << "," << p.get_y() << "). Is O? " << p.get_is_O() << endl;
		//cout << "(" << p.get_x() << "," << p.get_y() << ") ";
	}

	static int get_iG(vector<ePoint> &pts)
	{
		int order = pts.size() + 1;
		int max = 1;

		for (int i = 1; i < pts.size(); i++)
			if (order % i == 0)
				max = i;

		for (int i = 0; i < pts.size(); i++)
		{
			cout << i << endl;
			ePoint temp = pts[i] * max;
		}

		return max;
	}

	static void list_O(vector<ePoint> pts)
	{
		int j = 0;
		for (int i = 0; i < pts.size(); i++)
		{
			if (pts[i].get_is_O() == true)
			{
				ePoint::print_point(pts[i]);
				j++;
			}
		}
		cout << "=== " << j << " ===" << endl;
	}
};

bool is_simple(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
		if (n % i == 0)
			return false;
	return true;
}

int pow(int base, int exp)
{
	int result = base;
	for (int i = 1; i < exp; i++)
		result *= base;
	return result;
}

int main()
{
	srand(time(NULL));
	int n = 41;

	vector<ePoint> pts;
	ePoint::get_points(pts, 1, 3, n);

	cout << "Points of Elliptic Curve: " << endl;
	ePoint::print_points(pts);

	//int nA = rand() % (n - 3) + 2;
	//int nB = rand() % (n - 3) + 2;
	int nA = 3;
	int nB = 4;	
	
	cout << "Curve:" << endl;
	cout << "y ^ 2 = x ^ 3 + x + 3 (mod 41)" << endl;
	cout << "a = 1, b = 3, N = 41" << endl;

	int group_order = pts.size() + 1;
	cout << "Group order: " << group_order << endl << endl; // +1, because O  
	//int iG = rand() % pts.size(); // generate random G point
	int iG = 2;

	cout << "Generating point G... " << endl;
	int iG_temp = ePoint::get_iG(pts);
	cout << "iG = " << iG_temp << ". pts[iG] = ";
	ePoint::print_point(pts[iG_temp]);
	ePoint::print_points(pts);


	cout << endl << "List of good points: " << endl;
	cout << endl;
	ePoint::list_O(pts);

	cout << "Alice randomly selects private key (nA < N): " << nA << endl;
	cout << "Bob randomly selects private key (nB < N): " << nB << endl << endl;

	cout << "Alice calculates her public key: ";
	ePoint pA = pts[iG] * nA;
	ePoint::print_point(pA);
	cout << endl;
	cout << "Bob calculates his public key: ";
	ePoint pB = pts[iG] * nB;
	ePoint::print_point(pB);
	cout << endl;

	// int KA_x, KA_y, KB_x, KB_y;

	// multi_point(KA_x, KA_y, pA_x, pA_y, a, n, nB);
	// multi_point(KB_x, KB_y, pB_x, pB_y, a, n, nB);

	// cout << "Alice sends Bob her public key. Bob does the same." << endl;
	// cout << "Alice calculates common secret key: (" << KA_x << ", " << KA_y << ")" << endl;
	// cout << "Bob calculates common secret key: (" << KB_x << ", " << KB_y << ")" << endl << endl;

	// if (KA_x == KB_x && KA_y == KB_y)
	// 	cout << "Keys are the same. Success!" << endl;
	// else
	// 	cout << "Keys are the different. Wrong!" << endl;


	system("pause");
}