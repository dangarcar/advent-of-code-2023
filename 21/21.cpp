#include <bits/stdc++.h>
using namespace std;
 
/*
I coded a BFS for the first part but then changed it, so it hasn't been saved.
My solution is inspired in this one: https://github.com/villuna/aoc23/wiki/A-Geometric-solution-to-advent-of-code-2023,-day-21
*/

constexpr int STEPS = 26501365;
constexpr long INF = 1e18;

int R,C;

int incR[] = {1,-1,0,0};
int incC[] = {0,0,-1,1};

vector<string> board;

int main(int argc, char const *argv[]) {
    string str;
    while(getline(cin, str)) {
        if(str.empty()) continue;
        board.push_back(str);
    }

    R = board.size();
    C = board[0].size();

    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            if(board[i][j] == 'S') {
                vector<vector<long>> dist(R, vector<long>(C, INF));
                queue<pair<long,long>> q;
                dist[i][j] = 0;
                q.push({i,j});

                while(!q.empty()) {
                        auto [r,c] = q.front();
                        q.pop();

                    for(int k=0; k<4; ++k) {
                        long nr = r + incR[k];
                        long nc = c + incC[k];

                        if(0 <= nr && nr < R
                        && 0 <= nc && nc < C
                        && board[nr][nc] != '#'
                        && dist[nr][nc] == INF) {
                            dist[nr][nc] = dist[r][c] + 1;
                            q.push({nr, nc});
                        }
                    }
                }

                long even=0, even_corner=0, odd=0, odd_corner=0;
                for(auto v: dist) {
                    for(auto e: v) {
                        if(e == INF) continue;
                        if(e%2 == 0) {
                            even++;
                            if(e > 65) even_corner++;
                        } else {
                            odd++;
                            if(e > 65) odd_corner++;
                        }
                    }
                }

                long n = STEPS/R;
                cout << n << '\n';
                long ans = (n+1)*(n+1)*odd + n*n*even - (n+1)*odd_corner + n*even_corner;
                cout << ans << '\n';
            }
        }
    }
    return 0;
}