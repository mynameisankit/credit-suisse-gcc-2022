#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<iostream>
#include<vector>

using namespace std;

int dfs(int node, int curr_dist,
        vector<int>& edges,
        vector<vector<int>> &dist) {
    if(node == -1 || dist[node][0] != -1)
        return node;
    else {
        dist[node][0] = curr_dist;
        
        if(edges[node] == -1 || dist[edges[node]][1] == -1)
            dist[node][1] = dfs(edges[node], curr_dist + 1,
                                edges, dist);
        
        dist[node][0] = -1;
        
        return dist[node][1] == node ? -1 : dist[node][1];
    }
}

void solution(vector<int> &edges) {
    const int n = edges.size();
        
    vector<vector<int>> dist(n, vector<int>(2, -1));
    for(int i = 1; i < n; i++) {
        if(dist[i][1] != -1)
            continue;
            
        dfs(i, 0, edges, dist);
    }
    for(int i = 1; i < n; i++) {
        if(dist[i][1] != -1) {
            if(dist[dist[i][1]][0] == -1)
                dist[dist[i][1]][0] = 1;
            else
                dist[dist[i][1]][0]++;
        }
    }

    for(int i = 1; i < n; i++) {
        if(dist[i][1] != -1)
            cout << dist[dist[i][1]][0];
        else
            cout << dist[i][0];
        cout << " ";
    }
    cout << "\n";
        
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> flows(n + 1);
    for(int i = 1; i <= n; i++) {
        int q;
        cin >> q;
        
        flows[i] = q;
    }
    
    solution(flows);
    
    return 0;
}