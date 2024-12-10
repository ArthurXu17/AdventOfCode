#include <bits/stdc++.h>

using namespace std;

int main() {
    string str;
    cin>>str;
    cout<<str.size()<<endl;
    int memorySize = 0;
    for (auto & ch : str) {
        memorySize += (ch - '0');
    }
    vector<int> memory(memorySize, 0);
    int id = 0;
    int memoryIndex = 0;
    int usedSpace = 0;
    for (int i = 0; i < str.size(); i++) {
        int length = str[i] - '0';
        if (i % 2 == 1) { // free space
            for (int j = 0; j < length; j++) {
                memory[memoryIndex] = -1;
                memoryIndex++;
            }
        } else { // things
            for (int j = 0; j < length; j++) {
                memory[memoryIndex] = id;
                memoryIndex++;
            }
            id++;
            usedSpace += length;
        }
    }
    int prevFreeIndex = -1;
    unordered_map<int, int> nextFreeIndex; // map each free disk space index to the next free index
    //cout<<"Memory Before Transformation: "<<endl;
    for (int i = 0; i < memorySize; i++) {
        //cout<<memory[i]<<" ";
        if (memory[i] == -1) {
            nextFreeIndex[prevFreeIndex] = i;
            prevFreeIndex = i;
        }
    }
    //cout<<endl;

    int freeIndex = nextFreeIndex[-1];
    int dataIndex = memorySize - 1;
    while (dataIndex >= usedSpace) {
        if (memory[dataIndex] == -1) {
            dataIndex--;
            continue;
        }
        memory[freeIndex] = memory[dataIndex];
        memory[dataIndex] = -1;
        freeIndex = nextFreeIndex[freeIndex];
        dataIndex--;
    }
    long long result = 0;
    //cout<<"Memory After Transformation: "<<endl;
    for (int i = 0; i < memorySize; i++) {
        //cout<<memory[i]<<" ";
        if (memory[i] != -1) {
            result += i * memory[i];
        }
    }
    //cout<<endl;
    cout<<result<<endl;

}
