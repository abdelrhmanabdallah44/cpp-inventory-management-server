#include "Router.h"
#include <cstdlib>
#include <cctype>
#include <sstream>

Router::Router(Inventory& inv) : inventory(inv) {}

bool Router::startsWith(const std::string& text, const std::string& prefix)
{
    if (text.size() < prefix.size())
    {
        return false;
    }

    return text.substr(0, prefix.size()) == prefix;
}

bool Router::isNumber(const std::string& s)
{
    if (s.empty())
    {
        return false;
    }

    for (size_t i = 0; i < s.size(); ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
        {
            return false;
        }
    }

    return true;
}

int Router::extractId(const std::string& path)
{
    const std::string prefix = "/items/";

    if (!startsWith(path, prefix))
    {
        return -1;
    }

    std::string idPart = path.substr(prefix.size());

    if (!isNumber(idPart))
    {
        return -1;
    }

    return std::atoi(idPart.c_str());
}

bool Router::parseBody(const std::string& body, std::string& name, int& quantity, double& price)
{
    std::string quantityText;
    std::string priceText;
    std::istringstream ss(body);

    if (!std::getline(ss, name, ','))
    {
        return false;
    }

    if (!std::getline(ss, quantityText, ','))
    {
        return false;
    }

    if (!std::getline(ss, priceText))
    {
        return false;
    }

    if (name.empty())
    {
        return false;
    }

    std::istringstream qStream(quantityText);
    std::istringstream pStream(priceText);

    qStream >> quantity;
    pStream >> price;

    if (qStream.fail() || pStream.fail())
    {
        return false;
    }

    return true;
}

Response Router::handle(const Request& req)
{
    if (req.method == "GET" && req.path == "/items")
    {
        return { 200, "OK", inventory.listAsText() };
    }

    if (req.method == "GET" && startsWith(req.path, "/items/"))
    {
        int id = extractId(req.path);

        if (id == -1)
        {
            return { 400, "Bad Request", "Invalid item id." };
        }

        std::string itemText = inventory.itemAsText(id);

        if (itemText.empty())
        {
            return { 404, "Not Found", "Item not found." };
        }

        return { 200, "OK", itemText };
    }

    if (req.method == "POST" && req.path == "/items")
    {
        std::string name;
        int quantity = 0;
        double price = 0.0;

        if (!parseBody(req.body, name, quantity, price))
        {
            return { 400, "Bad Request", "Body format must be: name,quantity,price" };
        }

        bool added = inventory.addItem(name, quantity, price);

        if (!added)
        {
            return { 400, "Bad Request", "Invalid item data." };
        }

        return { 201, "Created", "Item added successfully." };
    }

    if (req.method == "PUT" && startsWith(req.path, "/items/"))
    {
        int id = extractId(req.path);

        if (id == -1)
        {
            return { 400, "Bad Request", "Invalid item id." };
        }

        std::string name;
        int quantity = 0;
        double price = 0.0;

        if (!parseBody(req.body, name, quantity, price))
        {
            return { 400, "Bad Request", "Body format must be: name,quantity,price" };
        }

        bool updated = inventory.updateItem(id, name, quantity, price);

        if (!updated)
        {
            return { 404, "Not Found", "Item not found or invalid data." };
        }

        return { 200, "OK", "Item updated successfully." };
    }

    if (req.method == "DELETE" && startsWith(req.path, "/items/"))
    {
        int id = extractId(req.path);

        if (id == -1)
        {
            return { 400, "Bad Request", "Invalid item id." };
        }

        bool deleted = inventory.deleteItem(id);

        if (!deleted)
        {
            return { 404, "Not Found", "Item not found." };
        }

        return { 200, "OK", "Item deleted successfully." };
    }

    return { 405, "Method Not Allowed", "Unsupported route or method." };
}