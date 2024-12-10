#include <bits/stdc++.h>

using namespace std;

int getFreeBlockIndexStart(vector<set<int>>& freeBlockSizeIndices, int blockSize) {
    int index = INT_MAX;
    int replacementBlockSize;
    for (int i = blockSize; i <= 9; i++) {
        if (!freeBlockSizeIndices[i].empty()) {
            auto it = freeBlockSizeIndices[i].begin(); // left most index of size at least blockSize
            if (*it < index) {
                index = *it;
                replacementBlockSize = i;
            }
        }
    }
    if (index == INT_MAX) {
        return -1;
    } else {
        // update free blocks
        freeBlockSizeIndices[replacementBlockSize].erase(index);
        freeBlockSizeIndices[replacementBlockSize-blockSize].insert(index + blockSize);
        return index;
    }
}

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
    cout<<"Memory Before Transformation: "<<endl;
    for (auto & n : memory) {
        cout<<n<<" ";
    }
    cout<<endl;
    vector<set<int>> freeBlockSizeIndices (10, set<int>()); // for each free block space size, map to all their start indices 
    for (int i = 0; i < memorySize; i++) {
        if (memory[i] != -1) {
            continue;
        }
        int blockSize = 0;
        while (i < memorySize && memory[i] == -1) {
            blockSize++;
            i++;
        }
        assert(blockSize <= 9);
        freeBlockSizeIndices[blockSize].insert(i - blockSize);
    }
    for (int i = memorySize - 1; i >= 0; ) {
        if (memory[i] == -1) {
            i--;
            continue;
        }
        int id = memory[i];
        int blockSize = 0;
        while (i >= 0 && memory[i] == id) {
            i--;
            blockSize++;
        }
        int freeBlockIndexStart = getFreeBlockIndexStart(freeBlockSizeIndices, blockSize);
        if (freeBlockIndexStart != -1 && freeBlockIndexStart < i) {
            for (int j = freeBlockIndexStart; j < freeBlockIndexStart + blockSize; j++) {
                memory[j] = id;
            }
            for (int j = i + 1; j <= i + blockSize; j++) {
                memory[j] = -1;
            }
        }

    }
    long long result = 0;
    cout<<"Memory After Transformation: "<<endl;
    for (int i = 0; i < memorySize; i++) {
        cout<<memory[i]<<" ";
        if (memory[i] != -1) {
            result += i * memory[i];
        }
    }
    cout<<endl;
    cout<<result<<endl;

}
