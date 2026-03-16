#ifndef ROUTER_H
#define ROUTER_H

#include "Inventory.h"
#include "Request.h"
#include "Response.h"
#include <string>

class Router
{
private:
    Inventory& inventory;

    bool startsWith(const std::string& text, const std::string& prefix);
    bool isNumber(const std::string& s);
    int extractId(const std::string& path);
    bool parseBody(const std::string& body, std::string& name, int& quantity, double& price);

public:
    Router(Inventory& inv);
    Response handle(const Request& req);
};

#endif