#include <bits/stdc++.h>
typedef unsigned long long ll;
using namespace std;

ll dfs(string& str, int i, vector<string>& patterns, vector<unordered_set<string>>& notPossiblePatternsByIndex, vector<unordered_map<string, ll>>& possibleWaysByIndex) {
    /*if (str == "bwbbrrgrrbrggubuggwgguguburbbgbgrruggugbggggb") {
        cout<<"Index: "<<i<<endl;
        cout<<"Size: "<<str.size()<<endl;
    }*/
    if (i == str.size()) {
        return 1;
    } else if (i > str.size()) {
        return 0;
    } else {
        ll result = 0;
        for (auto & p : patterns) {
            if (str.substr(i, p.size()) == p) {
                if (notPossiblePatternsByIndex[i].count(p)) {
                    continue;
                }
                if (possibleWaysByIndex[i].count(p)) {
                    result += possibleWaysByIndex[i][p];
                } else {
                    possibleWaysByIndex[i][p] = dfs(str, i + p.size(), patterns, notPossiblePatternsByIndex, possibleWaysByIndex);
                    result += possibleWaysByIndex[i][p];
                }
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


    ll result = 0;
    while (cin >> str) {
        vector<unordered_set<string>> notPossiblePatternsByIndex(str.size() + 1, unordered_set<string>());
        vector<unordered_map<string, ll>> possibleWaysByIndex(str.size() + 1, unordered_map<string, ll>());
        ll curResult = dfs(str, 0, patterns, notPossiblePatternsByIndex, possibleWaysByIndex);
        result += curResult;
        cout<<"Cur result: "<<curResult<<", "<<"Overall Result: "<<result<<endl;
    }
    cout<<result<<endl;

}
