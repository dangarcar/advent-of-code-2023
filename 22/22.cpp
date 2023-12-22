#include <bits/stdc++.h>
using namespace std;

struct Brick {
    long x1,y1,z1;
    long x2,y2,z2;
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

    vector<set<int>> adj(sz);
    vector<set<int>> s(sz);

    for(int i=0; i<sz; ++i) {
        while(1) {
            bool over = bricks[i].z1 == 1;
            for(int j=0; j<i; ++j) {
                if(isOver(bricks[i], bricks[j])) {
                    over = true;
                    adj[i].insert(j);
                }
            }

            if(over) break;
            
            bricks[i].z1--;
            bricks[i].z2--;
        }
    }

    long ans = 0;
    for(int i=0; i<sz; ++i) {
        bool needed = false;
        for(int j=i+1; j<sz; ++j) {
            if(adj[j].size() == 1 && adj[j].count(i)) {
                needed = true;
                break;
            }
        }

        if(!needed) 
            ans++;
    }
    cout << sz << '\n';
    cout << ans << '\n';

    return 0;
}
