#pragma once
#include "record.hpp"
#include <iostream>
class forwardList {

private:
    struct Node {
        record data{};
        Node *next;
        Node() {
            data = {};
            next = nullptr;
        }
    };
    Node *m_head;

public:
    forwardList() {
        m_head = nullptr;
    }
    ~forwardList() {
        Node *tempHead = m_head;
        if (m_head == nullptr) {
            return;
        }
        do{
            Node* oldHead=tempHead;
            tempHead=tempHead->next;
            delete oldHead;
        } while (tempHead != nullptr);
        m_head= nullptr;
    }
    void addNode(record data) {
        Node *tempNode = new Node;
        tempNode->data = data;
        if (m_head == nullptr) {
            m_head = tempNode;
        } else {
            tempNode->next = m_head;
            m_head = tempNode;
        }
    }
    void printList() {
        Node *tempNode = m_head;
        if (!tempNode) {
            std::cout << "This list is empty!" << std::endl;
        } else {
            do {
                for (int i = 0; i < 20; ++i) {
                    std::cout.width( sizeof(tempNode->data.author));
                    std::cout << tempNode->data.author;
                    std::cout.width( sizeof(tempNode->data.title));
                    std::cout << tempNode->data.title;
                    std::cout.width( sizeof(tempNode->data.publishingHouse));
                    std::cout << tempNode->data.publishingHouse;
                    std::cout.width(8);
                    std::cout << tempNode->data.year;
                    std::cout.width(8);
                    std::cout << tempNode->data.qtyPages;
                    std::cout << std::endl;
                    tempNode = tempNode->next;
                }
                char key = 0;
                std::cout << "Print next 20 records?(y/n)" << std::endl;
                do {
                    std::cin >> key;
                } while (key != 'y' && key != 'n');
                if (key == 'n') {
                    break;
                }
            } while (tempNode != nullptr);
        }
    }
};
