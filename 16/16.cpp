#include <bits/stdc++.h>
using namespace std;

enum Direction {
    UP, RIGHT, LEFT, DOWN, NONE
};

vector<vector<array<bool,4>>> visited;
vector<string> board;

int R,C;

pair<Direction,Direction> getDirection(char c, Direction d) {
    auto p = make_pair(d, NONE);

    switch(c) {
        case '\\':
            if(d == UP) p.first = LEFT;
            else if(d == DOWN) p.first = RIGHT;
            else if(d == LEFT) p.first = UP;
            else if(d == RIGHT) p.first = DOWN;
            break;
        case '/':
            if(d == UP) p.first = RIGHT;
            else if(d == DOWN) p.first = LEFT;
            else if(d == LEFT) p.first = DOWN;
            else if(d == RIGHT) p.first = UP;
            break;
        case '|':
            if(d == LEFT || d == RIGHT) 
                p = make_pair(UP, DOWN);
            break;
        case '-':
            if(d == DOWN || d == UP) 
                p = make_pair(LEFT, RIGHT);
            break;
        default:
            break;
    };

    return p;
}

void dfs(int r, int c, Direction d) {
    visited[r][c][d] = true;

    auto [a,b] = getDirection(board[r][c], d);

    if(a != NONE) {
        int nr = r + (a==DOWN? 1:0) + (a==UP? -1:0);
        int nc = c + (a==LEFT? -1:0) + (a==RIGHT? 1:0);
        if(0 <= nr && nr < R
        && 0 <= nc && nc < C
        && visited[nr][nc][a] == false) {
            dfs(nr, nc, a);
        }
    }

    if(b != NONE) {
        int nr = r + (b==DOWN? 1:0) + (b==UP? -1:0);
        int nc = c + (b==LEFT? -1:0) + (b==RIGHT? 1:0);
        if(0 <= nr && nr < R
        && 0 <= nc && nc < C
        && visited[nr][nc][b] == false) {
            dfs(nr, nc, b);
        }
    }
}

long solve(int r, int c, Direction d) {
    long ans = 0;

    visited.assign(R, vector<array<bool,4>>(C, {0,0,0,0}));
    dfs(r,c,d);

    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            auto& w = visited[i][j];
            auto a = w[0]+w[1]+w[2]+w[3];
            ans += a!=0;
        }
    }

    return ans;
}

int main(int argc, char const *argv[]) {
    string str;
    while(getline(cin, str)) {
        if(!str.empty())
            board.push_back(str);
    }

    R = board.size();
    C = board[0].size();

    /*for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            auto& w = visited[i][j];
            auto a = w[0]+w[1]+w[2]+w[3];

            if(board[i][j] == '.')
                cout << (a? char(a+'0'):'.');
            else
                cout << board[i][j];
        }
        cout << '\n';
    }*/

    long ans = 0;
    for(int i=0; i<R; ++i) {
        ans = max(ans, solve(i, 0, RIGHT));
        ans = max(ans, solve(i, C-1, LEFT));
    }

    for(int i=0; i<C; ++i) {
        ans = max(ans, solve(0, i, DOWN));
        ans = max(ans, solve(R-1, i, UP));
    }


    cout << '\n' << ans << '\n';

    return 0;
}
