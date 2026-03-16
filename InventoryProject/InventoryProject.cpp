#include "Inventory.h"
#include <sstream>

Inventory::Inventory() : nextId(1) {}

bool Inventory::isEmpty() const
{
    return items.empty();
}

const std::vector<Item>& Inventory::getAll() const
{
    return items;
}

Item* Inventory::findById(int id)
{
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (items[i].id == id)
        {
            return &items[i];
        }
    }
    return nullptr;
}

bool Inventory::addItem(const std::string& name, int quantity, double price)
{
    if (name.empty() || quantity < 0 || price < 0)
    {
        return false;
    }

    Item item;
    item.id = nextId++;
    item.name = name;
    item.quantity = quantity;
    item.price = price;

    items.push_back(item);
    return true;
}

bool Inventory::updateItem(int id, const std::string& name, int quantity, double price)
{
    Item* item = findById(id);

    if (item == nullptr || name.empty() || quantity < 0 || price < 0)
    {
        return false;
    }

    item->name = name;
    item->quantity = quantity;
    item->price = price;
    return true;
}

bool Inventory::deleteItem(int id)
{
    for (std::vector<Item>::iterator it = items.begin(); it != items.end(); ++it)
    {
        if (it->id == id)
        {
            items.erase(it);
            return true;
        }
    }
    return false;
}

std::string Inventory::listAsText() const
{
    if (items.empty())
    {
        return "No items found.";
    }

    std::ostringstream out;
    out << "Items List:\n";
    out << "ID | Name | Quantity | Price\n";
    out << "-----------------------------\n";

    for (size_t i = 0; i < items.size(); ++i)
    {
        out << items[i].id << " | "
            << items[i].name << " | "
            << items[i].quantity << " | "
            << items[i].price << "\n";
    }

    return out.str();
}

std::string Inventory::itemAsText(int id)
{
    Item* item = findById(id);

    if (item == nullptr)
    {
        return "";
    }

    std::ostringstream out;
    out << "Item Found:\n";
    out << "ID: " << item->id << "\n";
    out << "Name: " << item->name << "\n";
    out << "Quantity: " << item->quantity << "\n";
    out << "Price: " << item->price << "\n";

    return out.str();
}