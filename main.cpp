#include "list.hpp"
#include "record.hpp"
#include <iostream>
#include <cstdio>
using namespace std;

forwardList readFile(char *path) {
    forwardList tempList;
    FILE *file;
    file = fopen(path, "rb");
    record temp{};
    for (int i = 0; i < 4000; ++i) {
        fread(&temp,sizeof(record),1,file);
        tempList.addNode(temp);
        fseek(file,sizeof(record),1);
    }
    fclose(file);
    return tempList;
}
int main() {
    char path[] = "testBase1.dat";
    forwardList list = readFile(path);
    list.printList();
    return 0;
}