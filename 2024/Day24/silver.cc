#include <bits/stdc++.h>

using namespace std;

int main() {
    string str;
    while (getline(cin, str)) {
        if (str.size() < 6) {
            break;
        }
        string wire = str.substr(0,3);
        int value = str[5] - '0';
        //vals[wire] = value;
    }
    list<tuple<string, string, string, string>> gates;
    while (getline(cin, str)) {
        istringstream stream(str);
        string in1, gate, in2, arrow, out;
        stream >> in1 >> gate >> in2 >> arrow >> out;
        gates.push_back({in1, gate, in2, out});
    }
    list<tuple<string, string, string, string>> ogGates = gates;
    
    const unsigned long long min = 1;
    const unsigned long long max = (1ULL << 44); // 2^4
    // Create a random device and seed the generator
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // Define the distribution within the range
    std::uniform_int_distribution<unsigned long long> dist(min, max);
    int it = 0;
    int right = 0;
    int wrong = 0;
    while (true) {
        it++;
        if (it > 2000) {
            break;
        }
        auto x = dist(gen);
        auto y = dist(gen);
        bitset<48> xbits(x);
        bitset<48> ybits(y);
        
        unordered_map<string, int> vals;
        for (size_t i = 0; i < 48; ++i) {
            string filler = "";
            if (i < 10) {
                filler = "0";
            }
            string key = "x" + filler + std::to_string(i); // Format key as "x00", "x01", ...
            //cout<<key<<endl;
            vals[key] = xbits[i]; // Assign the corresponding bit value
            key[0] = 'y';
            //cout<<key<<endl;
            vals[key] = ybits[i];
        }
        bitset<48> z;
        gates = ogGates;
        while (!gates.empty()) {
            //cout<<gates.size()<<endl;
            for (auto it = gates.begin(); it != gates.end(); ) {
                auto [in1, gate, in2, out] = *it;
                if (vals.count(in1) && vals.count(in2)) {
                    if (gate == "AND") {
                        vals[out] = vals[in1] & vals[in2];
                    } else if (gate == "OR") {
                        vals[out] = vals[in1] | vals[in2];
                    } else if (gate == "XOR") {
                        vals[out] = vals[in1] ^ vals[in2];
                    }
                    if (out[0] == 'z') {
                        int index = stoi(out.substr(1));
                        z[index] = vals[out];
                    }
                    it = gates.erase(it);
                } else {
                    it++;
                }
            }
        }
        unsigned long long result = z.to_ullong();
        if (result != x + y) {
            cout<<"Wrong sum: "<<endl;
            cout<<"x: "<<x<<endl;
            cout<<"y: "<<y<<endl;
            cout<<"wrong output: "<<result<<endl;
            cout<<"Correct coutnput: "<<x + y<<endl;
            cout<<"x: "<<xbits<<endl;
            cout<<"y: "<<ybits<<endl;
            bitset<48> wrongBits(result);
            bitset<48> rightBits(x+y);
            cout<<"W: "<<wrongBits<<endl;
            cout<<"C: "<<rightBits<<endl;
            wrong++;
        } else {
            cout<<"Right: "<<result<<endl;
            cout<<"x: "<<x<<endl;
            cout<<"y: "<<y<<endl;
            right++;
        }
    }
    cout<<"Wrong: "<<wrong<<endl;
    cout<<"Right: "<<right<<endl;

}
