#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<iostream>
#include<vector>
#include<set>
#include<climits>

using namespace std;

bool solution(vector<int> &prices, int threshold) {
    const int n = prices.size();

    set<int> values { prices[n - 1] };
    for(int i = n - 2; i >= 0; i--) {
        int curr = prices[i];

        set<int>::iterator it = values.lower_bound(curr);
        if(it != values.begin() && *prev(it) + curr > threshold)
            return false;

        values.insert(curr);
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> prices(n);
    for(int i = 0; i < n; i++)
        cin >> prices[i];

    cout << solution(prices, m) << endl;

    return 0;
}