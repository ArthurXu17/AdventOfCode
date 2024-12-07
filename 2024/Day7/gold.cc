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
vector<string> generateTernaryStrings(int n) {
    vector<string> result;

    int totalStrings = pow(3, n); // Total combinations (3^length)

    for (int i = 0; i < totalStrings; ++i) {
        int num = i;
        string str;

        for (int j = 0; j < n; ++j) {
            str = char('0' + (num % 3)) + str; // Map remainder to '0', '1', '2'
            num /= 3; // Move to the next digit in base-3
        }

        result.push_back(str);
    }

    return result;
}

ll concatenate(ll a, ll b) {
    return stoll(to_string(a) + to_string(b));
}


bool solve(vector<int>& nums, ll target) {
    int n = nums.size() - 1;
    vector<string> allStrings = generateTernaryStrings(n);
    //cout<<"Num combinations: "<<allStrings.size()<<endl;
    for (auto & str : allStrings) {
        ll result = nums[0];
        for (int i = 0; i < n; i++) {
            //cout<<"Cur result: "<<result<<endl;
            if (str[i] == '0') {
                result += nums[i+1];
            } else if (str[i] == '1') {
                result *= nums[i+1];
            } else if (str[i] == '2') {
                result = concatenate(result, nums[i+1]);
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
