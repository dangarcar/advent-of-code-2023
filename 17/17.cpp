#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;

enum Direction {
    UP, RIGHT, LEFT, DOWN, NONE
};

vector<vector<int>> board;
int R,C;

pair<Direction,Direction> deg90[] = {
    {RIGHT, LEFT},
    {UP, DOWN},
    {UP, DOWN},
    {RIGHT, LEFT}
};

int incC[4] = {0,1,-1,0};
int incR[4] = {-1,0,0,1};
 
struct Data {
    int r,c;
    Direction d;
    int t;
};

using info = pair<int, Data>;

bool operator<(const info& a, const info& b) {
    return a.first < b.first;
}

int main(int argc, char const *argv[]) {
    string str;
    while(getline(cin, str)) {
        if(str.empty()) continue;
        board.push_back({});
        for(auto c: str) {
            board[board.size()-1].push_back(c-'0');
        }
    }

    R = board.size();
    C = board[0].size();

    /*for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            cout << board[i][j];
        }
        cout << '\n';
    }*/

    vector<vector<vector<vector<int>>>> dist(R, vector<vector<vector<int>>>(C, vector<vector<int>>(4, vector<int>(10, INF))));
    priority_queue<info, vector<info>, greater<info>> pq;
    dist[0][0][DOWN][0] = 0;
    dist[0][0][RIGHT][0] = 0;
    pq.push(make_pair(0, Data{0,0,DOWN,0}));
    pq.push(make_pair(0, Data{0,0,RIGHT,0}));

    while(!pq.empty()) {
        const auto [d, data] = pq.top();
        pq.pop();

        const auto r = data.r, c = data.c, t = data.t;
        const Direction dir = data.d;

        if(d > dist[r][c][dir][t])
            continue;

        if(t < 9) { //Go forward
            int nr = r + incR[dir];
            int nc = c + incC[dir];

            if(0 <= nr && nr < R
            && 0 <= nc && nc < C) {
                int cst = board[nr][nc];
                if(d+cst < dist[nr][nc][dir][t+1]) {
                    dist[nr][nc][dir][t+1] = d+cst;
                    pq.push(make_pair(d+cst, Data{nr,nc,dir,t+1}));
                }
            }
        }

        if(t >= 3) {
            auto [adir, bdir] = deg90[dir];

            int nr = r + incR[adir];
            int nc = c + incC[adir];
            if(0 <= nr && nr < R
            && 0 <= nc && nc < C) {
                int cst = board[nr][nc];
                if(d+cst < dist[nr][nc][adir][0]) {
                    dist[nr][nc][adir][0] = d+cst;
                    pq.push(make_pair(d+cst, Data{nr,nc,adir,0}));
                }
            }

            nr = r + incR[bdir];
            nc = c + incC[bdir];
            if(0 <= nr && nr < R
            && 0 <= nc && nc < C) {
                int cst = board[nr][nc];
                if(d+cst < dist[nr][nc][bdir][0]) {
                    dist[nr][nc][bdir][0] = d+cst;
                    pq.push(make_pair(d+cst, Data{nr,nc,bdir,0}));
                }
            }
        }
    }

    int ans = INF;
    for(int i=0; i<4; ++i) {
        for(int j=3; j<10; ++j) {
            ans = min(ans, dist[R-1][C-1][i][j]);
        }
    }

    cout << '\n' << ans << '\n';
    
    return 0;
}
