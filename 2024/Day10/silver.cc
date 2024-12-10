#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> p;

bool inBounds(int x, int y, int m, int n) {
    return x >= 0 && x < m && y >= 0 && y < n;
}
int main() {
    vector<string> grid;
    string str;
    while (getline(cin, str)) {
        grid.push_back(str);
    }
    vector<p> directions = {{1,0}, {-1,0}, {0,-1}, {0,1}};
    int m = grid.size();
    int n = grid[0].size();
    int result = 0;
    /*for (auto & t : grid) {
        cout<<t<<endl;
    }*/
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != '0') {
                continue;
            }
            //cout<<"Start Bfs at location: "<<i<<", "<<j<<endl;
            queue<p> bfs;
            bfs.push(make_pair(i,j));
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            visited[i][j] = true;
            int countNine = 0;
            while (!bfs.empty()) {
                p curNode = bfs.front();
                int x = curNode.first;
                int y = curNode.second;
                //cout<<"Visiting: "<<x<<", "<<y<<endl;
                bfs.pop();
                for (auto & direction : directions) {
                    int dx = direction.first;
                    int dy = direction.second;
                    int new_x = x + dx;
                    int new_y = y + dy;
                    if (inBounds(new_x, new_y, m, n) && grid[new_x][new_y] == grid[x][y] + 1 && !visited[new_x][new_y]) {
                        visited[new_x][new_y] = true;
                        bfs.push(make_pair(new_x, new_y));
                        if (grid[new_x][new_y] == '9') {
                            countNine++;
                        }
                    }
                }
            }
            result += countNine;
        }
    }
    cout<<result<<endl;
}
