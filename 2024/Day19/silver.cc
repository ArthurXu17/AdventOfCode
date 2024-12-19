#include <bits/stdc++.h>

using namespace std;

int dfs(string& str, int i, vector<string>& patterns, vector<unordered_set<string>>& notPossiblePatternsByIndex) {
    /*if (str == "bwbbrrgrrbrggubuggwgguguburbbgbgrruggugbggggb") {
        cout<<"Index: "<<i<<endl;
        cout<<"Size: "<<str.size()<<endl;
    }*/
    if (i == str.size()) {
        return true;
    } else if (i > str.size()) {
        return false;
    } else {
        bool result = false;
        for (auto & p : patterns) {
            if (str.substr(i, p.size()) == p) {
                if (notPossiblePatternsByIndex[i].count(p)) {
                    continue;
                }
                //cout<<"Trying index: "<<i<<" with pattern "<<p<<endl;
                result = result || dfs(str, i + p.size(), patterns, notPossiblePatternsByIndex);
            }
            if (result) {
                return true;
            } else {
                notPossiblePatternsByIndex[i].insert(p);
            }
        }
        return result;
    }
}

int main() {
    int n;
    string str;
    vector<string> patterns;
    getline(cin, str);
    istringstream pstream(str);
    while (pstream >> str) {
        patterns.push_back(str);
    }


    int result = 0;
    while (cin >> str) {
        vector<unordered_set<string>> notPossiblePatternsByIndex(str.size() + 1, unordered_set<string>());
        if (dfs(str, 0, patterns, notPossiblePatternsByIndex)) {
            result++;
            cout<<str<<endl;
        } else {
            //cout<<"NO"<<endl;
        }
    }
    cout<<result<<endl;

}
