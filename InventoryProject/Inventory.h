#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <string>
#include <vector>

class Inventory
{
private:
    std::vector<Item> items;
    int nextId;

public:
    Inventory();

    bool isEmpty() const;
    const std::vector<Item>& getAll() const;
    Item* findById(int id);

    bool addItem(const std::string& name, int quantity, double price);
    bool updateItem(int id, const std::string& name, int quantity, double price);
    bool deleteItem(int id);

    std::string listAsText() const;
    std::string itemAsText(int id);
};

#endif#pragma once
