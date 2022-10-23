#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<iostream>
#include<vector>

using namespace std;

int countSubarrays(vector<int> &nums, int k) {
    const int n = nums.size();
    
    int start, end, count, sum = nums[0];
    start = end = count = 0;

    while(start < n && end < n) {
        if(sum < k) {
            end++;
 
            if(end >= start)
                count += end - start;
 
            if(end < n)
                sum += nums[end];
        }
        else {
            sum -= nums[start];
            start++;
        }
    }
 
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    cin >> k;

    int n;
    cin >> n;

    vector<int> nums(n);
    for(int i = 0; i < n; i++)
        cin >> nums[i];

    cout << countSubarrays(nums, k) << "\n";

    return 0;
}