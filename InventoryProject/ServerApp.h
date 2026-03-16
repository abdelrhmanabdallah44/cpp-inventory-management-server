#ifndef SERVERAPP_H
#define SERVERAPP_H

#include "Inventory.h"
#include "Request.h"
#include "Response.h"
#include "Router.h"
#include <string>

enum class AppState
{
    Idle,
    ReadRequest,
    ParseRequest,
    RouteRequest,
    SendResponse,
    Exit
};

class ServerApp
{
private:
    Inventory inventory;
    Router router;
    AppState state;
    std::string rawInput;
    Request currentRequest;
    Response currentResponse;

    void printHelp();

public:
    ServerApp();
    void seedData();
    void run();
};

#endif
