#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<iostream>
#include<vector>
#include<climits>

using namespace std;

int soln(int pos, int n, bool implemented, vector<int> &costs, vector<vector<vector<int>>> &dp) {
    const int m = dp.size();
    
    if(pos == m) 
        return implemented ? INT_MIN : 0;
    else if(dp[pos][n][implemented] != INT_MAX)
        return dp[pos][n][implemented];
    else {
        int res = INT_MIN, curr;

        if(implemented) {
            curr = soln(pos + 1, n - 1, false, costs, dp);

            if(curr != INT_MIN)
                res = max<int>(res, curr + costs[pos]);
        }
        else if(n) {
            curr = soln(pos + 1, n, true, costs, dp);

            if(curr != INT_MIN)
                res = max<int>(res, curr - costs[pos]);
        }

        // Pass
        res = max<int>(res, soln(pos + 1, n, implemented, costs, dp));

        dp[pos][n][implemented] = res;
        return res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> costs(m);
    for(int i = 0; i < m; i++)
        cin >> costs[i];

    //{pos, strat}
    vector<vector<vector<int>>> dp(m, 
           vector<vector<int>>(n + 1, 
           vector<int>(2, INT_MAX)));

    cout << soln(0, n, false, costs, dp) << "\n";

    return 0;
}