#pragma once
#include "record.hpp"
#include "tools.hpp"
#include <cstring>
#include <iostream>


using std::cin;
using std::cout;
using std::endl;

const unsigned int numbersOutWidth = 6;


class List {
private:
    // members
    Node *m_head, *m_tail;
    int m_listSize = 0, m_pageSize = 20, m_foundIndex = 0;
    Node **m_indexArray = nullptr;
    bool m_sorted = false;
    // methods
    // for print
    static char choosePage() {
        char key;
        std::string tempStr;
        cout << "Show next page? (y) Previous? (p) Select page by number? (n) Exit (e)" << endl;
        bool errorFlag = false;
        do {
            if (errorFlag) {
                cout << "\x1b[31m There is no such option, try again! \x1b[0m" << endl;
            }
            cin >> tempStr;
            if (tempStr.length() > 1) tempStr = "";
            errorFlag = true;
        } while (tempStr[0] != 'y' && tempStr[0] != 'e' && tempStr[0] != 'p' && tempStr[0] != 'n' &&
                 tempStr[0] != 'Y' && tempStr[0] != 'E' && tempStr[0] != 'P' && tempStr[0] != 'N');
        key = tempStr[0];
        switch (key) {
            case 'e':
            case 'E':
                return 'e';
            case 'y':
            case 'Y':
                return 'y';
            case 'p':
            case 'P':
                return 'p';
            case 'n':
            case 'N':
                return 'n';
            default:
                return -1;
        }
    }
    int printPage(int currIndex) {
        for (int i = 0; i < m_pageSize; ++i, currIndex++) {
            int displayIndex = currIndex + 1 + this->m_foundIndex;
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
        cout << "Enter page number: ";
        int pageNumber;
        cin >> pageNumber;
        CheckCin();
        if (pageNumber <= 0 || pageNumber > m_listSize / m_pageSize) {
            cout << "It is impossible to read a page with that number!" << endl;
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
    struct ListQueue {
        Node *head = nullptr;
        Node *tail = nullptr;
    };

public:
    List() {
        m_head = nullptr;
        m_tail = nullptr;
    }
    Node **getIndexArray() {
        return this->m_indexArray;
    }
    int getIndexArraySize() const {
        return this->m_listSize;
    }
    void setFoundIndex(int index) {
        this->m_foundIndex = index;
    }
    bool isEmpty() const {
        if (this->m_listSize == 0) {
            return true;
        }
        return false;
    }
    bool isSorted() const {
        return this->m_sorted;
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
        delete[] m_indexArray;
        this->m_indexArray = new Node *[m_listSize];
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
            cout << "List is Empty!" << endl;
            return;
        }
        char key;
        int currIndex = 0;
        currIndex = printPage(currIndex);
        while (currIndex != m_listSize) {
            key = choosePage();
            if (key == 'y') {
                currIndex = printPage(currIndex);
            } else if (key == 'p') {
                currIndex -= m_pageSize * 2;
                if (currIndex < 0) {
                    cout << "\x1b[31m Out of range database! \x1b[0m" << endl;
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
    int binarySearch(char *key) {
        if (!this->m_sorted) {
            cout << "List doesn't sorted" << endl;
            return -1;
        }
        Node **arr = m_indexArray;
        const int keySize = 3;
        int mid, left = 0, right = m_listSize - 1;
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
    void DigitalSort() {
        int KDI[60];
        Node *tempList;
        ListQueue queueArr[256];
        for (int i = 12; i < 60; ++i) {
            KDI[i] = i;
        }
        for (int j = 59; j >= 12; j--) {
            for (auto &i : queueArr) {
                i.tail = (Node *) &i.head;
            }
            tempList = m_head;
            int tempKDI = KDI[j];
            while (tempList != nullptr) {
                int tempDigit = tempList->Digit[tempKDI];
                queueArr[tempDigit].tail->next = tempList;
                queueArr[tempDigit].tail = tempList;
                tempList = tempList->next;
            }
            tempList = (Node *) &m_head;
            for (auto &i : queueArr) {
                if (i.tail != (Node *) &i.head) {
                    tempList->next = i.head;
                    tempList = i.tail;
                }
            }
            tempList->next = nullptr;
        }
    }
    ~List() {
        if (m_indexArray) {
            for (size_t i = 0; i < m_listSize; i++) {
                delete m_indexArray[i];
            }
        }
        delete[] m_indexArray;
    }
};