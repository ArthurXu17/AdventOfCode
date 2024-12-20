#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> p;

bool inBounds(int a, int b, int m, int n) {
    return 0 <= a && a < m && 0 <= b && b < n;
}

int baseBfs(vector<string>& grid, int sx, int sy, int ex, int ey) {
    vector<p> directions = {{1,0},{-1,0},{0,1},{0,-1}};
    int n = grid.size();
    int m = grid.size();
    vector<vector<int>> distance(n, vector<int>(n, -1));
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
                /*for (auto & vec : distance) {
                    for (auto & d : vec) {
                        cout<<d<<" ";
                    }
                    cout<<endl;
                }*/
                return distance[nx][ny];
            }
        }
    }
    cout<<"base bfs fail"<<endl;
    assert(false);
    return -1;
}
int main() {
    string str;
    vector<string> grid;
    while (cin>>str) {
        grid.push_back(str);
    }
    
    int m = grid.size();
    int n =grid[0].size();
    int sx, sy, ex, ey;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
            } else if (grid[i][j] == 'E') {
                ex = i;
                ey = j;
            }
        }
    }
    int noCheatDistance = baseBfs(grid, sx, sy, ex, ey);
    set<vector<int>> cheats;
    int result = 0;
    int it = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = i; j < grid.size(); j++) {
            cout<<"Cheat Base: "<<i<<", "<<j<<endl;
            if (grid[i][j] == '#') {
                grid[i][j] = '.';
                vector<p> directions = {{1,0},{-1,0},{0,1},{0,-1}};
                vector<p> cheatDirections = {{1,0},{0,1}};
                for (auto & [dx, dy] : cheatDirections) {
                    int ni = i + dx;
                    int nj = j + dy;
                    bool secondCheat = false;
                    if (inBounds(ni, nj, m,n)) {
                        if (grid[ni][nj] == '#') {
                            grid[ni][nj] = '.';
                            secondCheat = true;
                        }
                    }
                    vector<vector<int>> distance(n, vector<int>(n, -1));
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
                                if ( noCheatDistance - distance[ex][ey] >= 100) {
                                    cheats.insert({i,j,ni,nj});
                                } /*else if (noCheatDistance - distance[ex][ey] == 64) {
                                    cout<<"Cheating saving: "<<noCheatDistance - distance[ex][ey]<<endl;
                                    cout<<"i,j: "<<i<<", "<<j<<endl;
                                    cout<<"ni, nj: "<<ni<<", "<< nj<<endl;
                                    cout<<it<<endl;
                                }*/
                                /*if (i == 7 && j == 6) {
                                    for (auto & str : grid) {
                                        cout<<str<<endl;
                                    }
                                    for (auto & vec : distance) {
                                        for (auto & d : vec) {
                                            cout<<d<<" ";
                                        }
                                        cout<<endl;
                                    }
                                }*/
                                break;
                            }
                        }
                    }
                    if (secondCheat) {
                        grid[ni][nj] = '#';
                    }
                    it++;
                }
                grid[i][j] = '#';
            }
        }
    }
    cout<<cheats.size()<<endl;
}
