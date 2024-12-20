#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> p;

bool inBounds(int a, int b, int m, int n) {
    return 0 <= a && a < m && 0 <= b && b < n;
}

int manhattenDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int baseBfs(vector<string>& grid, int sx, int sy, int ex, int ey, vector<vector<int>>& distance) {
    vector<p> directions = {{1,0},{-1,0},{0,1},{0,-1}};
    int n = grid.size();
    int m = grid.size();
    queue<p> bfs;
    bfs.push(make_pair(sx,sy));
    distance[sx][sy] = 0;
    while (!bfs.empty()) {
        auto [x,y] = bfs.front();
        //cout<<x<<", "<<y<<endl;
        bfs.pop();
        for (auto & [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            if (inBounds(nx, ny, m,n) && distance[nx][ny] == -1 && grid[nx][ny] != '#' ) {
                distance[nx][ny] = distance[x][y] + 1;
                bfs.push(make_pair(nx, ny));
            }
            if (nx == ex && ny == ey) {
                return distance[nx][ny];
            }
        }
    }
    cout<<"No path to "<<ex<<","<<ey<<endl;
    return -1;
}

// given starting point x, y, find possible end locations after going through at most numWalls
vector<p> getCheatingNeighbours(vector<string>& grid, int sx, int sy, int numWalls) {
    int m = grid.size();
    int n = grid[0].size();
    vector<p> result;
    for (int dx = -numWalls; dx <= numWalls; dx++) {
        for (int dy = -numWalls; dy <= numWalls; dy++) {
            int nx = sx + dx;
            int ny = sy + dy;
            if (manhattenDistance(nx, ny, sx, sy) <= numWalls && inBounds(nx, ny, m, n) && grid[nx][ny] != '#') {
                result.emplace_back(nx, ny);
            }
        }
    }
    return result;
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
    vector<vector<int>> distanceToEnd(m, vector<int>(n, -1));
    baseBfs(grid, ex, ey, -10, -10, distanceToEnd);
    int baseDistance = distanceToEnd[sx][sy];
    vector<vector<vector<p>>> cheatingNeighbours(m, vector<vector<p>>(n, vector<p>()));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '#') {
                cheatingNeighbours[i][j] = getCheatingNeighbours(grid, i, j, 20);
            }
        }
    }
    queue<p> bfs;
    vector<vector<int>> distanceFromStart(m, vector<int>(n, -1));
    vector<p> directions = {{1,0},{-1,0},{0,1},{0,-1}};
    bfs.push(make_pair(sx, sy));
    distanceFromStart[sx][sy] = 0;
    int result = 0;
    //map<int, int> cheatCount;
    while (!bfs.empty()) {
        auto [x,y] = bfs.front();
        bfs.pop();
        // going through immediate neighbours for bfs
        for (auto & [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            if (!inBounds(nx, ny, m, n)) {
                continue;
            }
            if (distanceFromStart[nx][ny] == -1 && grid[nx][ny] != '#') {
                distanceFromStart[nx][ny] = distanceFromStart[x][y] + 1;
                bfs.push(make_pair(nx, ny));
            }
        }
        // checking cheating routes
        vector<p> cheatingDestinations = cheatingNeighbours[x][y];
        for (auto dest : cheatingDestinations) {
            int nx = dest.first;
            int ny = dest.second;
            int cost = manhattenDistance(x, y, nx, ny);
            int totalRouteLength = distanceFromStart[x][y] + cost + distanceToEnd[nx][ny];
            int delta = baseDistance - totalRouteLength;
            if (delta >= 100) {
                result++;
            }
            /*if (delta >= 50) {
                if (cheatCount.count(delta)) {
                    cheatCount[delta]++;
                } else {
                    cheatCount[delta] = 1;
                }
            }*/
        }
    }
    /*for (auto & [k,v] : cheatCount) {
        cout<<k<<": "<<v<<endl;
    }*/
    cout<<result<<endl;
    
    
}
