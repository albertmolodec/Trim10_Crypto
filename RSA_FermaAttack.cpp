
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>


using namespace std;

int main()
{
    // long long N = 11970041221; // Albert
    long long N = 269603579723; // Ksyusha
    cout << "Plain N = " << N << endl;
    long int k = (int)sqrt(N)+1;
    
    long int y_square = k * k - N;
    long int x, y;
    long int d = 1;

    if ((int)sqrt(y_square) == sqrt(y_square))
    {
        y = sqrt(y_square);
        x = sqrt(N+y_square);
    }

    double eps = 0.01;

    do
    {
        y = sqrt(y_square);
        x = sqrt(N+y_square);
        
        if ((long int)sqrt(y_square)>(N/2))
        {
            cout << "Not found" << endl;
        }
        else 
        {
            y_square=y_square+2*k+d;
            d+=2;
        }
    }
    while (sqrt(y_square) - (int)sqrt(y_square) > eps);
    int p_new = x - y;
    int q_new = x + y;
    long long N_new = 0;
    N_new = p_new * 2 * q_new / 2;
    cout << "p_new = " << p_new << ", q_new = " << q_new << endl; 
}
