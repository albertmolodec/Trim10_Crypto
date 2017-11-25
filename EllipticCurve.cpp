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
	void set_xy(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void set_x(int x)	{		this->x = x;	}
	void set_y(int y)   {		this->y = y;	}
	void set_abn(int a, int b, int n)
	{
		this->a = a;
		this->b = b;
		this->n = n;
	}
	int get_x()	{ return this->x; }
	int get_y() { return this->y; }
	int get_a()	{ return this->a; }
	int get_b()	{ return this->b; }
	int get_n()	{ return this->n; }

	ePoint(int x, int y, int a = 1, int b = 3, int n = 41)
	{
		set_xy(x,y);
		set_abn(a,b,n);
	}
	ePoint() 
	{
		set_abn(1,3,41);
	}
	~ePoint() {	cout << "Memory has been cleaned." << endl;	}	

	ePoint operator = (ePoint p1)
	{
		return ePoint(this->x = p1.x, this->y = p1.y, this->a = p1.a, this->b = p1.n, this->n = p1.n);
	}

	ePoint operator + (ePoint p2)
	{
		ePoint p3;
		int lambda = get_lambda(*this, p2);
		int dx = p2.get_x() - this->get_x();
		int dy = p2.get_y() - this->get_y();

		if (dx < 0)
			dx += this->get_n();
		if (dy > 0)
			dy += this->get_n();
		
		if (lambda < 0)
			lambda += this->get_n();

		p3.set_x( (lambda*lambda - this->get_x() - p2.get_x() ) % this->get_n() );
		p3.set_y( (lambda * (this->get_x() - p3.get_x()) - this->get_y()) & this->get_n());

		if (p3.get_x() < 0)
			p3.x += this->get_n();
		if (p3.get_y() < 0)
			p3.y += this->get_n();

		return p3;		
	}

	// int operator % (int N)
	// {
	// 	return mod(this->get_a(), N);
	// }

	

	int get_lambda(ePoint p1, ePoint p2)
	{
		int x1 = p1.get_x();
		int x2 = p2.get_x();
		int y1 = p1.get_y();
		int y2 = p2.get_y();
		int n = p1.get_n();
		int a = p1.get_n();

		if (x1 == x2 && y1 == y2)
			return ((3 * x1 * x1 + a) * ext_ev(2 * y1, n)) % n;
		else
			return ((y2-y1) * ext_ev(x2-x1, n)) % n;
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

	static void get_points(vector<ePoint> &pts, int a, int b, int n)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (((j * j) % n) == ((i * i * i + a * i + b) % n))
				{
					ePoint pt(i,j);
					pts.push_back(pt);
				}
	}

	static void print_points(vector<ePoint> pts)
	{
		for (int i = 0; i < pts.size(); i++)
			cout << "(" << pts[i].x << "," << pts[i].y << ")" << " ";
		cout << endl;
	}
};

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
	ePoint default_ePoint(0,0);

	ePoint::get_points(pts, 1, 3, n);

	cout << "Points of Elliptic Curve: " << endl;
	ePoint::print_points(pts);

	int nA = rand() % (n-3) + 2;
	int nB = rand() % (n-3) + 2;
	int pA_x, pA_y, pB_x, pB_y;
	
	cout << "Curve:\ny^2 = x^3 + x + 3 (mod 41)" << endl;
	cout << "a = 1, b = 3, N = 41" << endl;

	cout << "Group order: " << pts.size() + 1 << endl << endl ; // +1, because O  
	int iG = rand() % pts.size(); // genarate random G point
	
	cout << "Generating point G...\nG = (" << pts[iG].get_x() << ", " << pts[iG].get_y() << ")" << endl;

	cout << "Alice randomly selects private key (nA < N): " << nA << endl;
	cout << "Bob randomly selects private key (nB < N): " << nB << endl << endl;

	cout << "Testing sum... (" << (default_ePoint+pts[iG]).get_x() << ", " << (default_ePoint+pts[iG]).get_y() << ")" << endl;

	// multi_point(pA_x, pA_y, p[iG * 2], p[iG * 2 + 1], a, n, nA);
	// multi_point(pB_x, pB_y, p[iG * 2], p[iG * 2 + 1], a, n, nB);
 
	// cout << "Alice calculates her public key: (" << pA_x << ", " << pA_y << ")" << endl;
	// cout << "Bob calculates his public key: (" << pB_x << ", " << pB_y << ")" << endl << endl;

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
}