#pragma once

#include <string>
#include <iostream>

using namespace std;

class Item {
public:
    Item() = default;
    virtual compl Item() = default;
    
    string name = "ItemTest";
    string description = "DescriptionTest";
    int value = 10;
    int position = 1;
    int num = 1;
    int id = 0;
    
    void Add(Item item);
    void Remove(Item item);
    void Show(void);
};

class Cure: public Item {
public:
    Cure() = default;
    explicit Cure(string const& newName, string const& newDescription, int newValue, int newCurePoints);
    virtual compl Cure() = default;
    
    int CurePoints = 0;
};
