#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

/*
void generateBinaryStrings(int n, string current, vector<string>& result) {
    if (n == 0) {
        result.push_back(current);
        return;
    }
    // Add '0' and recurse
    generateBinaryStrings(n - 1, current + "0", result);
    // Add '1' and recurse
    generateBinaryStrings(n - 1, current + "1", result);
}

// Function to return all n-digit binary strings
vector<string> generateBinaryStrings(int n) {
    vector<string> result;
    generateBinaryStrings(n, "", result);
    return result;
}*/

// Function to generate all n-digit binary strings iteratively
vector<string> generateBinaryStrings(int n) {
    vector<string> result;
    int total = 1 << n; // Total number of binary strings is 2^n

    for (int i = 0; i < total; ++i) {
        string binaryString = "";
        for (int j = n - 1; j >= 0; --j) {
            // Extract each bit from the integer and add it to the string
            binaryString += ((i >> j) & 1) ? '1' : '0';
        }
        result.push_back(binaryString);
    }

    return result;
}


bool solve(vector<int>& nums, ll target) {
    int n = nums.size() - 1;
    vector<string> allStrings = generateBinaryStrings(n);
    //cout<<"Num combinations: "<<allStrings.size()<<endl;
    for (auto & str : allStrings) {
        ll result = nums[0];
        for (int i = 0; i < n; i++) {
            //cout<<"Cur result: "<<result<<endl;
            if (str[i] == '0') {
                result += nums[i+1];
            } else {
                result *= nums[i+1];
            }
        }
        //cout<<"End result: "<<result<<endl;
        if (result == target) {
            return true;
        }
    }
    return false;
}
int main() {
    string str;
    ll result = 0;
    /*
    vector<int> a = {10,19};
    bool test = solve(a, 190);
    if (test) {
        cout<<"U"<<endl;
    } else {
        cout<<"F"<<endl;
    }*/

    while (getline(cin, str)) {
        //cout<<str<<endl;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == ':') {
                str[i] = ' ';
                break;
            }
        }
        istringstream stream(str);
        vector<int> nums;
        ll target;
        int n;
        stream >> target;
        while (stream >> n) {
            nums.push_back(n);
        }
        if (solve(nums, target)) {
            result+=target;
        }
    }
    cout<<result<<endl;
}
