#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<iostream>
#include<vector>
#include<tuple>
#include<set>
#include<algorithm>
#include<climits>

using namespace std;

// #define FILLED '$'

// void count(vector<string> &grid, vector<vector<int>> &cnt) {
//     const int n = cnt.size();

//     int top, left, top_left;
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < n; j++) {
//             top = (i ? cnt[i - 1][j] : 0);
//             left = (j ? cnt[i][j - 1] : 0);
//             top_left = ((i && j) ? cnt[i - 1][j - 1] : 0);

//             cnt[i][j] = top + left - top_left + (grid[i][j] == FILLED);
//         }
//     }

//     return;
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n;
//     cin >> n;

//     vector<string> grid(n);
//     for(int i = 0; i < n; i++)
//         cin >> grid[i];

//     vector<vector<int>> cnt(n, vector<int>(n, 0));
//     count(grid, cnt);

//     return 0;
// }

bool sort_events(tuple<int, char, string> &a, tuple<int, char, string> &b) {
    return get<0>(a) < get<0>(b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<string> names(n);

    for(int i = 0; i < n; i++)
        cin >> names[i];

    vector<tuple<int, char, string>> events(2*n);
    for(int i = 0; i < n; i++) {
        int start, end;
        cin >> start >> end;

        events[2*i] = make_tuple(start, '+', names[i]);
        events[2*i + 1] = make_tuple(end, '-', names[i]);
    }

    sort(events.begin(), events.end(), sort_events);

    set<string> people;

    //Init
    int i = 0;
    for(i = 0; i < 2*n; i++) {
        tuple<int, char, string> &curr = events[i];

        string &name = get<2>(curr);

        int time, start_time;
        time = get<0>(curr);
        start_time = get<0>(events[0]);

        if(time == start_time)
            people.insert(name);
        else
            break;
    }

    // start, end, count, vector of name
    vector<tuple<int, int, int, vector<string>>> res;

    int prev_start = get<0>(events[0]);
    for(; i < 2*n ; i++) {
        tuple<int, char, string> &curr = events[i];

        int time = get<0>(curr);
        char event = get<1>(curr);
        string &name = get<2>(curr);

        if(prev_start != time)
            res.push_back(
                make_tuple(prev_start, time, people.size(), 
                           vector<string>(people.begin(), people.end()))
            );

        if(event == '+') {
            people.insert(name);
            prev_start = time;
        }
        else {
            prev_start = time;
            people.erase(people.find(name));
        }
    }

    const int m = res.size();

    cout << m << "\n";
    for(int i = 0; i < m; i++) {
        tuple<int, int, int, vector<string>> &curr = res[i];

        int start, end, count;
        start = get<0>(curr);
        end = get<1>(curr);
        count = get<2>(curr);

        cout << start << " " << end << " " << count << " ";

        vector<string> &names = get<3>(curr);

        const int names_size = names.size();
        for(int j = 0; j < names_size; j++) {
            cout << names[j];
            
            if(j + 1 != names_size)
                cout << " ";
        }

        cout << "\n";
    }

    return 0;
}