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

vector<string> getOutputs(istringstream& iss) {
    vector<string> o;
    string s;
    while(getline(iss, s, ',')){
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
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
            nodes.insert(make_pair(name, Node { CONJ, false, getOutputs(iss) }));
        } else if(c == '%') { //Flip-flop
            string name; iss >> name;
            iss >> str;
            nodes.insert(make_pair(name, Node { FLIP, false, getOutputs(iss) }));
        } else { //Broadcaster
            iss >> str >> str; //Buffer
            broadcaster = getOutputs(iss);
        }
    }

    for(auto& [s, n]: nodes) {
        for(auto w: n.out) {
            if(nodes[w].t == CONJ) {
                nodes[w].in.insert(make_pair(s, false));
            }
        }
    }

    long low = 0, high = 0;
    for(int i=0; ; ++i) {
        queue<Info> q;
        for(auto e: broadcaster)
            q.push(Info{ "", e, false }); // First nodes are always flip-flops

        low++;

        while(!q.empty()) {
            auto info = q.front();
            q.pop();

            if(info.signal) {
                high++;
            } else {
                low++;
            }

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
                }
            }
        }
    }

    cout << '\n' << low*high << '\n';

    return 0;
}
