#include <bits/stdc++.h>
using namespace std;

struct Entry {
    long x,m,a,s;
};

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

bool accepted(const string& insName, const Entry& e) {
    if(insName == "A")
        return true;
    else if(insName == "R")
        return false;

    const auto& inSet = instructions[insName];

    string next;
    for(auto ins: inSet.ins) {
        long v;
        switch(ins.v) {
            case 'x': v = e.x; break;
            case 'm': v = e.m; break;
            case 'a': v = e.a; break;
            case 's': v = e.s; break;
            default: cerr << "Not supposed to reach here!\n";
        }

        bool t = (ins.sym == '>')? (v > ins.w) : (v < ins.w);
        if(t) {
            next = ins.next;
            break;
        }
    }

    if(next.empty())
        next = inSet.def;

    return accepted(next, e);
}

int main(int argc, char const *argv[]) {
    vector<Entry> entries;

    string str;
    while(getline(cin, str)) {
        if(str.empty()) continue;

        char c;
        istringstream iss(move(str));
        string name;
        while(iss >> c, c != '{') 
            name += c;

        if(name.empty()) { //Entry
            Entry e;
            iss.ignore(2); iss >> e.x;
            iss.ignore(3); iss >> e.m;
            iss.ignore(3); iss >> e.a;
            iss.ignore(3); iss >> e.s;
            entries.push_back(e);
        } else { //Instruction
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
    }

    long ans = 0;
    for(const auto& e: entries) {
        if(accepted("in", e))
            ans += e.x + e.m + e.a + e.s;
    }

    cout << ans << '\n';

    return 0;
}
