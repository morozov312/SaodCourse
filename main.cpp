#include "list.hpp"
#include "record.hpp"
#include <fstream>
#include <iostream>
using namespace std;

void ReplaceSpaces(char* str){
    for (int i = 0; str[i] != '\0'; ++i) {
        if(str[i] == ' '){
            str[i]='_';
        }
    }
}
forwardList ReadFile(char *path) {
    forwardList tempList;
    record temp{};
    ifstream file(path, ios::in | ios::binary);
    if (!file) {
        cout << "File open error !!!";
        return tempList;
    }
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(record))) {
        ReplaceSpaces(temp.author);
        ReplaceSpaces(temp.title);
        ReplaceSpaces(temp.publishingHouse);
        tempList.addNode(temp);
        file.seekg(sizeof(record), ios::cur);
    }
    file.close();
    return tempList;
}
int main() {
    char path[] = "testBase1.dat";
    forwardList list = ReadFile(path);
    list.printList();
    return 0;
}