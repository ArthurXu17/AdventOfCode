#include <bits/stdc++.h>

using namespace std;

bool checkLevel(int a, int b, bool isIncreasing) {
    int diff = abs(b - a);
    if (diff < 1 || diff > 3) {
        return false;
    }
    if (isIncreasing && b < a) {
        return false;
    }
    if (!isIncreasing && b > a) {
        return false;
    }
    return true;
}


bool solveNoDampen(vector<int>& nums) {
    bool isIncreasing = nums[1] > nums[0];
    for (int i = 0; i < nums.size() - 1; i++) {
        if (!checkLevel(nums[i],nums[i+1],isIncreasing)) {
            return false;
        }
    }
    return true;
}

bool solveWithDampen(vector<int>& nums) {
    bool isIncreasing = nums[1] > nums[0];
    vector<int> copy = nums;
    vector<int> copy2 = nums;
    for (int i = 0; i < nums.size() - 1; i++) {
        // if something wrong attempt to remove index i + 1
        if (!checkLevel(nums[i],nums[i+1],isIncreasing)) {
            if (i == nums.size() - 2) {
                return true;
            } 
            copy.erase(copy.begin() + i + 1);
            copy2.erase(copy2.begin() + i);
            return solveNoDampen(copy) || solveNoDampen(copy2);
        }
    }
    return true;
}

bool solve(vector<int>& nums) {
    for (auto & n : nums) {
        cout<<n<<" ";
    }
    cout<<endl;
    vector<int> copy = nums;
    copy.erase(copy.begin());
    return solveNoDampen(nums) || solveNoDampen(copy) || solveWithDampen(nums);
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
            cout<<"yes"<<endl;
        }  else {
            cout<<"no"<<endl;
        }
    }
    cout<<result<<endl;
}