#pragma once
#include <cstring>
struct record {
    char author[12];
    char title[32];
    char publishingHouse[16];
    short int year;
    short int qtyPages;
};
struct Node {
    Node *next = nullptr;
    union {
        record data{};
        unsigned char Digit[sizeof(record)];
    };
};
