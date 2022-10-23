#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

typedef unsigned long long int ulli;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ulli num;
    cin >> num;
    
    if(!(num%2) && num%4)
        cout << "PASS";
    else if(num%2) 
        cout << "SELL";
    else
        cout << "BUY";
    cout << "\n";

    return 0;
}