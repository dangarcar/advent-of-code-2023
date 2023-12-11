#include <bits/stdc++.h>
using namespace std;

long gcd(long a, long b) {
    while(true) {
        if (a == 0) 
            return b;
        b %= a;
        if (b == 0)
            return a;
        a %= b;
    }
}

int main(int argc, char const *argv[]) {
    string way;
    cin >> way;
    size_t sz = way.length();

    cin.ignore();
    cin.ignore();

    map<string, pair<string,string>> m;
    string str;
    while(getline(cin, str)) {
        istringstream iss(str);
        string src, l, r;
        char c;
        iss >> src >> c >> c >> l >> r;
        
        m[src] = make_pair(l.substr(0,3), r.substr(0,3));
    }

    /*for(auto [a, p]: m) {
        cout << a << ' ' << p.first << ' ' << p.second << '\n';
    }*/

    cout << "Input done\n";

    vector<string> currs;    
    for(auto [s,g]: m) {
        if(s[2] == 'A')
            currs.push_back(s);
    }
    //cout << currs.size() << '\n';
    vector<long> sols;

    for(auto curr: currs) {
        long step = 0;
        while(curr[2] != 'Z') {
            char c = way[step%sz];
            if(c == 'R') {
                curr = m[curr].second;
            }
            else {
               curr = m[curr].first; 
            }
            ++step;
        }

        sols.push_back(step);
    }

    for(auto s:sols)
        cout << s << ' ';
    cout << '\n';

    auto ans = accumulate(sols.begin(), sols.end(), 1L, [](long a, long b){
        long t = gcd(a, b);
        return t? (a/t * b) : 0;
    });
    cout << ans << '\n';

    return 0;
}