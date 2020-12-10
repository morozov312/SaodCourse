#pragma once
#include "list.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Encode {
private:
    vector<double> m_probabilities;
    vector<vector<int>> m_matrix;
    vector<char> m_data;
    int calcMedian(int left, int right) {
        long double sumLeft = 0, sumRight = m_probabilities[right];
        unsigned long median;
        for (int i = left; i < right; ++i) {
            sumLeft += m_probabilities[i];
        }
        median = right;
        while (sumLeft >= sumRight) {
            --median;
            sumLeft -= m_probabilities[median];
            sumRight += m_probabilities[median];
        }
        return (int) median;
    }
    void quickSortProbability(int L, int R) {
        int i = L;
        int j = R;
        double temp = m_probabilities[(i + j) / 2];
        while (i <= j) {
            while (m_probabilities[i] > temp) {
                i++;
            }
            while (m_probabilities[j] < temp) {
                j--;
            }
            if (i <= j) {
                swap(m_probabilities[i], m_probabilities[j]);
                swap(m_data[i], m_data[j]);
                i++;
                j--;
            }
        }
        if (L < j) {
            quickSortProbability(L, j);
        }
        if (i < R) {
            quickSortProbability(i, R);
        }
    }
    void calcProbabilities() {
        sort(m_data.begin(), m_data.end());
        auto endPtr = unique(m_data.begin(), m_data.end());
        for (auto i = m_data.begin(); i != endPtr; ++i) {
            int countElements = count(m_data.begin(), m_data.end(), *i);
            m_probabilities.push_back((double) countElements / m_data.size());
        }
        m_data.erase(endPtr, m_data.end());
    }
    void algorithmFano(int left, int right) {
        if (left < right) {
            int median = calcMedian(left, right);
            for (int i = left; i <= right; ++i) {
                if (i <= median)
                    m_matrix[i].push_back(0);
                else
                    m_matrix[i].push_back(1);
            }
            algorithmFano(left, median);
            algorithmFano(median + 1, right);
        }
    }
    void output() {
        double averageLen = 0;
        double entropy = 0;
        for (int i = 0; i < m_matrix.size(); ++i) {
            averageLen += m_matrix[i].size() * m_probabilities[i];
            entropy -= m_probabilities[i] * log2(m_probabilities[i]);
            cout << " " << m_data[i] << "    ";
            cout << setw(5) << to_string(m_probabilities[i]) << "    ";
            cout << m_matrix[i].size() << "    ";
            for (auto &j : m_matrix[i]) {
                cout << j;
            }
            cout << endl;
        }
        cout << "Average code length: " << averageLen << std::endl;
        cout << "Entropy: " << entropy << std::endl;
    };

public:
    explicit Encode(List &list) {
        Node **listIndexArr = list.getIndexArray();
        int listSize = list.getIndexArraySize();
        for (int i = 0; i < listSize; ++i) {
            string tmpStr;
            for (int j = 0; listIndexArr[i]->data.author[j] != '\0'; j++) {
                m_data.push_back(listIndexArr[i]->data.author[j]);
            }
            for (int j = 0; listIndexArr[i]->data.title[j] != '\0'; j++) {
                m_data.push_back(listIndexArr[i]->data.title[j]);
            }
            for (int j = 0; listIndexArr[i]->data.publishingHouse[j] != '\0'; j++) {
                m_data.push_back(listIndexArr[i]->data.publishingHouse[j]);
            }
            tmpStr = to_string(listIndexArr[i]->data.year);
            for (auto &j : tmpStr) {
                m_data.push_back(j);
            }
            tmpStr = to_string(listIndexArr[i]->data.qtyPages);
            for (auto &j : tmpStr) {
                m_data.push_back(j);
            }
        }
    }
    void encodeFano() {
        calcProbabilities();
        m_matrix.resize(m_probabilities.size());
        quickSortProbability(0, (int) m_probabilities.size() - 1);
        algorithmFano(0, (int) m_probabilities.size() - 1);
        output();
    }
};