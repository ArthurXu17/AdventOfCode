#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

bool inBounds(int a, int b, int n) {
    return 0 <= a && a < n && 0 <= b && b < n;
}

int main() {
    int n = 71;
    vector<vector<bool>> grid(n, vector<bool>(n, false));
    vector<p> directions = {{1,0},{-1,0},{0,1},{0,-1}};
    int a,b;
    while (true) {
        cin >> a >> b;
        //cout<<a<<" "<<b<<endl;
        grid[b][a] = true;
        vector<vector<int>> distance(n, vector<int>(n, -1));
        queue<p> bfs;
        bfs.push(make_pair(0,0));
        distance[0][0] = 0;
        while (!bfs.empty()) {
            auto [x,y] = bfs.front();
            //cout<<x<<", "<<y<<endl;
            bfs.pop();
            for (auto & [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                if (inBounds(nx, ny, n) && distance[nx][ny] == -1 && !grid[nx][ny] ) {
                    distance[nx][ny] = distance[x][y] + 1;
                    bfs.push(make_pair(nx, ny));
                }
            }
        }
        if (distance[n-1][n-1] == -1) {
            cout<<a<<","<<b<<endl;
            break;
        }
    }
    
}
