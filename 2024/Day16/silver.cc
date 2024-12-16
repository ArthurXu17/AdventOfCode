#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> p;
typedef long long ll;

p getDirection(int n) {
    if (n == 0) {
        return {1,0};
    } else if (n == 1) {
        return {0,-1};
    } else if (n == 2) {
        return {-1,0};
    } else if (n == 3) {
        return {0,1};
    } else {
        cout<<"Invalid Direction"<<endl;
        return {0,0};
    }
}

int main() {
    string str;
    vector<string> grid;
    while (cin >> str) {
        grid.push_back(str);
    }
    int startx, starty, endx, endy;
    int m = grid.size();
    int n = grid[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'S') {
                startx = i;
                starty = j;
            } 
            if (grid[i][j] == 'E') {
                endx = i;
                endy = j;
            } 
        }
    }
    ll answer = LLONG_MAX;
    //for (int initDirection = 0; initDirection <= 3; initDirection++) {
        int initDirection = 3;
        priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;
        vector<vector<vector<ll>>> distance(m, vector<vector<ll>>(n, vector<ll>(4, LLONG_MAX)));
        pq.push({0, startx, starty, initDirection});
        distance[startx][starty][initDirection] = 0;
        while (!pq.empty()) {
            vector<ll> info = pq.top();
            ll curDistance = info[0];
            int x = info[1];
            int y = info[2];
            int direction = info[3];
            auto [dx, dy] = getDirection(direction);
            pq.pop();
            if (grid[x+dx][y+dy] != '#' && distance[x][y][direction] + 1 < distance[x+dx][y+dy][direction]) {
                distance[x+dx][y+dy][direction] = distance[x][y][direction] + 1;
                pq.push({distance[x+dx][y+dy][direction], x+dx, y+dy, direction});
            }
            int newDirection = (direction + 1)%4;
            if (newDirection < 0) {
                newDirection += 4;
            }
            if (distance[x][y][direction] + 1000 < distance[x][y][newDirection]) {
                 distance[x][y][newDirection] = distance[x][y][direction] + 1000;
                 pq.push({distance[x][y][newDirection], x, y, newDirection});
            }

            newDirection = (direction - 1)%4;
            if (newDirection < 0) {
                newDirection += 4;
            }
            if (distance[x][y][direction] + 1000 < distance[x][y][newDirection]) {
                 distance[x][y][newDirection] = distance[x][y][direction] + 1000;
                 pq.push({distance[x][y][newDirection], x, y, newDirection});
            }
        }
        for (int endD = 0; endD <= 3; endD++) {
            answer = min(answer, distance[endx][endy][endD]);
        }
    //} 
    cout<<answer<<endl;
    

}
