#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<iostream>
#include<vector>
#include<list>

using namespace std;

bool dfs(int node, vector<bool> &visited, vector<list<int>> &adj_list) {
    if(visited[node])
        return true;
    
    visited[node] = true;

    bool flag = false;
    for(list<int>::iterator it = adj_list[node].begin(); 
        it != adj_list[node].end(); it++)
        flag |= dfs(*it, visited, adj_list);

    visited[node] = false;

    return flag;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<bool> visited(n, false);
    vector<list<int>> adj_list(n);

    int u, v;
    bool flag = true;
    for(int i = 0; i < m; i++) {
        cin >> u >> v;

        if(flag) {
            if(u == v)
                continue;
            
            adj_list[u].push_back(v);

            if(dfs(u, visited, adj_list))
                flag = false;
        }
    }

    if(flag)
        cout << "Eligible";
    else
        cout << "Ineligible";
    cout << "\n";

    return 0;
}