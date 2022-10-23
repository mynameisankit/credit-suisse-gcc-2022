#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

#define FILLED '$'

void reset(int &min_var, int &max_var) {
    min_var = INT_MAX;
    max_var = INT_MIN;

    return;
}

int bfs(int sx, int sy, 
        vector<string> &grid, 
        vector<vector<bool>> &visited) {
    const int n = grid.size();

    int row_min, row_max, col_min, col_max;
    reset(row_min, row_max);
    reset(col_min, col_max);

    queue<vector<int>> frontier;
    frontier.push({ sx, sy });

    while(!frontier.empty()) {
        int x, y;
        x = frontier.front()[0];
        y = frontier.front()[1];

        visited[x][y] = true;

        for(int dir_x = -1; dir_x <= 1; dir_x++) {
            for(int dir_y = -1; dir_y <= 1; dir_y++) {
                int nx, ny;
                nx = x + dir_x;
                ny = y + dir_y;

                if(nx == x && ny == y)
                    continue;

                if(nx >= 0 && nx < n && ny >= 0 && ny < n && 
                   !visited[nx][ny] && grid[nx][ny] == FILLED) {
                    visited[nx][ny] = true;
                    frontier.push({ nx, ny });
                }
            }
        }

        row_min = min<int>(row_min, x);
        col_min = min<int>(col_min, y);
        row_max = max<int>(row_max, x);
        col_max = max<int>(col_max, y);

        frontier.pop();
    }

    return max<int>(row_max - row_min + 1, col_max - col_min + 1);
}

int solution(vector<string> &grid) {
    const int n = grid.size();

    int row_min, row_max, col_min, col_max;
    reset(row_min, row_max);
    reset(col_min, col_max);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            char curr = grid[i][j];
            
            if(curr == FILLED) {
                row_min = min<int>(row_min, i);
                col_min = min<int>(col_min, j);
                row_max = max<int>(row_max, i);
                col_max = max<int>(col_max, j);
            }
        }
    }

    int res = max<int>(row_max - row_min + 1, col_max - col_min + 1);

    vector<vector<bool>> visited(n, vector<bool>(n, false));

    int curr = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == FILLED && !visited[i][j])
                curr += bfs(i, j, grid, visited);
        }
    } 

    return min<int>(res, min<int>(curr, n));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<string> grid(n);
    for(int i = 0; i < n; i++)
        cin >> grid[i];

    cout << solution(grid) << "\n";

    return 0;
}