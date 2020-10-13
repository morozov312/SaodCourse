#pragma once
#include "record.hpp"
#include <cstring>
#include <iostream>
#define KEY_SIZE 3
void Merge(Node *low, Node *high, Node **tempHead) {
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
void Split(Node **low, Node **high, Node *tempHead) {
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
void MergeSort(Node **head) {
    Node *low = nullptr;
    Node *high = nullptr;
    if ((*head == nullptr) || ((*head)->next == nullptr)) {
        return;
    }
    Split(&low, &high, *head);
    MergeSort(&low);
    MergeSort(&high);
    Merge(low, high, head);
}
bool CheckCin() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        return true;
    }
    return false;
}
int BinarySearch(Node **arr, int l, int r, const char key[]) {
    int mid, left = l, right = r;
    char buffer[KEY_SIZE + 1];
    while (left < right) {
        mid = (left + right) / 2;
        strncpy(buffer, (arr[mid]->data).publishingHouse, KEY_SIZE);
        buffer[KEY_SIZE] = '\0';
        if (strcmp(buffer, key) < 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    strncpy(buffer, (arr[right]->data).publishingHouse, KEY_SIZE);
    buffer[KEY_SIZE] = '\0';
    if (strcmp(buffer, key) == 0) {
        return right;
    } else {
        return -1;
    }
}