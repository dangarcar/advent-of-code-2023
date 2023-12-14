#include <bits/stdc++.h>
using namespace std;

long cycle(vector<string>& board) {
    for(int j=0; j<board[0].size(); ++j) {
        for(int i=0; i<board.size(); ++i) {
            if(board[i][j] == 'O') {
                board[i][j] = '.';
                
                int k=i;
                while(k > 0 && board[k-1][j] == '.')
                    --k;
                
                board[k][j] = 'O';
            }
        }
    }

    for(int i=0; i<board.size(); ++i) {
        for(int j=0; j<board[i].size(); ++j) {
            if(board[i][j] == 'O') {
                board[i][j] = '.';
                
                int k=j;
                while(k > 0 && board[i][k-1] == '.')
                    --k;
                
                board[i][k] = 'O';
            }
        }
    }

    for(int j=0; j<board[0].size(); ++j) {
        for(int i=board.size()-1; i>=0; --i) {
            if(board[i][j] == 'O') {
                board[i][j] = '.';
                
                int k=i;
                while(k+1 < board.size() && board[k+1][j] == '.')
                    ++k;
                
                board[k][j] = 'O';
            }
        }
    }

    for(int i=0; i<board.size(); ++i) {
        for(int j=board[0].size()-1; j>=0; --j) {
            if(board[i][j] == 'O') {
                board[i][j] = '.';
                
                int k=j;
                while(k+1 < board[0].size() && board[i][k+1] == '.')
                    ++k;
                
                board[i][k] = 'O';
            }
        }
    }

    long total=0;
    auto l = board.size();
    for(int i=0; i<l; ++i) {
        for(int j=0; j<board[0].size(); ++j) {
            if(board[i][j] == 'O')
                total += l-i;
        }
    }

    return total;
}

int main(int argc, char const *argv[]) {
    vector<string> board;
    string str;

    while(getline(cin, str)) {
        if(str.empty()) continue;
        board.push_back(str);
    }

    vector<pair<long,int>> c;
    vector<pair<long,int>> pos;
    for(int t=1; t<=1e9; ++t) {
        auto a = cycle(board);

        if(t < 1000) continue;

        if(pos.empty()) {
            if(!c.empty() && a == c[0].first)
                pos.push_back({a, t});
            else
                c.push_back({a, t});
        } else {
            pos.push_back({a, t});

            auto last = pos.size()-1;
            if(pos[last].first != c[last].first) {
                c.insert(c.end(), pos.begin(), pos.end());
                pos.clear();
            } else if(pos.size() == c.size()) {
                break;
            }
        }
    }

    auto sz = c.size();
    auto mod = 1000000000 % sz;
    long n = -1;
    for(auto [a,t]: c) {
        if(mod == t%sz) 
            n = a;
    }
    cout << '\n' << n << '\n';

    return 0;
}
