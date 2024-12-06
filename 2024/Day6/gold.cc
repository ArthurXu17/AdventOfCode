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
    //cout<<n<<" x "<< m<<endl;
    vector<vector<set<pair<int, int>>>> previousDirections(n, vector<set<pair<int, int>>>(m, set<pair<int, int>>())); // for each location, store the directions that we've been at that location
    int dx = -1;
    int dy = 0;
    int result = 0;
    while (true) {
        //cout<<x<<", "<<y<<endl;
        previousDirections[x][y].insert(make_pair(dx,dy));
        if (goesOutOfBounds(x,y,dx,dy,m,n)) {
            break;
        }
        int new_dx = dx;
        int new_dy = dy;
        changeDirection(new_dx, new_dy);
        if (previousDirections[x][y].find(make_pair(new_dx, new_dy)) != previousDirections[x][y].end()) {
            result++;
        }
        if (grid[x+dx][y+dy] == '#') {
            changeDirection(dx,dy);
        }
        x += dx;
        y += dy;
    }
    cout<<result<<endl;
}

