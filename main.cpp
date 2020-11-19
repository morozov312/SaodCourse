#include "list.hpp"
#include "tools.hpp"
#include "tree.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

List ReadFile(const char *path);
int Menu(const char *path, List &list, List &queue, Tree &DOPA1);
void CreateQueue(List &list, List &queue);

int main() {
    const char dataBasePath[] = "testBase1.dat";
    List list, searchQueue;
    Tree DOPA1;
    while (true) {
        int res = Menu(dataBasePath, list, searchQueue, DOPA1);
        if (!res) break;
    }
    return 0;
}

int Menu(const char *path, List &list, List &queue, Tree &DOPA1) {
    int key;
    cout << "Выберите пнукт меню:" << endl;
    cout << "0 - Выход" << endl;
    cout << "1 - Загрузить БД в динамическую память" << endl;
    cout << "2 - Вывод текущего состояния БД" << endl;
    cout << "3 - Сортировка слиянием по полям 1-издательство 2-автор" << endl;
    cout << "4 - Быстрый посик по первым трем буквам издательства" << endl;
    cout << "5 - Вывод очереди по результатам поиска" << endl;
    cout << "6 - Построить дерево оптимального поиска А1" << endl;
    cout << "7 - Вывод дерева(с лева на право)" << endl;
    cout << "8 - Поиск в дереве" << endl;
    cout << "9 - Закодировать БД кодом Фано:" << endl;
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
            if (queue.isEmpty()) {
                cout << "По данному ключу поиска записей не найдено!" << endl;
            } else {
                queue.createIndexArray();
                cout << "Очередь успешно построена!" << endl;
            }
            break;
        }
        case 5: {
            if (queue.isEmpty())
                cout << "Очередь еще не построена!" << endl;
            else
                queue.printList();
            break;
        }
        case 6: {
            if (queue.isEmpty()) {
                cout << "Очередь для построения еще не готова!" << endl;
            } else {
                DOPA1.setIndexArray(queue.getIndexArray(), queue.getIndexArraySize());
                DOPA1.buildTreeA1();
                cout << "Дерево успешно построено!" << endl;
            }
            break;
        }
        case 7: {
            if (DOPA1.isEmpty())
                cout << "Дерево не было построено!" << endl;
            else {
                Vertex *root = DOPA1.getRoot();
                DOPA1.printLeftToRight(root);
            }
            break;
        }
        case 8: {
            if (DOPA1.isEmpty()) {
                cout << "Дерево не было построено!" << endl;
            } else {
                Vertex *root = DOPA1.getRoot();
                int searchKey;
                cout << "Введите год для поиска записей: ";
                cin >> searchKey;
                if (!CheckCin()) {
                    cout << "Некорректный ввод поля поиска" << endl;
                    break;
                }
                List result = DOPA1.search(searchKey, root);
                if (result.isEmpty())
                    cout << "Записей с таким годом в очереди не найдено!" << endl;
                else
                    result.printList();
            }
            break;
        }
        case 9: {
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
char charToUppercase(char symbol) {
    if ((int) symbol > -96 && (int) symbol < -64)
        return (char) (symbol - 32);
    return symbol;
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
    searchKey[0] = charToUppercase(searchKey[0]);
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
