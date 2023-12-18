#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[]) {
    string str;

    vector<pair<long,long>> coords;
    long x=0, y=0, l=0;

    coords.push_back(make_pair(0,0));
    while(getline(cin, str)) {
        if(str.empty()) continue;
        istringstream iss(str);

        char d; int a;
        iss >> d >> a;
        string s; iss >> s;
        d = s[7];
        s = string(s.begin()+2, s.end()-2);
        a = stoi(s, 0, 16);

        switch (d) {
            case '0': x += a; break;
            case '2': x -= a; break;
            case '3': y += a; break;
            case '1': y -= a; break;
            default: break;
        }

        l += a;
        coords.push_back(make_pair(x,y));
    }

    for(auto [a,b]: coords) {
        cout << a << ',' << b << '\n';
    }

    long ans = 0;
    auto sz = coords.size();
    for(int i=1; i<sz; ++i) {
        auto [a,b] = coords[i-1];
        auto [c,d] = coords[i];
        ans += a*d - b*c;
    }

    cout << abs(ans/2) + l/2 +1 << '\n';

    return 0;
}
