#include "list.hpp"
#include "record.hpp"
#include <fstream>
#include <iostream>
using namespace std;

forwardList readFile(char *path) {
    forwardList tempList;
    record temp{};
    ifstream file(path, ios::in | ios::binary);
    if (!file) {
        cout << "File open error !!!";
    }
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(record))) {
        tempList.addNode(temp);
        file.seekg(sizeof(record), ios::cur);
    }
    file.close();
    return tempList;
}
int main() {
    char path[] = "testBase1.dat";
    forwardList list = readFile(path);
    list.printList();
    return 0;
}