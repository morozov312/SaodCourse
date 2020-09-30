#pragma once
#include "record.hpp"
#include <iostream>
class forwardList {

private:
    struct Node {
        record data;
        Node *next;
    };
    Node *head;
    Node *findLastNode() const {
        Node *ptr_current_node = head;
        if (ptr_current_node == nullptr) {
            return nullptr;
        }
        while (ptr_current_node->next != nullptr) {
            ptr_current_node = ptr_current_node->next;
        }
        return ptr_current_node;
    }

public:
    forwardList() {
        head = nullptr;
    }
    void addNode(record data) {
        Node *tempNode = new Node;
        tempNode->data = data;
        if (head != nullptr) {
            findLastNode()->next = tempNode;
        } else {
            head = tempNode;
        }
    }
    void printList() {
        Node *tempNode = head;
        if (!tempNode) {
            std::cout << "This list is empty!" << std::endl;
        } else {
            do {
                for (int i = 0; i < 20; ++i) {
                    std::cout.width(12);
                    std::cout << tempNode->data.author;
                    std::cout.width(32);
                    std::cout << tempNode->data.title;
                    std::cout.width(16);
                    std::cout << tempNode->data.publishingHouse;
                    std::cout.width(10);
                    std::cout << tempNode->data.year;
                    std::cout.width(10);
                    std::cout << tempNode->data.qtyPages;
                    std::cout << std::endl;
                    tempNode = tempNode->next;
                }
                char key = 0;
                std::cout << "Print next 20 records?(y/n)" << std::endl;
                do {
                    std::cin >> key;
                } while (key != 'y' && key != 'n');
                if(key == 'n'){
                    break;
                }
            } while (tempNode != nullptr);
        }
    }
};
