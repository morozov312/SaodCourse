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
    const int m_pageSize = 1000;
    // methods
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
        const unsigned int numbersOutWidth = 8;
        for (int i = 0; i < m_pageSize; ++i, currIndex++) {
            int displayIndex = currIndex + 1;
            try {
                if (currIndex >= m_listSize)
                    throw std::range_error("Out of range");
            } catch (std::range_error &e) {
                break;
            }
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

public:
    List() {
        m_head = nullptr;
        m_tail = nullptr;
        m_indexArray = nullptr;
    }
    Node *getHead() {
        return this->m_head;
    }
    void setHead(Node *newHead) {
        this->m_head = newHead;
    }
    int getSize() const {
        return this->m_listSize;
    }
    Node **getIndexArray() {
        return this->m_indexArray;
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
            m_indexArray[i] = tempNode;
            tempNode = tempNode->next;
        }
    }
    void printList() {
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
    ~List() {
        // list
        Node *tempHead = m_head;
        if (m_head == nullptr) {
            return;
        }
        do {
            Node *oldHead = tempHead;
            tempHead = tempHead->next;
            delete oldHead;
        } while (tempHead != nullptr);
        m_head = nullptr;
        delete m_head;
        // array
        delete[] m_indexArray;
    }
};