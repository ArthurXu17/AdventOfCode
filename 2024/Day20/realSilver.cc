#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> p;

int bfs(vector<string>& grid, int sx, int sy, int ex, int ey) {
    queue<p> q;
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> distance(m, vector<int>(n, -1));
    q.push(make_pair(sx, sy));
    distance[sx][sy] = 0;
    vector<p> directions = {{1,0}, {-1, 0}, {0,1}, {0,-1}};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (auto & [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            // don't need to check in bounds since grid is bordered
            if (distance[nx][ny] == -1 && grid[nx][ny] != '#') {
                q.push(make_pair(nx, ny));
                distance[nx][ny] = distance[x][y] + 1;
            }
            if (grid[nx][ny] == 'E') {
                return distance[nx][ny];
            }
        }
    }
    cout<<"Bfs not reachable"<<endl;
    assert(false);
    return -1;
}

int main() {
    string str;
    vector<string> grid;
    while (cin >> str) {
        grid.push_back(str);
    }
    int m = grid.size();
    int n = grid[0].size();
    int sx, sy, ex, ey;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
            } else if (grid[i][j] == 'E') {
                ex = i;
                ey = j;
            }
        }
    }
    int baseDistance = bfs(grid, sx, sy, ex, ey);
    cout<<"Base Distance: "<<baseDistance<<endl;
    map<int, int> cheatCount;
    int over100 = 0;
    // loop over all things to remove
    for (int i = 1; i < m-1; i++) {
        for (int j = 1; j < n-1; j++) {
            if (grid[i][j] != '#') {
                continue;
            }
            //cout<<i<<", "<<j<<endl;
            /*for (auto & str : grid) {
                cout<<str<<endl;
            }*/
            grid[i][j] = '.';
            int cheatDistance = bfs(grid, sx, sy, ex, ey);
            int delta = baseDistance - cheatDistance;
            if (delta > 0) {
                if (cheatCount.count(delta)) {
                    cheatCount[delta]++;
                } else {
                    cheatCount[delta] = 1;
                }
            }
            if (delta >= 100) {
                over100++;
            }
            grid[i][j] = '#';
        }
    }
    /*for (auto & [k,v] : cheatCount) {
        cout<<k<<": "<<v<<endl;
    }*/
   cout<<over100<<endl;
}
