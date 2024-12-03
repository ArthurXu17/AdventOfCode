#include <bits/stdc++.h>

using namespace std;

bool solve(vector<int>& nums) {
    bool isIncreasing = nums[1] > nums[0];
    for (int i = 0; i < nums.size() - 1; i++) {
        int diff = abs(nums[i+1] - nums[i]);
        if (diff < 1 || diff > 3) {
            return false;
        }
        if (isIncreasing && nums[i+1] < nums[i]) {
            return false;
        }
        if (!isIncreasing && nums[i+1] > nums[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    string line;
    int result = 0;
    while (getline(cin, line)) {
        istringstream stream(line);
        vector<int> nums;
        int n;
        while (stream >> n) {
            nums.push_back(n);
        }
        if (solve(nums)) {
            result+=1;
        } 
    }
    cout<<result<<endl;
}