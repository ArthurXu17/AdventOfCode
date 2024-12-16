#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> node; // x, y, direction
typedef long long ll;

p getDirection(int n)
{
    if (n == 0)
    {
        return {1, 0};
    }
    else if (n == 1)
    {
        return {0, -1};
    }
    else if (n == 2)
    {
        return {-1, 0};
    }
    else if (n == 3)
    {
        return {0, 1};
    }
    else
    {
        cout << "Invalid Direction: " << n << endl;
        return {0, 0};
    }
}

int main()
{
    string str;
    vector<string> grid;
    while (cin >> str)
    {
        grid.push_back(str);
    }
    int startx, starty, endx, endy;
    int m = grid.size();
    int n = grid[0].size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 'S')
            {
                startx = i;
                starty = j;
            }
            if (grid[i][j] == 'E')
            {
                endx = i;
                endy = j;
            }
        }
    }
    // for (int initDirection = 0; initDirection <= 3; initDirection++) {
    int initDirection = 3;
    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;
    vector<vector<vector<ll>>> distance(m, vector<vector<ll>>(n, vector<ll>(4, LLONG_MAX)));
    vector<vector<vector<vector<node>>>> parents(m, vector<vector<vector<node>>>(n, vector<vector<node>>(4, vector<node>()))); // for each possible location + direction, maintain a list of parents
    pq.push({0, startx, starty, initDirection});
    distance[startx][starty][initDirection] = 0;
    while (!pq.empty())
    {
        vector<ll> info = pq.top();
        ll curDistance = info[0];
        int x = info[1];
        int y = info[2];
        int direction = info[3];
        auto [dx, dy] = getDirection(direction);
        pq.pop();
        if (x == endx && y == endy) {
            continue;
        }
        if (grid[x + dx][y + dy] != '#' && curDistance + 1 <= distance[x + dx][y + dy][direction])
        {
            /*if (x+dx == endx && y+dy == endy) {
                cout<<"Sole parent of end: "<<x<<", "<<y<<endl;
                cout<<"Previous min distance to end: "<<distance[x + dx][y + dy][direction]<<endl;
            }*/
            distance[x + dx][y + dy][direction] = curDistance + 1;
            /*if (x+dx == endx && y+dy == endy) {
                cout<<"Min distance to end after update: "<<distance[x + dx][y + dy][direction]<<endl;*/
            pq.push({distance[x + dx][y + dy][direction], x + dx, y + dy, direction});
            parents[x + dx][y + dy][direction].push_back({x, y, direction});
        } /*else if (grid[x + dx][y + dy] != '#' && curDistance + 1 == distance[x + dx][y + dy][direction]) {
            parents[x + dx][y + dy].push_back(make_pair(x,y));
            if (x+dx == endx && y+dy == endy) {
                cout<<"Additional parent of end: "<<x<<", "<<y<<endl;
            }
        }*/
        int newDirection = (direction + 1) % 4;
        if (newDirection < 0)
        {
            newDirection += 4;
        }
        if (distance[x][y][direction] + 1000 <= distance[x][y][newDirection])
        {
            distance[x][y][newDirection] = distance[x][y][direction] + 1000;
            pq.push({distance[x][y][newDirection], x, y, newDirection});
            parents[x][y][newDirection].push_back({x, y, direction});
        }

        newDirection = (direction - 1) % 4;
        if (newDirection < 0)
        {
            newDirection += 4;
        }
        if (distance[x][y][direction] + 1000 <= distance[x][y][newDirection])
        {
            distance[x][y][newDirection] = distance[x][y][direction] + 1000;
            pq.push({distance[x][y][newDirection], x, y, newDirection});
            parents[x][y][newDirection].push_back({x, y, direction});
        }
    }
    ll chepeastPath = LLONG_MAX;
    for (int endD = 0; endD <= 3; endD++) {
        chepeastPath = min(chepeastPath, distance[endx][endy][endD]);
    }
    cout<<"Cheapest path: "<<chepeastPath<<endl;

    vector<int> endDirections;
    for (int endD = 0; endD <= 3; endD++) {
        if (chepeastPath == distance[endx][endy][endD]) {
            endDirections.push_back(endD);
        }
    }

    /*for (int i = 1; i <= 3; i++) {
        cout<<"Parents of 1, "<<i<<": ";
        for (auto & [x,y] : parents[1][i]) {
            cout<<x<<", "<<y<<"; ";
        }
        cout<<endl;
    }
    for (int i = 2; i <= 4; i++) {
        cout<<"Parents of 3, "<<i<<": ";
        for (auto & [x,y] : parents[3][i]) {
            cout<<x<<", "<<y<<"; ";
        }
        cout<<endl;
    }
    cout<<"Parents of 2, 4: ";
        for (auto & [x,y] : parents[2][4]) {
            cout<<x<<", "<<y<<"; ";
        }
    cout<<endl;
    cout<<"Parents of 1, 4: ";
        for (auto & [x,y] : parents[1][4]) {
            cout<<x<<", "<<y<<"; ";
        }
    cout<<endl;*/
    queue<node> parentsBfs;
    for (auto & endD : endDirections) {
        cout<<"Possible End direction: "<<endD<<endl;
        parentsBfs.push({endx, endy, endD});

    }
    vector<vector<bool>> visitedLocations(m, vector<bool>(n, false));
    vector<vector<vector<bool>>> visitedNodes(m, vector<vector<bool>>(n, vector<bool>(4,false)));
    visitedLocations[endx][endy] = true;
    while (!parentsBfs.empty())
    {
        auto [x, y, d] = parentsBfs.front();
        parentsBfs.pop();
        for (auto &[px, py, pd] : parents[x][y][d])
        {
            if (!visitedNodes[px][py][pd])
            {
                visitedLocations[px][py] = true;
                visitedNodes[px][py][pd] = true;
                parentsBfs.push({px, py, pd});
            }
        }
    }

    
    int answer = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visitedLocations[i][j])
            {
                answer++;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] != '#' && visitedLocations[i][j])
            {
                cout<<"O";
            } else 
            {
                cout<<grid[i][j];
            }
        }
        cout<<endl;
    }
    //}
    cout << answer << endl;
}
