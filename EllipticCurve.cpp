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
	bool good;

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
		this->good = good;
	}
	ePoint()
	{
		set_ab(1, 3);
		set_n(41);
		this->good = false;
	}
	~ePoint() {}

	ePoint operator = (ePoint p1)
	{
		return ePoint(this->x = p1.x, this->y = p1.y, this->n = p1.n, this->good = p1.good, this->a = p1.a, this->b = p1.b);
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
		/*cout << "plus: ";
		print_point(*this);
		print_point(p2);*/
		bool is_good = false;
		int lambda = get_lambda(*this, p2, is_good);
		//cout << "lambda = " << lambda << endl;

		int x1 = this->get_x();
		int x2 = p2.get_x();
		int y1 = this->get_y();
		int N = this->get_n();		

		p3.set_x( mod(lambda * lambda - x1 - x2, N) );
		p3.set_y( mod((lambda*(x1-p3.get_x())-y1), N) );
		p3.set_n(N);
		p3.good = is_good;
		
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
		
		// TO DO: realize function "==" to compare points p1 and p2
		if (x1 == x2 && y1 == y2)
		{
			int inv = ext_ev(2 * y1, n);
			if (2 * y1 == 0)
			{
				is_good = true;
			}
			return ( mod(((3 * x1 * x1 + a) * inv), n));
		}
		else
		{
			int inv = ext_ev(x2 - x1, n);
			if (x2 - x1 == 0)
			{
				is_good = true;
			}
			return ( mod(((y2 - y1) * inv), n));			
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
		cout << "(" << p.get_x() << "," << p.get_y() << ") ";
	}

	static int get_iG(vector<ePoint> &pts, int &max_suborder)
	{
		int order = pts.size() + 1;
		int max = 1;
		vector<int> good_pts;

		for (int i = 1; i < pts.size(); i++)
			if (order % i == 0 && is_simple(i) == true)
				max = i;
		max_suborder = max;
		
		for (int i = 0; i < pts.size(); i++)
		{
			ePoint temp = pts[i] * max;
			if (temp.good == true)
				good_pts.push_back(i);
		}

	/*	cout << "Good points: ";
		for (int i = 0; i < good_pts.size(); i++)
		{
			ePoint::print_point(pts[good_pts[i]]);
		}
		cout << endl;*/

		int iG = rand() % good_pts.size();

		return good_pts[iG];
	}

	static bool is_simple(int n)
	{
		for (int i = 2; i <= sqrt(n); i++)
			if (n % i == 0)
				return false;
		return true;
	}
};

int main()
{
	srand(time(NULL));
	int n = 41;

	vector<ePoint> pts;
	
	ePoint::make_points(pts, 1, 3, n);

	cout << "Points of Elliptic Curve: " << endl;
	ePoint::print_points(pts);

	
	
	cout << endl << "Curve:" << endl;
	cout << "y^2 = x^3 + x + 3 (mod 41)" << endl;
	cout << "a = 1, b = 3, N = 41" << endl;

	int group_order = pts.size() + 1;
	cout << "Group order: " << group_order << endl << endl; // +1, because O  

	int max_suborder;
	cout << "Generating point G = ";
	int iG = ePoint::get_iG(pts, max_suborder);
	ePoint::print_point(pts[iG]);
	cout << endl;
	
	int nA = rand() % (max_suborder - 3) + 2;
	int nB = rand() % (max_suborder - 3) + 2;
	cout << "Alice randomly selects private key (nA < N): " << nA << endl;
	cout << "Bob randomly selects private key (nB < N): " << nB << endl << endl;

	cout << "Alice calculates her public key: ";
	ePoint pA = pts[iG] * nA;
	ePoint::print_point(pA);
	cout << endl;
	cout << "Bob calculates his public key: ";
	ePoint pB = pts[iG] * nB;
	ePoint::print_point(pB);
	cout << endl << endl;

	cout << "Alice sends Bob her public key. Bob does the same." << endl;
	cout << "Alice calculates common secret key: ";
	ePoint kA = pA * nB;
	ePoint::print_point(kA);
	cout << endl;
	cout << "Bob calculates common secret key: ";
	ePoint kB = pB * nA;
	ePoint::print_point(kB);
	cout << endl << endl;

	 if (kA == kB)
	 	cout << "Keys are the same. Success!" << endl;
	 else
	 	cout << "Keys are the different. Wrong!" << endl;


	system("pause");
}