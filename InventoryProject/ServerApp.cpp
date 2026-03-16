#include "ServerApp.h"
#include "RequestParser.h"
#include <iostream>

ServerApp::ServerApp()
    : router(inventory), state(AppState::Idle)
{
}

void ServerApp::printHelp()
{
    std::cout << "Available requests:\n";
    std::cout << "GET /items\n";
    std::cout << "GET /items/1\n";
    std::cout << "POST /items Mouse,10,250.5\n";
    std::cout << "PUT /items/1 Keyboard,7,500\n";
    std::cout << "DELETE /items/1\n";
    std::cout << "Type exit to quit.\n";
    std::cout << "-------------------------\n";
}

void ServerApp::seedData()
{
    inventory.addItem("Mouse", 10, 150.0);
    inventory.addItem("Keyboard", 5, 300.0);
    inventory.addItem("Monitor", 3, 2500.0);
}

void ServerApp::run()
{
    seedData();
    printHelp();

    while (state != AppState::Exit)
    {
        switch (state)
        {
        case AppState::Idle:
            state = AppState::ReadRequest;
            break;

        case AppState::ReadRequest:
            std::cout << "> ";
            std::getline(std::cin, rawInput);

            if (rawInput == "exit")
            {
                state = AppState::Exit;
            }
            else if (rawInput.empty())
            {
                std::cout << "Please enter a request.\n";
                state = AppState::ReadRequest;
            }
            else
            {
                state = AppState::ParseRequest;
            }
            break;

        case AppState::ParseRequest:
            currentRequest = RequestParser::parse(rawInput);

            if (currentRequest.method.empty() || currentRequest.path.empty())
            {
                currentResponse = { 400, "Bad Request", "Invalid request format." };
                state = AppState::SendResponse;
            }
            else
            {
                state = AppState::RouteRequest;
            }
            break;

        case AppState::RouteRequest:
            currentResponse = router.handle(currentRequest);
            state = AppState::SendResponse;
            break;

        case AppState::SendResponse:
            currentResponse.print();
            state = AppState::ReadRequest;
            break;

        case AppState::Exit:
            break;
        }
    }

    std::cout << "Application closed.\n";
}