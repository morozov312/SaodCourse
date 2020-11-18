#pragma once

#include "list.hpp"
#include "record.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Tree {

private:
    // members
    Node **m_queueIndexArray = nullptr;
    int m_queueIndexArraySize = 0;
    vector<record> m_uniqueRecords;
    vector<int> m_weightArray;
    Vertex *m_root = nullptr;
    // methods
    static void addDoubleIndirection(record key, Vertex **root) {
        Vertex **head_ptr = root;
        while (*head_ptr) {
            if (key.year < (*head_ptr)->data.year) {
                head_ptr = &((*head_ptr)->ptrLeft);
            } else if (key.year > (*head_ptr)->data.year) {
                head_ptr = &((*head_ptr)->ptrRight);
            } else {
                cout << "Element is already in the array" << endl;
                break;
            }
        }
        if (*head_ptr == nullptr) {
            *head_ptr = new Vertex;
            (*head_ptr)->data = key;
        }
    }
    static void swapNodes(Node **first, Node **second) {
        Node *temp = *first;
        *first = *second;
        *second = temp;
    }
    void quickSort(int L, int R) {
        int i = L;
        int j = R;
        Node temp = *m_queueIndexArray[(i + j) / 2];
        while (i <= j) {
            while ((*m_queueIndexArray[i]).data.year < temp.data.year) {
                i++;
            }
            while ((*m_queueIndexArray[j]).data.year > temp.data.year) {
                j--;
            }
            if (i <= j) {
                swapNodes(&m_queueIndexArray[i], &m_queueIndexArray[j]);
                i++;
                j--;
            }
        }
        if (L < j) {
            quickSort(L, j);
        }
        if (i < R) {
            quickSort(i, R);
        }
    }
    void reverseQuickSort(int L, int R) {
        int i = L;
        int j = R;
        int temp = m_weightArray[(i + j) / 2];
        while (i <= j) {
            while (m_weightArray[i] > temp) {
                i++;
            }
            while (m_weightArray[j] < temp) {
                j--;
            }
            if (i <= j) {
                swap(m_weightArray[i], m_weightArray[j]);
                swap(m_uniqueRecords[i], m_uniqueRecords[j]);
                i++;
                j--;
            }
        }
        if (L < j) {
            reverseQuickSort(L, j);
        }
        if (i < R) {
            reverseQuickSort(i, R);
        }
    }
    void createWeightArray() {
        quickSort(0, m_queueIndexArraySize - 1);
        int currWeight = 1;
        for (int i = 0; i < m_queueIndexArraySize; ++i) {
            cout.width(6);
            cout << m_queueIndexArray[i]->data.year << " ";
        }
        cout << endl;
        for (int i = 0; i < m_queueIndexArraySize; ++i) {
            if ((i != m_queueIndexArraySize - 1) && (m_queueIndexArray[i]->data.year == m_queueIndexArray[i + 1]->data.year)) {
                currWeight++;
                int j = i + 1;
                while ((j != m_queueIndexArraySize - 1) && (m_queueIndexArray[j]->data.year == m_queueIndexArray[j + 1]->data.year)) {
                    currWeight++;
                    j++;
                }
            }
            m_uniqueRecords.push_back(m_queueIndexArray[i]->data);
            m_weightArray.push_back(currWeight);
            i += currWeight - 1;
            currWeight = 1;
        }
        for (auto &i : m_uniqueRecords) {
            cout.width(6);
            cout << i.year << " ";
        }
        cout << endl;
        for (auto &i : m_weightArray) {
            cout.width(6);
            cout << i << " ";
        }
        cout << endl;
        int res = 0;
        for (auto &i : m_weightArray) {
            res += i;
        }
        cout << res << endl;
    }

public:
    Tree(Node **indexArr, int size) {
        this->m_queueIndexArray = indexArr;
        this->m_queueIndexArraySize = size;
    }
    Vertex *getRoot() {
        return m_root;
    };
    void buildTreeA1() {
        createWeightArray();
        reverseQuickSort(0, (int) m_uniqueRecords.size() - 1);
        for (auto &i : m_uniqueRecords) {
            addDoubleIndirection(i, &m_root);
        }
    }
    void printLeftToRight(Vertex *root) {
        if (root != nullptr) {
            printLeftToRight(root->ptrLeft);
            cout.width(sizeof(root->data.author));
            cout << (root->data).author;
            cout.width(sizeof(root->data.title));
            cout << (root->data).title;
            cout.width(sizeof(root->data.publishingHouse));
            cout << (root->data).publishingHouse;
            cout.width(numbersOutWidth);
            cout << (root->data).year;
            cout.width(numbersOutWidth);
            cout << (root->data).qtyPages;
            cout << endl;
            printLeftToRight(root->ptrRight);
        }
    }
};