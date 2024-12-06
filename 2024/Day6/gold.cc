#include <bits/stdc++.h>

using namespace std;

void changeDirection(int& dx, int& dy) {
    if (dx == -1 && dy == 0) {
        dx = 0;
        dy = 1;
    } else if (dx == 0 && dy == 1) {
        dx = 1;
        dy = 0;
    } else if (dx == 1 && dy == 0) {
        dx = 0;
        dy = -1;
    } else if (dx == 0 && dy == -1) {
        dx = -1;
        dy = 0;
    }
}

bool goesOutOfBounds(int x, int y, int dx, int dy, int m, int n) {
    return x + dx < 0 || x + dx >= n || y + dy < 0 || y+dy >= m;
}

    bool isCycle(vector<string>& grid, int x, int y)
    {

        vector<pair<int, int>> directions =  {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        int direction = 0;
        map<tuple<int, int, int>, bool> visited;
        pair<int, int> current = make_pair(x,y);
        while (current.first >= 0 && current.first < grid.size() && current.second >= 0 && current.second < grid[0].size())
        {
            if (visited[{current.first, current.second, direction}])
            {
                return true;
            }
            visited[{current.first, current.second, direction}] = true;
            if (
                current.first + directions[direction].first < 0 ||
                current.first + directions[direction].first >= grid.size() ||
                current.second + directions[direction].second < 0 ||
                current.second + directions[direction].second >= grid[0].size())
            {
                return false;
            }
            if (grid[current.first + directions[direction].first][current.second + directions[direction].second] == '#')
            {
                direction++;
                direction %= 4;
            }
            else
            {
                current.first += directions[direction].first;
                current.second += directions[direction].second;
            }
        }
        return false;
    }

bool isLoop(vector<string>& grid, int x, int y, int m, int n) {

    vector<vector<set<pair<int, int>>>> previousDirections(n, vector<set<pair<int, int>>>(m, set<pair<int, int>>())); // for each location, store the directions that we've been at that location
    int dx = -1;
    int dy = 0;
    int result = 0;
    while (!(x < 0 || x >= n || y < 0 || y>= m)) {
        //cout<<x<<", "<<y<<endl;
        if (previousDirections[x][y].find(make_pair(dx, dy)) != previousDirections[x][y].end()) {
            return true;
        }
        previousDirections[x][y].insert(make_pair(dx,dy));
        
        if (!goesOutOfBounds(x,y,dx,dy,m,n) && grid[x+dx][y+dy] == '#') {
            changeDirection(dx,dy);
        } else {
            x += dx;
            y += dy;

        }
    }
    return false;
    /*
    int dx = -1;
    int dy = 0;
    int iterations = 0;
    while (true) {
        if (iterations > 4*m * n) {
            return true;
        }
        //cout<<x<<", "<<y<<endl;
        if (goesOutOfBounds(x,y,dx,dy,m,n)) {
            break;
        }
        if (grid[x+dx][y+dy] == '#') {
            changeDirection(dx,dy);
        }
        x += dx;
        y += dy;
        iterations++;
    }
    return false;*/
}

int main() {
    string str;
    vector<string> grid;
    int x, y;
    int i = 0;
    while (cin>>str) {
        grid.push_back(str);
        //cout<<"\""<<str<<"\""<<endl;
        //cout<<str.size()<<endl;
        for (int j = 0; j < str.size(); j++) {
            if (str[j] == '^') {
                x = i;
                y = j;
                //cout<<"Start: "<<x<<", "<<y<<endl;
            }
        }
        i++;
    }
    int n = grid.size();
    int m = grid[0].size();
    int result = 0;
    cout<<n<<" x "<<m<<endl;
    // iteratively brute force adding obstacle at each coordinate
    int ob = 0;
    int blank = 0;
    int other = 0;
    for (auto & str : grid) {
        for (auto & c : str) {
            if (c == '#') {
                ob++;
            } else if (c == '.') {
                blank++;
            } else {
                other++;
            }
        }
    }
    cout<<"Obstacles: "<<ob<<endl;
    cout<<"Empty: "<<blank<<endl;
    cout<<"Start: "<<other<<endl;
    int checks = 0;
    set<pair<int, int>> correct;
    set<pair<int, int>> me;
    for (int i = 0; i < n ; i++) {
        cout<<i<<endl;
        for (int j = 0 ; j < m ;j++) {
            if (grid[i][j] != '.') {
                continue;
            }
            checks++;
            grid[i][j] = '#';
            if (isCycle(grid, x,y)) {
                //cout<<i<<", "<<j<<endl;
                correct.insert(make_pair(i,j));
            }
            if (isLoop(grid, x,y, m, n)) {
                //cout<<i<<", "<<j<<endl;
                me.insert(make_pair(i,j));
            }
            grid[i][j] = '.';
        }
    }
    cout<<checks<<endl;
    cout<<"Correct Size: "<<correct.size()<<endl;
    cout<<"MY Size: "<<me.size()<<endl;
    cout<<"MY Size2: "<<me.size()<<endl;
    
    cout<<"Correct not in mine: "<<endl;
    for (auto & p : correct){
        if (me.find(p) == me.end()) {
            cout<<p.first<<", "<<p.second<<endl;
        }
    }
    cout<<"Wrong but in mine: "<<endl;
    for (auto & p : me){
        if (correct.find(p) == correct.end()) {
            cout<<p.first<<", "<<p.second<<endl;
        }
    }

}

