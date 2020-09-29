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
            std::cout << "forward list is empty!" << std::endl;
        } else {
            do {
                std::cout << tempNode->data.author << std::endl;
                std::cout << tempNode->data.title << std::endl;
                std::cout << tempNode->data.publishingHouse << std::endl;
                std::cout << tempNode->data.year << std::endl;
                std::cout << tempNode->data.qtyPages << std::endl;
                std::cout << std::endl;
                tempNode = tempNode->next;
            } while (tempNode != nullptr);
        }
    }
};
