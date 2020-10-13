#include "list.hpp"
#include "tools.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

List ReadFile(const char *path);
int Menu(const char *path);
List CreateQueue(List list);

int main() {
    const char dataBasePath[] = "testBase1.dat";
    while (true) {
        int res = Menu(dataBasePath);
        if (!res)
            break;
    }
    return 0;
}

int Menu(const char *path) {
    int key;
    cout << "Выберите пнукт меню:" << endl;
    cout << "0 - Выход" << endl;
    cout << "1 - Показать информацию из БД:" << endl;
    cout << "2 - Сортировка слиянием по полям 1-издательство 2-автор:" << endl;
    cout << "3 - Быстрый посик по первым трем буквам издательства:" << endl;
    cout << "4 - Построить дерево оптимального поиска А1:" << endl;
    cout << "5 - Закодировать БД кодом Фано:" << endl;
    cin >> key;
    if (!CheckCin()) {
        key = -1;
    }
    switch (key) {
        case 0: {
            cout << "Выход";
            return 0;
        }
        case 1: {
            List list = ReadFile(path);
            list.printList();
            break;
        }
        case 2: {
            List list = ReadFile(path);
            list.mergeSort();
            list.printList();
            break;
        }
        case 3: {
            List list = ReadFile(path);
            list.mergeSort();
            List queue;
            list.createIndexArray();
            queue = CreateQueue(list);
            queue.printList();
            break;
        }
        default: {
            cout << "Такого пункта нет" << endl;
            break;
        }
    }
    return 1;
}
List CreateQueue(List list) {
    Node **arr = list.getIndexArray();
    const char searchKey[] = "Пат";
    List queue;
    int res = list.binarySearch(searchKey);
    if (res != -1) {
        queue.addNode(arr[res]->data);
        do {
            res++;
            if (strncmp(arr[res]->data.publishingHouse, searchKey, strlen(searchKey)) == 0) {
                queue.addNode(arr[res]->data);
            } else {
                break;
            }
        } while (true);
    }
    return queue;
}
List ReadFile(const char *path) {
    List tempList;
    record temp{};
    ifstream file(path, ios::in | ios::binary);
    if (!file) {
        cout << "File open error !!!";
        return tempList;
    }
    while (file.read((char *) (&temp), sizeof(record))) {
        tempList.addNode(temp);
    }
    file.close();
    return tempList;
}