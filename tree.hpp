#pragma once
#include "list.hpp"
#include "record.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    List data{};
    Vertex *ptrRight = nullptr;
    Vertex *ptrLeft = nullptr;
    int weight = 0;
};
class Tree {

private:
    // members
    Node **m_queueIndexArray = nullptr;
    int m_queueIndexArraySize = 0;
    vector<record> m_uniqueRecords;
    vector<int> m_weightArray;
    vector<List> m_ListArray;
    Vertex *m_root = nullptr;
    // methods
    void addDoubleIndirection(List key, Vertex **root, int weightPos) {
        Vertex **head_ptr = root;
        while (*head_ptr) {
            if (key.begin().year < (*head_ptr)->data.begin().year) {
                head_ptr = &((*head_ptr)->ptrLeft);
            } else if (key.begin().year > (*head_ptr)->data.begin().year) {
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
                swap(m_ListArray[i], m_ListArray[j]);
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
            m_uniqueRecords.push_back(m_queueIndexArray[i]->data);
            m_weightArray.push_back(currWeight);
            i += currWeight - 1;
            currWeight = 1;
        }
    }
    void createListArray() {
        int pos = 0;
        for (auto &i : m_weightArray) {
            List tempList{};
            for (int j = 0; j < i; ++j, ++pos) {
                tempList.addNode(m_queueIndexArray[pos]->data);
            }
            m_ListArray.push_back(tempList);
        }
    }
    void destroyRecursive(Vertex **leaf) {
        if ((*leaf)) {
            destroyRecursive(&((*leaf)->ptrLeft));
            destroyRecursive(&((*leaf)->ptrRight));
            delete (*leaf);
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
    List search(int key, Vertex *root) {
        List tempList;
        if (!root) return tempList;
        if (key < root->data.begin().year)
            return search(key, root->ptrLeft);
        else if (key > root->data.begin().year)
            return search(key, root->ptrRight);
        return root->data;
    }
    void buildTreeA1() {
        createWeightArray();
        createListArray();
        reverseQuickSort(0, (int) m_ListArray.size() - 1);
        int weightPos = 0;
        for (auto &i : m_ListArray) {
            addDoubleIndirection(i, &m_root, weightPos);
            weightPos++;
        }
    }
    void printLeftToRight(Vertex *root) {
        if (root != nullptr) {
            printLeftToRight(root->ptrLeft);
            cout.width(4);
            cout << root->weight << endl;
            root->data.printList();
            printLeftToRight(root->ptrRight);
        }
    }
    ~Tree() {
        destroyRecursive(&m_root);
    }
};