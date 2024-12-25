#include <bits/stdc++.h>

using namespace std;

bool isXor(string s) {
    return s[0] == 'x' && isdigit(s[1]);
}

bool isAnd(string s) {
    return s[0] == 'a' && isdigit(s[1]);
}

bool isCarry(string s) {
    return s[0] == 'c' && isdigit(s[1]);
}

int main() {
    unordered_map<string, int> vals;
    string str;
    while (getline(cin, str)) {
        if (str.size() < 6) {
            break;
        }
        string wire = str.substr(0,3);
        int value = str[5] - '0';
        vals[wire] = value;
    }
    vector<array<string,4>> gates;
    
    unordered_map<string, string> rename;
    // initially rename a and x terms
    while (getline(cin, str)) {
        istringstream stream(str);
        string in1, gate, in2, arrow, out;
        stream >> in1 >> gate >> in2 >> arrow >> out;
        if (in1[0] == 'y' && in2[0] == 'x') {
            swap(in1, in2);
        }
        if (in1[0] == 'x') {
            in1[0] = 'r';
        }
        if (in2[0] == 'y') {
            in2[0] = 's';
        }
        if (in1[0] == 'r' && in2[0] == 's' && gate == "AND") {
            rename[out] =  "a" + in1.substr(1);
            /*if (in1.substr(1) == "25") { // swapping a25 and x25
                rename[out] = "x25";
                cout<<"x25 original: "<<out<<endl;
            }
            if (in1.substr(1) == "12") {
                // out here is z12, don't replace
                continue;
            }*/
        }
        if (in1[0] == 'r' && in2[0] == 's' && gate == "XOR") {
            if (in1.substr(1) == "00") {
                gates.push_back({in1, gate, in2, out});
                continue;
            }
            rename[out] =  "x" + in1.substr(1);
            /*if (in1.substr(1) == "25") { // swapping a25 and x25
                rename[out] = "a25";
                cout<<"a25 original: "<<out<<endl;
            }*/
        }
        gates.push_back({in1, gate, in2, out});
    }
    //rename["vdc"] = "a12"; // for swapping a12 with z12
    
    for (auto & arr : gates) {
        for (auto & str : arr) {
            if (rename.count(str)) {
                str = rename[str];
            }
        }
    }
    // reorder so that a/x terms come first
    for (auto & [in1, gate, in2, out]  : gates) {
        if ((in2[0] == 'a' || in2[0] == 'x') && isdigit(in2[1])) {
            swap(in1, in2);
        }
    }
    // finding carry terms
    for (auto & [in1, gate, in2, out]  : gates) {
        if (isAnd(in1) && gate == "OR") {
            string number = to_string(stoi(in1.substr(1)) + 1);
            if (number.size() == 1) {
                number = "0" + number;
            }
            rename[out] = "c" + number;
            cout<<"Replacing: "<<out<<" with "<<rename[out]<<endl;
        }
    }
    for (auto & arr : gates) {
        for (auto & str : arr) {
            if (rename.count(str)) {
                str = rename[str];
            }
        }
    }

    // finding h terms
    for (auto & [in1, gate, in2, out]  : gates) {
        if (isAnd(in1) && gate == "OR" && isCarry(out)) {
            rename[in2] = "h" + in1.substr(1);
        }
    }
    for (auto & arr : gates) {
        for (auto & str : arr) {
            if (rename.count(str)) {
                str = rename[str];
            }
        }
    }

    sort(gates.begin(), gates.end());
    ofstream firstWire;
    firstWire.open("FirstWire.txt");
    firstWire<<"Sorted by First Wire"<<endl;    
    for (auto [in1, gate, in2, out]  : gates) {
        firstWire<<in1<<" "<<gate<<" "<<in2<<" -> "<<out<<endl;
    }
    firstWire.close();

    ofstream outputWire;
    outputWire.open("OutputWire.txt");
    sort(gates.begin(), gates.end(), [](const auto& a, const auto& b) {
        return a[3] < b[3]; // Compare by the fourth element
    });
    outputWire<<"Sorted by Output Wire"<<endl;    
    for (auto [in1, gate, in2, out]  : gates) {
        outputWire<<in1<<" "<<gate<<" "<<in2<<" -> "<<out<<endl;
    }

    ofstream operation;
    operation.open("Operation.txt");
    sort(gates.begin(), gates.end(), [](const auto& a, const auto& b) {
        return a[1] < b[1]; // Compare by the fourth element
    });
    operation<<"Sorted by Operation"<<endl;    
    for (auto [in1, gate, in2, out]  : gates) {
        operation<<in1<<" "<<gate<<" "<<in2<<" -> "<<out<<endl;
    }
    operation.close();

    unordered_set<string> bad;

    for (auto & [in1, gate, in2, out]  : gates) {
        if (!isdigit(in1[1])) {
            bad.insert(in1);
        }
        if (!isdigit(in2[1])) {
            bad.insert(in2);
        }
        if (!isdigit(out[1])) {
            bad.insert(out);
        }
    }
    for (auto & str: bad) {
        cout<<str<<endl;
    }
    cout<<rename["mgw"]<<endl;
    cout<<rename["bds"]<<endl;

}
