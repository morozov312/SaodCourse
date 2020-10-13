#pragma once
#include "record.hpp"
#include "tools.hpp"
#include <cstring>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class List {

private:
    // members
    Node *m_head, *m_tail;
    int m_listSize = 0;
    Node **m_indexArray;
    int m_pageSize = 20;
    bool m_sorted = false;
    // methods
    // for print
    static char choosePage(char key) {
        cout << "Показать следующие 20 записей?(y) Предыдущие 20?(p) Выбрать страницу по номеру?(n) Выход(e)" << endl;
        bool errorFlag = false;
        do {
            if (errorFlag) {
                cout << "Такого варианта нет,Попробуйте еще раз!" << endl;
            }
            cin >> key;
            errorFlag = true;
        } while (key != 'y' && key != 'e' && key != 'p' && key != 'n');
        switch (key) {
            case 'e':
                return 'e';
            case 'y': {
                return 'y';
            }
            case 'p': {
                return 'p';
            }
            case 'n': {
                return 'n';
            }
            default:
                return -1;
        }
    }
    int printPage(int currIndex) {
        const unsigned int numbersOutWidth = 6;
        cout << endl;
        for (int i = 0; i < m_pageSize; ++i, currIndex++) {
            int displayIndex = currIndex + 1;
            try {
                if (currIndex >= m_listSize)
                    throw std::range_error("Out of range");
            } catch (std::range_error &e) {
                break;
            }
            cout.width(numbersOutWidth);
            cout << displayIndex;
            cout.width(sizeof(m_head->data.author));
            cout << (m_indexArray[currIndex]->data).author;
            cout.width(sizeof(m_head->data.title));
            cout << (m_indexArray[currIndex]->data).title;
            cout.width(sizeof(m_head->data.publishingHouse));
            cout << (m_indexArray[currIndex]->data).publishingHouse;
            cout.width(numbersOutWidth);
            cout << (m_indexArray[currIndex]->data).year;
            cout.width(numbersOutWidth);
            cout << (m_indexArray[currIndex]->data).qtyPages;
            cout << endl;
        }
        return currIndex;
    }
    int printPageByNum(int currIndex) {
        cout << "Введите номер страницы: ";
        int pageNumber;
        cin >> pageNumber;
        CheckCin();
        if (pageNumber <= 0 || pageNumber > m_listSize / m_pageSize) {
            cout << "Невозможно прочитать страницу с таким номером!" << endl;
            return currIndex;
        } else {
            currIndex = (pageNumber - 1) * m_pageSize;
            currIndex = printPage(currIndex);
        }
        return currIndex;
    }
    // for sort
    static void merge(Node *low, Node *high, Node **tempHead) {
        Node tmp;
        *tempHead = nullptr;
        if (low == nullptr) {
            *tempHead = high;
            return;
        }
        if (high == nullptr) {
            *tempHead = low;
            return;
        }
        if (strcmp(low->data.publishingHouse, high->data.publishingHouse) < 0) {
            *tempHead = low;
            low = low->next;
        } else if (strcmp(low->data.publishingHouse, high->data.publishingHouse) == 0) {
            if (strcmp(low->data.author, high->data.author) < 0) {
                *tempHead = low;
                low = low->next;
            } else {
                *tempHead = high;
                high = high->next;
            }
        } else {
            *tempHead = high;
            high = high->next;
        }
        tmp.next = *tempHead;
        while (low && high) {
            if (strcmp(low->data.publishingHouse, high->data.publishingHouse) < 0) {
                (*tempHead)->next = low;
                low = low->next;
            } else if (strcmp(low->data.publishingHouse, high->data.publishingHouse) == 0) {
                if (strcmp(low->data.author, high->data.author) < 0) {
                    (*tempHead)->next = low;
                    low = low->next;
                } else {
                    (*tempHead)->next = high;
                    high = high->next;
                }
            } else {
                (*tempHead)->next = high;
                high = high->next;
            }
            (*tempHead) = (*tempHead)->next;
        }
        if (low) {
            while (low) {
                (*tempHead)->next = low;
                (*tempHead) = (*tempHead)->next;
                low = low->next;
            }
        }
        if (high) {
            while (high) {
                (*tempHead)->next = high;
                (*tempHead) = (*tempHead)->next;
                high = high->next;
            }
        }
        *tempHead = tmp.next;
    }
    static void split(Node **low, Node **high, Node *tempHead) {
        Node *fast;
        Node *slow;
        if (tempHead == nullptr || tempHead->next == nullptr) {
            (*low) = tempHead;
            (*high) = nullptr;
            return;
        }
        slow = tempHead;
        fast = tempHead->next;
        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                fast = fast->next;
                slow = slow->next;
            }
        }
        (*low) = tempHead;
        (*high) = slow->next;
        slow->next = nullptr;
    }

public:
    List() {
        m_head = nullptr;
        m_tail = nullptr;
        m_indexArray = nullptr;
    }
    Node **getIndexArray() {
        return this->m_indexArray;
    }
    bool isSorted() const {
        if (!this->m_sorted) {
            return false;
        }
        return true;
    }
    void addNode(record data) {
        m_listSize++;
        Node *tempNode = new Node;
        tempNode->data = data;
        if (m_head != nullptr) {
            m_tail->next = tempNode;
            m_tail = tempNode;
        } else {
            m_head = m_tail = tempNode;
        }
    }
    void createIndexArray() {
        m_indexArray = new Node *[m_listSize];
        Node *tempNode = m_head;
        for (int i = 0; i < m_listSize; ++i) {
            if (!tempNode) {
                return;
            }
            m_indexArray[i] = tempNode;
            tempNode = tempNode->next;
        }
    }
    void printList() {
        this->createIndexArray();
        if (m_listSize == 0) {
            cout << "Список пуст!" << endl;
            return;
        }
        char key;
        int currIndex = 0;
        currIndex = printPage(currIndex);
        while (currIndex != m_listSize) {
            key = choosePage(key);
            if (key == 'y') {
                currIndex = printPage(currIndex);
            } else if (key == 'p') {
                currIndex -= m_pageSize * 2;
                if (currIndex < 0) {
                    cout << "Выход за пределы БД!" << endl;
                    currIndex = 0;
                }
                currIndex = printPage(currIndex);
            } else if (key == 'n') {
                currIndex = printPageByNum(currIndex);
            } else if (key == 'e') {
                return;
            }
        }
    }
    void mergeSort(Node **head = nullptr) {
        this->m_sorted = true;
        if (!head) {
            head = &this->m_head;
        }
        Node *low = nullptr;
        Node *high = nullptr;
        if ((*head == nullptr) || ((*head)->next == nullptr)) {
            return;
        }
        split(&low, &high, *head);
        mergeSort(&low);
        mergeSort(&high);
        merge(low, high, head);
    }
    int binarySearch(const char key[]) {
        if (!this->isSorted()) {
            cout << "Массив не отсортирован!" << endl;
            return -1;
        }
        Node **arr = m_indexArray;
        const int keySize = strlen(key);
        int mid, left = 0, right = m_listSize;
        while (left < right) {
            mid = (left + right) / 2;
            if (strncmp(arr[mid]->data.publishingHouse, key, keySize) < 0) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        if (strncmp(arr[right]->data.publishingHouse, key, keySize) == 0) {
            return right;
        } else {
            return -1;
        }
    }
};