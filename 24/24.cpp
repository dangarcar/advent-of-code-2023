#include <bits/stdc++.h>
using namespace std;

struct Line {
    long double x,y,z, dx, dy, dz;
};

/*
Resolves system of equations to determine position using the point and slope formula
y = y1 + m1(x - x1) & y = y2 + m2(x - x2)
y1 + m1x -m1x1 = y2 + m2x - m2x2
(m1 - m2)x = -y1 + y2 + m1x1 - m2x2
x = (-y1 + y2 + m1x1 - m2x2)/(m1 - m2)
*/
pair<long double, long double> intersection(Line l1, Line l2) {
    auto m1 = l1.dy/l1.dx, m2 = l2.dy/l2.dx;

    if(abs(m1-m2) < FLT_EPSILON)
        return make_pair(NAN, NAN);

    auto x = (-l1.y + l2.y + m1*l1.x - m2*l2.x)/(m1 - m2);
    auto y = m1*x + l1.y - m1*l1.x;

    return make_pair(x, y);
}

long double L = 200000000000000.0L, R = 400000000000000.0L;

int main(int argc, char const *argv[]) {
    string str;
    vector<Line> lines;

    while(getline(cin, str)) {
        if(str.empty()) continue;
        istringstream iss(str);

        long double x,y,z, dx, dy, dz;
        char ch;
        iss >> x >> ch >> y >> ch >> z >> ch >> dx >> ch >> dy >> ch >> dz;
        lines.push_back({x, y, z, dx, dy, dz});
    }

    auto sz = lines.size();

    long ans = 0;
    for(int i=0; i<sz; ++i) {
        for(int j=i+1; j<sz; ++j) {
            if(i==j) continue;
            auto [x, y] = intersection(lines[i], lines[j]);

            if(!isnanl(x) && !isnanl(y)
            && L <= x && x <= R
            && L <= y && y <= R) {
                if(lines[i].dx >= 0 && x < lines[i].x
                || lines[i].dx <= 0 && x > lines[i].x
                || lines[j].dx >= 0 && x < lines[j].x
                || lines[j].dx <= 0 && x > lines[j].x
                || lines[i].dy >= 0 && y < lines[i].y
                || lines[i].dy <= 0 && y > lines[i].y
                || lines[j].dy >= 0 && y < lines[j].y
                || lines[j].dy <= 0 && y > lines[j].y) {
                    continue;
                }

                cout << x << ' ' << y << '\n';
                ans++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}