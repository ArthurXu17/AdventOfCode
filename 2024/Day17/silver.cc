#include <bits/stdc++.h>

using namespace std;

int main() {
    int a,b,c;
    vector<int> instructions;
    int index = 0;
    cin>>a>>b>>c;
    int num;
    while (cin >> num) {
        instructions.push_back(num);
    }
    int n = instructions.size();
    
    while (index < n) {
        int opcode = instructions[index];
        index++;
        int combo = instructions[index];
        int literal = combo;
        //cout<<"Instruction at index "<<index<<endl;
        //cout<<opcode<<endl;
        //cout<<literal<<endl;
        if (combo == 4) {
            combo = a;
        } else if (combo == 5) {
            combo = b;
        } else if (combo == 6) {
            combo = c;
        }
        if (opcode == 0) {
            a = a / pow(2,combo);
        }else if (opcode == 1) {
            b = b ^ literal;
        } else if (opcode == 2) {
            b = combo % 8;
        } else if (opcode == 3) {
            if (a != 0) {
                index = literal;
                continue;
            }
        } else if (opcode == 4) {
            b = b ^ c;
        } else if (opcode == 5) {
            cout<<combo%8<<",";
        } else if (opcode == 6) {
            b = a / pow(2,combo); 
        } else if (opcode == 7) {
            c = a / pow(2,combo);
        }
        index ++;
    }
    cout<<endl;
}
