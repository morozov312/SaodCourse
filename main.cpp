#include "list.hpp"
#include "tools.hpp"
#include "tree.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

List ReadFile(const char *path);
int Menu(const char *path, List &list, List &queue);
void CreateQueue(List &list, List &queue);

int main() {
    const char dataBasePath[] = "testBase1.dat";
    List list, searchQueue;
    while (true) {
        int res = Menu(dataBasePath, list, searchQueue);
        if (!res) break;
    }
    return 0;
}

int Menu(const char *path, List &list, List &queue) {
    int key;
    cout << "Выберите пнукт меню:" << endl;
    cout << "0 - Выход" << endl;
    cout << "1 - Загрузить БД в динамическую память" << endl;
    cout << "2 - Вывод текущего состояния БД" << endl;
    cout << "3 - Сортировка слиянием по полям 1-издательство 2-автор:" << endl;
    cout << "4 - Быстрый посик по первым трем буквам издательства:" << endl;
    cout << "5 - Построить дерево оптимального поиска А1:" << endl;
    cout << "6 - Закодировать БД кодом Фано:" << endl;
    cin >> key;
    if (!CheckCin()) {
        cout << "Некорректный выбор пункта меню!" << endl;
        return -1;
    }
    switch (key) {
        case 0: {
            cout << "Выход";
            return 0;
        }
        case 1: {
            list = ReadFile(path);
            cout << "База данных была загружена в динамическую память" << endl;
            break;
        }
        case 2: {
            list.printList();
            break;
        }
        case 3: {
            list.mergeSort();
            cout << "Список успешно отсортирован!" << endl;
            break;
        }
        case 4: {
            list.createIndexArray();
            CreateQueue(list, queue);
            if (queue.isEmpty())
                cout << "По данному ключу поиска записей не найдено!" << endl;
            else
                queue.printList();
            break;
        }
        case 5: {
            if (queue.isEmpty()) {
                break;
            } else {
                Tree DOPA1(queue.getIndexArray(), queue.getIndexArraySize());
                DOPA1.buildTreeA1();
                Vertex *root = DOPA1.getRoot();
                DOPA1.printLeftToRight(root);
                cout << endl;
            }
            break;
        }
        case 6: {
            cout << "Кодировка еще не готова" << endl;
            // todo Fano code
            break;
        }
        default: {
            cout << "Такого пункта нет" << endl;
            break;
        }
    }
    return 1;
}
void CreateQueue(List &list, List &queue) {
    Node **arr = list.getIndexArray();
    char searchKey[3];
    int tryCounter = 0;
    cout << "Введите первые три буквы издательства для поиска: ";
    while (true) {
        cin >> searchKey;
        if (tryCounter != 0) {
            cout << "Ошибка ввода! Попробуйте еще раз" << endl;
        }
        tryCounter++;
        if (CheckCin()) break;
    }
    int res = list.binarySearch(searchKey);
    queue.setFoundIndex(res);
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