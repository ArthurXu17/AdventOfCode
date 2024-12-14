#include <bits/stdc++.h>
typedef long long ll;
typedef pair<int, int> p;
using namespace std;

int longestRow(vector<vector<vector<p>>> &grid) {
    int maxLength = 0;
    for (int i = 0; i < grid.size(); i++) {
        int curLength = 0;
        for (int j = 0; j < grid[i].size(); i++) {
            if (grid[i][j].empty()) {
                curLength = 0;
            } else {
                curLength++;
                maxLength = max(curLength, maxLength);
            }
        }
    }
    return maxLength;
}

void updateGrid(vector<vector<vector<p>>> & grid) {
    for (int i = 0; i < grid.size(); i++) {
        int curLength = 0;
        for (int j = 0; j < grid[i].size(); i++) {
            if (grid[i][j].empty()) {
                curLength = 0;
            } else {
                curLength++;
            }
        }
    }
}

int main() {
    int m = 103;
    int n = 101;
    ll t = 100;
    vector<vector<vector<p>>> grid(m, vector<vector<p>>(n, vector<p>())); // for each index, keep track of all velocities of robot at that index
    string str;
    while (getline(cin, str)) {
        for (auto & ch : str) {
            if (!(isdigit(ch) || ch == '-')) {
                ch = ' ';
            }
        }
        istringstream stream(str);
        ll x, y, dx, dy;
        stream >> y >> x >> dy >> dx;
        grid[x][y].emplace_back(dx, dy);
    }
    
}
