#include "list.hpp"
#include "record.hpp"
#include <iostream>
using namespace std;

forwardList readFile(char *path) {
    forwardList list;
    FILE *file;
    file = fopen(path, "rb");
    record arrayRecords[4000] = {0};
    fread((record *) arrayRecords, sizeof(record), 4000, file);
    for (auto &i : arrayRecords) {
        cout << i.author <<endl;
        cout << i.title <<endl;
        cout << i.publishingHouse <<endl;
        cout << i.year <<endl;
        cout << i.qtyPages <<endl;
        cout<<endl;
    }
    fclose(file);
    return list;
}
int main() {
    char path[] = "testBase1.dat";
    readFile(path);
    return 0;
}