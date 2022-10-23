#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<iostream>
#include<unordered_map>
#include<string>

using namespace std;

int longestPalindrome(string &s) {
    unordered_map<char, int> freq;

    for(int i = 0; i < s.length(); i++)
        freq[s[i]]++;
    
    int sum = 0;
    bool isOneAvailable = false;

    for(unordered_map<char, int>::iterator it = freq.begin(); it != freq.end(); it++) {
        if(it->second == 1)
            isOneAvailable = true;
        else if(it->second%2 == 0)
            sum += it->second;
        else {
            sum += (it->second - 1);
            isOneAvailable = true;
        }
    }
    
    return sum + isOneAvailable;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    cout << longestPalindrome(s) << "\n";    

    return 0;
}