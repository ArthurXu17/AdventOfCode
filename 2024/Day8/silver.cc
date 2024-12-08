#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> p;

bool inBounds(int n, int m, int x, int y) {
    return x >= 0 && x < n &&  y >= 0 && y < m;
}

int main() {
    vector<string> grid;
    string str;
    while (cin>>str) {
        grid.push_back(str);
    }
    int n = grid.size();
    int m = grid[0].size();
    unordered_map<char, vector<p>> locations;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char ch = grid[i][j];
            if (ch == '.') {
                continue;
            }
            if (locations.find(ch) == locations.end()) {
                locations[ch] = {make_pair(i,j)};
            } else {
                locations[ch].push_back(make_pair(i,j));
            }
        }
    }
    cout<<n<<" x "<<m<<endl;
    vector<vector<bool>> antiNodes(n, vector<bool>(m, false));
    /*for (auto & [ch, points]: locations) {
        cout<<ch<<": ";
        for (auto & p : points) {
            cout<<"("<<p.first<<", "<<p.second<<") ";
        }
        cout<<endl;
    }*/
    for (auto & [ch, points]: locations) {
        cout<<ch<<": ";
        for (auto & p : points) {
            cout<<"("<<p.first<<", "<<p.second<<") ";
        }
        cout<<endl;
        for (int i = 0; i < points.size(); i++) {
            for (int j = i+1; j < points.size(); j++) {
                p p1 = points[i];
                p p2 = points[j];
                //cout<<"Handling Points: "<<"("<<p1.first<<", "<<p1.second<<") "<<"("<<p2.first<<", "<<p2.second<<") "<<endl;
                int dx = p2.first - p1.first;
                int dy = p2.second - p1.second;
                if (inBounds(n,m,p2.first+dx, p2.second+dy)) {
                    antiNodes[p2.first+dx][p2.second+dy] = true;
                }
                //cout<<"First Bounds Check for Points: "<<"("<<p1.first<<", "<<p1.second<<") "<<"("<<p2.first<<", "<<p2.second<<") "<<endl;
                if (inBounds(n,m,p1.first-dx, p1.second-dy)) {
                    antiNodes[p1.first-dx][p1.second-dy] = true;
                }
                //cout<<"Handled Points: "<<"("<<p1.first<<", "<<p1.second<<") "<<"("<<p2.first<<", "<<p2.second<<") "<<endl;
            }
        }
    }
    int result = 0;
    for (const auto & vec : antiNodes) {
        for (const auto & b : vec) {
            if (b) {
                result++;
            }
        }
    }
    cout<<result<<endl;
}
