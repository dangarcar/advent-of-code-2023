#include <bits/stdc++.h>
using namespace std;

constexpr long scale = 1000000;
set<int> empty_rows, empty_cols;

long distance(int a, int b, int c, int d) {
    long dist = 0;
    for(int i=a; i<c; ++i) {
        if(empty_rows.count(i))
            dist += scale;
        else 
            dist++;
    }
    
    for(int j=b; j<d; ++j) {
        if(empty_cols.count(j))
            dist += scale;
        else 
            dist++;
    }
    
    return dist;
}


int main(int argc, const char* argv[]) {
    vector<string> board;
    string str;
    while(getline(cin, str)) {
        board.push_back(str);
    }

    for(int i=0; i<board.size(); ++i) {
        if(find(board[i].begin(), board[i].end(), '#') == board[i].end()) {
            empty_rows.insert(i);
        }
    }

    for(int i=0; i<board[i].length(); ++i) {
        bool gal = false;
        for(auto s: board){
            if(s[i] == '#')
                gal = true;
        }

        if(!gal)
            empty_cols.insert(i);
    }

    long total = 0;
    
    for(int i=0; i<board.size(); ++i) {
        for(int j=0; j<board[i].length(); ++j) {
            for(int k=0; k<board.size(); ++k) {
                for(int l=0; l<board[i].length(); ++l) {
                    if(board[i][j] == '#' && board[k][l] == '#') {
                        total += distance(i,j,k,l);
                    }
                }
            }
        }
    }

    cout << '\n' << total << '\n';
} 