#include <bits/stdc++.h>
using namespace std;

enum Type {
    CONJ, FLIP
};

struct Node {
    Type t;
    bool state;
    vector<string> out;

    map<string, bool> in;
};

struct Info {
    string parent;
    string name;
    bool signal; 
};

string rxParent;

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

vector<string> getOutputs(string parent, istringstream& iss) {
    vector<string> o;
    string s;
    while(getline(iss, s, ',')){
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        if(s == "rx") rxParent = parent;
        if(!s.empty()) o.push_back(s);
    }
    return o;
}

int main(int argc, char const *argv[]) {
    map<string, Node> nodes;
    vector<string> broadcaster;

    string str;
    while(getline(cin, str)) {
        if(str.empty()) continue;

        istringstream iss(move(str));
        char c = iss.get();
        if(c == '&') { //Conjuction
            string name; iss >> name;
            iss >> str;
            nodes.insert(make_pair(name, Node { CONJ, false, getOutputs(name, iss) }));
        } else if(c == '%') { //Flip-flop
            string name; iss >> name;
            iss >> str;
            nodes.insert(make_pair(name, Node { FLIP, false, getOutputs(name, iss) }));
        } else { //Broadcaster
            iss >> str >> str; //Buffer
            broadcaster = getOutputs("", iss);
        }
    }

    for(auto& [s, n]: nodes) {
        for(auto w: n.out) {
            if(nodes[w].t == CONJ) {
                nodes[w].in.insert(make_pair(s, false));
            }
        }
    }

    cout << rxParent << '\n';

    long ans = 1;
    for(auto e: broadcaster) {
        long l = 0;

        while(true) {
            l++;

            bool rx = false;
            queue<Info> q;
            q.push(Info{ "", e, false }); // First nodes are always flip-flops

            while(!q.empty()) {
                auto info = q.front();
                q.pop();

                auto& n = nodes[info.name];

                if(n.t == FLIP) {
                    if(info.signal == true) continue;

                    n.state = !n.state;
                    for(auto w: n.out) {
                        q.push(Info{info.name, w, n.state});
                    }
                } else { //Conjuction
                    n.in[info.parent] = info.signal;

                    bool a = true;
                    for(auto e: n.in) {
                        a &= e.second;
                    }

                    n.state = !a;

                    for(auto w: n.out) {
                        q.push(Info{info.name, w, n.state});
                        if(w == rxParent && n.state == true) 
                            rx = true;
                    }
                }
            }

            if(rx) {
                cout << l << '\n';
                break;
            }
        }

        ans = ans/gcd(ans, l) * l;
    }

    cout << '\n' << ans << '\n';

    return 0;
}
