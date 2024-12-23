#include <bits/stdc++.h>

using namespace std;

int codeToInt(string& str) {
    if (str.size() == 2) {
        int a = str[0] - 'a';
        int b = str[1] - 'a';
        return 26*a + b;
    } else {
        cout<<"Smth wrong with str: "<<str<<endl;
        assert(false);
        return -1;
    }
}
string intToCode(int n) {
    char a = n / 26 + 'a';
    char b = n % 26 + 'a';
    return {a,b};
}

vector<vector<int>> getSubsets(vector<int>& nums) {
    int n = nums.size();
    int p = 1 << n;
    vector<vector<int>> subs(p);
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                subs[i].push_back(nums[j]);
            }
        }
    }
    return subs;
}

bool validClique(vector<int>& vertices, vector<vector<bool>>& adj) {
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = i + 1; j < vertices.size(); j++) {
            if (!adj[vertices[i]][vertices[j]]) {
                return false;
            }
        }
    }
    return true;
}

vector<int> maxCliqueOfGroup(vector<int>& group, vector<vector<bool>>& adj) {
    vector<int> result(4, -1); // dummy value
    if (group.size() == 14) {
        vector<vector<int>> subsets = getSubsets(group);
        for (auto & subset : subsets) {
            if (subset.size() > result.size() && validClique(subset, adj)) {
                result = subset;
            }
        }
        return result;
    } else {
        cout<<"Group size wrong"<<endl;
        for (auto & g : group) {
            cout<<g<<" ";
        }
        cout<<endl;
        assert(false);
        return {};
    }
}

int main() {
    int total = 26*26;
    string sa, sb;
    vector<unordered_set<int>> outgoingNeighbours(total, unordered_set<int>());
    vector<vector<bool>> adj(total, vector<bool>(total, false));
    while (cin >> sa >> sb) {
        int a = codeToInt(sa);
        int b = codeToInt(sb);
        adj[a][b] = true;
        adj[b][a] = true;
        outgoingNeighbours[a].insert(b);
    }
    vector<vector<int>> potentialGroups;
    int groups = 0;
    for (int i = 0;  i < total; i++) {
        if (outgoingNeighbours[i].size() >= 13) {
            vector<int> curGroup(outgoingNeighbours[i].begin(), outgoingNeighbours[i].end());
            curGroup.push_back(i);
            potentialGroups.emplace_back(curGroup);
            groups++;
            cout<<groups<<": "<<i<<"("<<intToCode(i)<<")"<<endl;
        }
    }
    vector<int> maxClique = {};
    for (auto & group : potentialGroups) {
        vector<int> groupMaxClique = maxCliqueOfGroup(group, adj);
        cout<<"Group: ";
        for (auto & g : group) {
            cout<<g<<" ";
        }
        cout<<endl;
        cout<<"Max Clique: ";
        for (auto & g : groupMaxClique) {
            cout<<g<<" ";
        }
        cout<<endl;
        cout<<"Max Clique Size: "<<groupMaxClique.size()<<endl;
        if (groupMaxClique.size() > maxClique.size()) {
            maxClique = groupMaxClique;
        } 
    }
    vector<string> maxCliqueStrings;
    for (auto & num : maxClique) {
        maxCliqueStrings.push_back(intToCode(num));
    }
    sort(maxCliqueStrings.begin(), maxCliqueStrings.end());
    for (auto & str : maxCliqueStrings) {
        cout<<str<<",";
    }
    cout<<endl;
}
