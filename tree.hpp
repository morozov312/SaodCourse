#pragma once
#include "list.hpp"
#include "record.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    vector<record> data;
    Vertex *ptrRight = nullptr;
    Vertex *ptrLeft = nullptr;
    int weight = 0;
};
class Tree {

private:
    // members
    Node **m_queueIndexArray = nullptr;
    int m_queueIndexArraySize = 0;
    vector<int> m_weightArray;
    vector<vector<record>> m_vectorArray;
    Vertex *m_root = nullptr;
    // methods
    void addDoubleIndirection(vector<record> key, Vertex **root, int weightPos) {
        Vertex **head_ptr = root;
        while (*head_ptr) {
            if (key[0].year < (*head_ptr)->data[0].year) {
                head_ptr = &((*head_ptr)->ptrLeft);
            } else if (key[0].year > (*head_ptr)->data[0].year) {
                head_ptr = &((*head_ptr)->ptrRight);
            } else {
                cout << "Element is already in the array" << endl;
                break;
            }
        }
        if (*head_ptr == nullptr) {
            *head_ptr = new Vertex;
            (*head_ptr)->data = key;
            (*head_ptr)->weight = m_weightArray[weightPos];
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
                swap(m_vectorArray[i], m_vectorArray[j]);
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
            if ((i != m_queueIndexArraySize - 1) && (m_queueIndexArray[i]->data.year == m_queueIndexArray[i + 1]->data.year)) {
                currWeight++;
                int j = i + 1;
                while ((j != m_queueIndexArraySize - 1) && (m_queueIndexArray[j]->data.year == m_queueIndexArray[j + 1]->data.year)) {
                    currWeight++;
                    j++;
                }
            }
            m_weightArray.push_back(currWeight);
            i += currWeight - 1;
            currWeight = 1;
        }
    }
    void createVectorArray() {
        int pos = 0;
        for (auto &i : m_weightArray) {
            vector<record> tempVector;
            for (int j = 0; j < i; ++j, ++pos) {
                tempVector.push_back(m_queueIndexArray[pos]->data);
            }
            m_vectorArray.push_back(tempVector);
        }
    }
    void destroyRecursive(Vertex **root) {
        if (*root) {
            destroyRecursive(&((*root)->ptrLeft));
            destroyRecursive(&((*root)->ptrRight));
            delete *root;
        }
    }

public:
    void setIndexArray(Node **indexArr, int size) {
        this->m_queueIndexArray = indexArr;
        this->m_queueIndexArraySize = size;
    }
    Vertex *getRoot() {
        return m_root;
    }
    bool isEmpty() {
        if (m_root) {
            return false;
        }
        return true;
    }
    vector<record> search(int key, Vertex *root) {
        vector<record> tempVector;
        if (!root) return tempVector;
        if (key < root->data[0].year)
            return search(key, root->ptrLeft);
        else if (key > root->data[0].year)
            return search(key, root->ptrRight);
        return root->data;
    }
    void buildTreeA1() {
        createWeightArray();
        createVectorArray();
        reverseQuickSort(0, (int) m_vectorArray.size() - 1);
        int weightPos = 0;
        for (auto &i : m_vectorArray) {
            addDoubleIndirection(i, &m_root, weightPos);
            weightPos++;
        }
    }
    void printLeftToRight(Vertex *root) {
        if (root != nullptr) {
            printLeftToRight(root->ptrLeft);
            cout.width(4);
            cout << root->weight << endl;
            for (auto &i : root->data) {
                cout << "    ";
                cout.width(sizeof(i.author));
                cout << i.author;
                cout.width(sizeof(i.title));
                cout << i.title;
                cout.width(sizeof(i.publishingHouse));
                cout << i.publishingHouse;
                cout.width(sizeof(numbersOutWidth));
                cout << i.year;
                cout.width(sizeof(numbersOutWidth));
                cout << i.qtyPages << endl;
            }
            printLeftToRight(root->ptrRight);
        }
    }
    ~Tree() {
        destroyRecursive(&m_root);
    }
};