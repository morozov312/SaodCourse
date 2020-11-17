#pragma once

#include "list.hpp"
#include "record.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Tree {

private:
    struct Vertex {
        int data = 0;
        Vertex *ptrRight = nullptr;
        Vertex *ptrLeft = nullptr;
    };
    // members
    Node **m_queueIndexArray = nullptr;
    int m_queueIndexArraySize = 0;
    vector<record> m_uniqueRecords;
    vector<int> m_weightArray;
    // methods
    static void addDoubleIndirection(int key, Vertex **root) {
        Vertex **head_ptr = root;
        while (*head_ptr) {
            if (key < (*head_ptr)->data) {
                head_ptr = &((*head_ptr)->ptrLeft);
            } else if (key > (*head_ptr)->data) {
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

public:
    Tree(Node **indexArr, int size) {
        this->m_queueIndexArray = indexArr;
        this->m_queueIndexArraySize = size;
    }
    static void swap(Node **first, Node **second) {
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
                swap(&m_queueIndexArray[i], &m_queueIndexArray[j]);
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
    void createWeightArray() {
        quickSort(0, m_queueIndexArraySize - 1);
        int currWeight = 0;
        for (int i = 0; i < m_queueIndexArraySize - 1; ++i) {
            if (currWeight == 0) {
                m_uniqueRecords.push_back((*m_queueIndexArray[i]).data);
                currWeight++;
            } else {
                if ((*m_queueIndexArray[i]).data.year != (*m_queueIndexArray[i + 1]).data.year) {
                    currWeight++;
                    m_weightArray.push_back(currWeight);
                    currWeight = 0;
                } else {
                    currWeight++;
                }
            }
        }
        if (currWeight == 0) {
            m_uniqueRecords.push_back((*m_queueIndexArray[m_queueIndexArraySize - 1]).data);
            m_weightArray.push_back(1);
        } else {
            currWeight++;
            m_weightArray.push_back(currWeight);
        }
    }
    //    void QuickSortRev(int L, int R) {
    //        int i = L;
    //        int j = R;
    //        int temp = weights_array[(i + j) / 2];
    //        while (i <= j) {
    //            while (weights_array[i] > temp) {
    //                i++;
    //            }
    //            while (weights_array[j] < temp) {
    //                j--;
    //            }
    //            if (i <= j) {
    //                swap(weights_array[i], weights_array[j]);
    //                swap(m_array[i], m_array[j]);
    //                i++;
    //                j--;
    //            }
    //        }
    //        if (L < j) {
    //            QuickSortRev(L, j);
    //        }
    //        if (i < R) {
    //            QuickSortRev(i, R);
    //        }
    //    }
    //    void buildTreeA1(Vertex **root) {
    //        QuickSortRev(0, (int) m_array.size() - 1);
    //        for (int &i : m_array) {
    //            addDoubleIndirection(i, root);
    //        }
    //    }
    void printLeftToRight(Vertex *root) {
        if (root != nullptr) {
            printLeftToRight(root->ptrLeft);
            cout << root->data << " ";
            printLeftToRight(root->ptrRight);
        }
    }
};