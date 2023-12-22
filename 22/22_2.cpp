#include <bits/stdc++.h>
using namespace std;

/*
It's brute force but only needs 6 min in my WSL2 instance because of some little optimizations
*/

struct Brick {
    long x1,y1,z1;
    long x2,y2,z2;
};

struct counting_iterator {
    size_t count;
    counting_iterator& operator++() { ++count; return *this; }

    struct black_hole { void operator=(int) {} };
    black_hole operator*() { return black_hole(); }
};

vector<Brick> bricks;

bool isOver(const Brick& a, const Brick& b) {
    if (a.x1 > b.x2 || b.x1 > a.x2)
        return false;

    if (a.y2 < b.y1 || b.y2 < a.y1)
        return false;

    return a.z1-1 == b.z2;
}

int main(int argc, char const *argv[]) {
    string str;
    while(getline(cin, str)) {
        if(str.empty()) continue;

        istringstream iss(str);
        Brick b; char c;
        iss >> b.x1 >> c >> b.y1 >> c >> b.z1;
        iss.ignore();
        iss >> b.x2 >> c >> b.y2 >> c >> b.z2;

        bricks.push_back(b);
    }

    auto sz = bricks.size();
    sort(bricks.begin(), bricks.end(), [](const auto& a, const auto& b){
        return a.z1 < b.z1;
    });

    vector<vector<int>> adj(sz);
    vector<vector<int>> len(sz);

    for(int i=0; i<sz; ++i) {
        while(1) {
            bool over = bricks[i].z1 == 1;
            for(int j=0; j<i; ++j) {
                if(isOver(bricks[i], bricks[j])) {
                    over = true;
                    len[i].push_back(j);
                    adj[j].push_back(i);
                }
            }

            if(over) break;
            
            bricks[i].z1--;
            bricks[i].z2--;
        }
    }

    vector<int> dist(sz, -1);

    long ans = 0;
    for(int i=0; i<sz; ++i) {
        queue<int> q;
        set<int> visited;
        visited.insert(i);
        q.push(i);

        while(!q.empty()) {
            auto e = q.front();
            q.pop();

            for(auto j: adj[e]) {
                auto a = set_intersection(visited.begin(), visited.end(), len[j].begin(), len[j].end(), counting_iterator()).count;
                if(a == len[j].size()) {
                    dist[j] = visited.size();
                    visited.insert(j);
                    q.push(j);
                }
            }
        }

        ans += max(0UL, visited.size()-1);
        cout << i << ' ' << ans << '\n';
    }
    cout << sz << '\n';
    cout << ans << '\n';

    return 0;
}
