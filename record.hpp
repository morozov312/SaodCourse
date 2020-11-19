#pragma once
struct record {
    char author[12];
    char title[32];
    char publishingHouse[16];
    short int year;
    short int qtyPages;
};
struct Node {
    record data{};
    Node *next = nullptr;
};
