#include <bits/stdc++.h>
using namespace std;

vector<long> getDerivative(const vector<long>& v){
    vector<long> dv(v.size()-1);
    for(int i=0; i<dv.size(); ++i) {
        dv[i] = v[i+1] - v[i];
    }

    return dv;
}

long next(vector<long> seq) {
    if(accumulate(seq.begin(), seq.end(), 0L) == 0L)
        return 0L;

    auto dv = getDerivative(seq);    
    return *seq.rbegin() + next(dv);
}

int main(int argc, char const *argv[]) {
    string str;
    long ans = 0;

    while(getline(cin, str)) {
        istringstream iss(str);
        vector<long> v;

        long a;
        while(iss >> a)
            v.push_back(a);

        reverse(v.begin(), v.end());

        /*for(auto e: v)
            cout << e << ' ';
        cout << next(v) << '\n';*/
        ans += next(v);
    }
    
    cout << ans << '\n';
    return 0;
}
