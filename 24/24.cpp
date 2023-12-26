#include <bits/stdc++.h>
using namespace std;

struct Line {
    long x,y,z, dx, dy, dz;
};

int main(int argc, char const *argv[]) {
    string str;
    vector<Line> lines;

    while(getline(cin, str)) {
        if(str.empty()) continue;
        istringstream iss(str);

        long x,y,z, dx, dy, dz;
        char ch;
        iss >> x >> ch >> y >> ch >> z >> ch >> dx >> ch >> dy >> ch >> dz;
        lines.push_back({x, y, z, dx, dy, dz});
    }

    long ans = 0;
    cout << ans << '\n';

    return 0;
}