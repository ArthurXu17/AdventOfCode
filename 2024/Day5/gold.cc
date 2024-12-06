#include <bits/stdc++.h>

using namespace std;

int middleNumIfGood(unordered_map<int, unordered_set<int>>& cannotFollow, vector<int>& arr) {
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

vector<int> properOrdering(unordered_map<int, unordered_set<int>>& cannotFollow, vector<int>& arr) {
    vector<pair<int,int>> sortingArray;
    for (auto & n : arr) {
        int numBanned = 0;
        // for each n, find how many m that cannot follow it
        for (auto & m : arr) {
            if (m != n && cannotFollow[n].find(m) != cannotFollow[n].end()) {
                numBanned++;
            }
        }
        sortingArray.push_back(make_pair(numBanned, n));
    }
    sort(sortingArray.begin(), sortingArray.end(), greater());
    vector<int> result;
    for (auto & p : sortingArray) {
        result.push_back(p.second);
    }
    return result;
}

int main() {
    string str;
    unordered_map<int, unordered_set<int>> cannotFollow;
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
            cannotFollow[num2].insert(num1);
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
        if (middleNumIfGood(cannotFollow, nums) == 0) {
            vector<int> proper = properOrdering(cannotFollow, nums);
            result += proper[proper.size() / 2];
        }
    }
    cout<<result<<endl;


}
