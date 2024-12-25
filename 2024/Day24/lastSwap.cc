#include <bits/stdc++.h>

using namespace std;

int numRight(vector<array<string, 4>>& gates, std::mt19937_64& gen, std::uniform_int_distribution<unsigned long long>& dist) {
    int it = 0;
    int right = 0;
    int wrong = 0;
    auto ogGates = gates;
    while (true) {
        //cout<<it<<endl;
        it++;
        if (it > 50) {
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
        int lastSize = gates.size();
        //cout<<"Starting size: "<<lastSize<<endl;
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
            if (gates.size() == lastSize) {
                //cout<<"Doesn't terminate"<<endl;
                return 0;
            }
            lastSize = gates.size();
        }
        unsigned long long result = z.to_ullong();
        if (result == 0) {
            cout<<"Giving me zero"<<endl;
        }
        if (result != x + y) {
            /*cout<<"Wrong sum: "<<endl;
            cout<<"x: "<<x<<endl;
            cout<<"y: "<<y<<endl;
            cout<<"wrong output: "<<result<<endl;
            cout<<"Correct coutnput: "<<x + y<<endl;
            cout<<"x: "<<xbits<<endl;
            cout<<"y: "<<ybits<<endl;
            bitset<48> wrongBits(result);
            bitset<48> rightBits(x+y);
            cout<<"W: "<<wrongBits<<endl;
            cout<<"C: "<<rightBits<<endl;*/
            wrong++;
        } else {
            /*cout<<"Right: "<<result<<endl;
            cout<<"x: "<<x<<endl;
            cout<<"y: "<<y<<endl;*/
            right++;
        }
    }
    return right;
            
}

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
    vector<array<string, 4>> gates;
    while (getline(cin, str)) {
        istringstream stream(str);
        string in1, gate, in2, arrow, out;
        stream >> in1 >> gate >> in2 >> arrow >> out;
        gates.push_back({in1, gate, in2, out});
    }
    vector<array<string, 4>> ogGates = gates;
    
    const unsigned long long minX = 1;
    const unsigned long long maxY = (1ULL << 44); // 2^4
    // Create a random device and seed the generator
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // Define the distribution within the range
    std::uniform_int_distribution<unsigned long long> dist(minX, maxY);
    
    int maxRight = 0;
    for (int i = 0; i < gates.size(); i++) {
        cout<<i<<endl;
        for (int j = i + 1; j < gates.size(); j++) {
            //cout<<i<<", "<<j<<endl;
            swap(gates[i][3], gates[j][3]);
            int curRight = numRight(gates, gen, dist);
            if (curRight > maxRight) {
                cout<<"New Best: "<<curRight<<endl;
                cout<<"Swapping indices "<<i<<" and "<<j<<endl;
                cout<<"Swapping gates "<<ogGates[i][3]<<" and "<<ogGates[j][3]<<endl;
                maxRight = curRight;
            }
            gates = ogGates;
        }
    }

    

}
