#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

void get_points(map<int,int> &p, int a, int b, int N)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cout << i << " " << j << endl;
            if ( ((j * j) % N) == ((i * i * i + a * i + b) % N) )
            {
                p.insert(pair<int,int> (i,j));
            }
        }
}

//int get_lambda()

void print_points(map<int,int> p)
{
    map<int,int>::iterator itMap;

    for (itMap = p.begin(); itMap != p.end(); itMap++)
        cout << itMap->first << " " << itMap->second << endl;

    cout << "p size = " << p.size() << endl;
}

int main()
{
    int a = 1;
    int b = 3;
    int N = 7;

    map <int, int> p;

    cout << "Points:" << endl;
    get_points(p,a,b,N);
    
    print_points(p);


}
