#include <bits/stdc++.h>
using namespace std;

using Entry = array<pair<long,long>, 4>;

struct Instruction {
    char v;
    char sym;
    long w;
    string next;
};

struct InstructionSet {
    vector<Instruction> ins;
    string def;
};

map<string, InstructionSet> instructions;
map<char, int> xmas = { {'x', 0}, {'m', 1}, {'a', 2}, {'s', 3} };

long solve(const string& insName, Entry e) {
    if(insName == "A")
        return accumulate(e.begin(), e.end(), 1L, [](long acc, const auto& r){
            return acc * max(0L, r.second - r.first +1);
        });
    else if(insName == "R")
        return 0L;

    const auto& inSet = instructions[insName];
    long ans = 0L;
    for(auto ins: inSet.ins) {
        Entry ne = e;
        auto i = xmas[ins.v];

        if(ins.sym == '>' && e[i].second > ins.w) {
            ne[i] = make_pair(ins.w+1, e[i].second);
            e[i] = make_pair(e[i].first, ins.w);
        }
        else if(e[i].first < ins.w) {
            ne[i] = make_pair(e[i].first, ins.w-1);
            e[i] = make_pair(ins.w, e[i].second);
        }

        ans += solve(ins.next, ne);
    }

    ans += solve(inSet.def, e);

    return ans;
}

int main(int argc, char const *argv[]) {
    string str;
    while(getline(cin, str)) {
        if(str.empty()) break;

        char c;
        istringstream iss(move(str));
        string name;
        while(iss >> c, c != '{') 
            name += c;

        InstructionSet inSet;
        while(getline(iss, str, ',')) {
            if(*str.rbegin() == '}') {
                inSet.def = string(str.begin(), str.end()-1);
                instructions[name] = inSet;
                break;
            }

            istringstream tokenizer(move(str));
            Instruction in;
            in.v = tokenizer.get();
            in.sym = tokenizer.get();
            tokenizer >> in.w;
            tokenizer.ignore();
            tokenizer >> in.next;

            inSet.ins.push_back(in);
        }
    }

    long ans = solve("in", Entry {
        make_pair(1,4000),
        make_pair(1,4000),
        make_pair(1,4000),
        make_pair(1,4000),
    });
    

    cout << ans << '\n';

    return 0;
}
