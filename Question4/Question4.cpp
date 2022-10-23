#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<iostream>
#include<string>
#include<climits>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<string> names(n);
    vector<pair<int, int>> times(n);

    for(int i = 0; i < n; i++)
        cin >> names[i];

    int start, end, min_start = INT_MAX, max_end = INT_MIN;
    for(int i = 0; i < n; i++) {
        cin >> start >> end;
        times[i] = {start, end};

        min_start = min<int>(min_start, start);
        max_end = max<int>(max_end, end);
    }

    unordered_map<string, vector<bool>> reg;
    int size = max_end - min_start;

    for(int i = 0; i < n; i++) {
        string &curr = names[i];
        reg.insert({curr, vector<bool>(size, false)});

        start = times[i].first;
        end = times[i].second;
        for(int j = start; j < end; j++)
            reg[curr][j - min_start] = true;
    }

    unordered_set<string> available;
    //Init
    for(unordered_map<string, vector<bool>>::iterator it = reg.begin(); 
        it != reg.end(); 
        it++) {
        const string &name = it->first;

        if(reg[name][0])
            available.insert(name);
    }

    vector<tuple<int, int, int, vector<string>>> res;
    int prev_start, prev_end;
    prev_start = prev_end = min_start;

    for(int curr_time = min_start + 1; curr_time <= max_end; curr_time++) {
        bool is_same = true;

        for(unordered_map<string, vector<bool>>::iterator it = reg.begin(); 
            is_same && curr_time != max_end && it != reg.end(); it++) {
                const string &name = it->first;
                bool status = reg[name][curr_time - min_start];

                if(!status && available.find(name) != available.end())
                    is_same = false;
                if(status && available.find(name) == available.end())
                    is_same = false;
        }

        if(curr_time != max_end && is_same)
            prev_end = curr_time;
        else {
            res.push_back(make_tuple(prev_start, curr_time, 
                          available.size(), 
                          vector<string>(available.begin(), available.end())));
            
            vector<string> &names = get<3>(res[res.size() - 1]);
            sort(names.begin(), names.end());

            for(unordered_map<string, vector<bool>>::iterator it = reg.begin(); 
                it != reg.end() && curr_time != max_end; it++) {
                const string &name = it->first;
                bool status = reg[name][curr_time - min_start];

                if(status)
                    available.insert(name);
                if(!status && available.find(name) != available.end())
                    available.erase(available.find(name));
            }

            prev_start = prev_end = curr_time;
        }
    }

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); i++) {
        tuple<int, int, int, vector<string>> &curr = res[i];

        int start = get<0>(curr), end = get<1>(curr), count = get<2>(curr);
        vector<string> &people = get<3>(curr);

        cout << start << " " << end << " " << count << " ";
        for(int j = 0; j < people.size(); j++) {
            cout << people[j];

            if(j + 1 != people.size())
                cout << " ";
        }
        cout << "\n";
    }

    return 0;
}