#include <bits/stdc++.h>

using namespace std;

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int processStringAtIndex(string& str, int i) {
    string num1;
    string num2;

    while (i < str.size() && isDigit(str[i])) {
        num1.push_back(str[i]);
        i++;
    }
    if (num1.empty()) {
        return -1;
    }
    if (str[i] != ',') {
        return -1;
    }
    i++;
    while (i < str.size() && isDigit(str[i])) {
        num2.push_back(str[i]);
        i++;
    }
    if (num2.empty()) {
        return -1;
    }
    if (str[i] != ')') {
        return -1;
    }
    return stoi(num1) * stoi(num2);
}

int main() {
    string str;
    getline(cin, str);
    int i = 0;
    int result = 0;
    int numMuls = 0;
    int strSize = str.size();
    cout<<"Str Size: "<<strSize<<endl;
    string reconstruction;
    while (i < str.size() - 4) {
        reconstruction.push_back(str[i]);
        //cout<<str[i]<<endl;
        if (str[i] == 'm' && str[i+1] == 'u' && str[i+2] == 'l' && str[i+3] == '(') {
            cout<<"mul index: "<<i<<endl;
            numMuls++;
            int multResult = processStringAtIndex(str, i + 4);
            if (multResult != -1) {
                result += multResult;
            }
        }
        i++;   
    }
    cout<<numMuls<<endl;
    cout<<result<<endl;
    //cout<<"Reconstruction: "<<reconstruction<<endl;
    //cout<<"Reconstruction size: "<<reconstruction.size()<<endl;

}