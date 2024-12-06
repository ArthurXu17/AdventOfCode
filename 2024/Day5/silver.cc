#include <bits/stdc++.h>

using namespace std;

int middleNumIfGood(unordered_map<int, vector<int>>& cannotFollow, vector<int>& arr) {
    unordered_set<int> bannedNums;
    for (auto & n : arr) {
        if (bannedNums.find(n) != bannedNums.end()) {
            return 0;
        }
        if (cannotFollow.find(n) != cannotFollow.end()) {
            for (auto & m : cannotFollow[n]) {
                bannedNums.insert(m);
            }
        }
    }
    return arr[arr.size() / 2];
}

int main() {
    string str;
    unordered_map<int, vector<int>> cannotFollow;
    while (getline(cin, str)) {
        //cout<<"iter1: "<<str<<endl;
        //cout<<"Size: "<<str.size()<<endl;
        if (str.size() < 5) {
            break;
        }
        string str1 = {str[0], str[1]};
        string str2 = {str[3], str[4]};
        int num1 = stoi(str1);
        int num2 = stoi(str2);
        if (cannotFollow.find(num2) == cannotFollow.end()) {
            cannotFollow[num2] = {num1};
        } else {
            cannotFollow[num2].push_back(num1);
        }
    }
    int result = 0;
    while (getline(cin, str)) {
        //cout<<"iter2: "<<str<<endl;
        for (auto & ch : str) {
            if (ch == ',') {
                ch = ' ';
            }
        }
        istringstream stream(str);
        vector<int> nums;
        int n;
        while (stream >> n) {
            nums.push_back(n);
        }
        result += middleNumIfGood(cannotFollow, nums);
    }
    cout<<result<<endl;


}
