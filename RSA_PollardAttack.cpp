#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

bool is_prime(int x) {
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

long long NOD(long long n1, long long n2)
{
  long long div;
  if (n1 == n2) return n1;
  long long d = n1 - n2;
  if (d < 0) {
    d = -d;  
    div = NOD(n1, d);
  } 
  else
    div = NOD(n2, d); 
  return div;
}

long long NOK(long long n1, long long n2) 
{ 
  return n1 * n2 / NOD(n1, n2);
}

long long new_pow(long long a, long long d, long long n)
{
	long long b = 1;

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

void print_vector(vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;
}

long long get_k(vector<int> FB)
{
    long long nk=1;
    cout << "FB size = " << FB.size() << endl;
    for (int i = 0; i < FB.size(); i++) {
        nk=NOK(nk,FB[i]);
        cout << "i = " << i << ", nk = " << nk << endl;
    }
    cout << "k is found." << endl;
    return nk;
}


int main()
{
    vector<int> FB;

    //int temp[30] = {2, 3, 4, 5, 7, 8, 9, 11, 13, 16, 17, 19, 23, 25, 27, 29, 31, 32, 37, 41, 43, 47, 49, 53, 59, 61, 64, 67, 71, 73};
    int temp[14] = {2, 3, 4, 5, 7, 8, 9, 11, 13, 16, 17, 19, 23, 25};
    for (int i = 0; i < 12; i++)
        FB.push_back(temp[i]);

    cout << "Factor base: ";
    print_vector(FB);

    long long N = 11970041221;
    cout << "N = " << N << endl;
    long long k = get_k(FB);
    cout << "k = " << k << endl;

    long long ak;
    int a = 2;
    int f = 0;
    bool flag = false;

    cout << "'While' in process..." << endl;

    while (a <= N || flag == true)
    {
        ak = pow(a,k);
        f = NOD(ak-1, N);
        if (f != 1) 
            flag = true;
        a++;
    }
    cout << "p = " << f << endl;
}
