#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> p;

bool inBounds(int a, int b, int m, int n) {
    return 0 <= a && a < m && 0 <= b && b < n;
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
map<p, unordered_set<int>> getCheatingNeighbours(vector<string>& grid, int sx, int sy, int numWalls) {
    queue<p> bfs;
    map<p, unordered_set<int>> result; // map each new location to possible distances required to get there
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> distance(m, vector<int>(n, -1));
    bfs.push(make_pair(sx, sy));
    distance[sx][sy] = 0;
    vector<p> directions = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!bfs.empty()) {
        auto [x,y] = bfs.front();
        bfs.pop();
        if (x != sx && y != sy) {
            assert(grid[x][y] == '#');
        }
        if (distance[x][y] > numWalls) {
            break;
        }
        for (auto & [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            if (!inBounds(nx, ny, m, n)) {
                continue;
            }
            if (grid[nx][ny] != '#' && grid[x][y] == '#') {
                // reached end of cheating
                auto destination = make_pair(nx, ny);
                if (result.count(destination)) {
                    result[destination].insert(distance[x][y] + 1);
                } else {
                    result[destination] = {distance[x][y] + 1};
                }
            } else if (distance[nx][ny] == -1 && grid[nx][ny] == '#') {
                // stay cheating
                distance[nx][ny] = distance[x][y] + 1;
                bfs.push(make_pair(nx, ny));
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
    vector<vector<map<p, unordered_set<int>>>> cheatingNeighbours(m, vector<map<p, unordered_set<int>>>(n, map<p, unordered_set<int>>()));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '#') {
                cheatingNeighbours[i][j] = getCheatingNeighbours(grid, i, j, 19);
            }
        }
    }
    queue<p> bfs;
    vector<vector<int>> distanceFromStart(m, vector<int>(n, -1));
    vector<p> directions = {{1,0},{-1,0},{0,1},{0,-1}};
    bfs.push(make_pair(sx, sy));
    distanceFromStart[sx][sy] = 0;
    int result = 0;
    map<int, int> cheatCount;
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
        map<p, unordered_set<int>> cheatingRoutes = cheatingNeighbours[x][y];
        for (auto [dest, costList] : cheatingRoutes) {
            if (costList.size() > 1) {
                cout<<"Cost List at least 2"<<endl;
            }
            for (auto & cost : costList) {
                int totalRouteLength = distanceFromStart[x][y] + cost + distanceToEnd[dest.first][dest.second];
                int delta = baseDistance - totalRouteLength;
                if (delta >= 100) {
                    result++;
                }
                if (delta >= 50) {
                    if (cheatCount.count(delta)) {
                        cheatCount[delta]++;
                    } else {
                        cheatCount[delta] = 1;
                    }
                }
            }
        }
    }
    for (auto & [k,v] : cheatCount) {
        cout<<k<<": "<<v<<endl;
    }
    cout<<result<<endl;
    
    
}
