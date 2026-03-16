Inventory Management Server – C++ Project
1. Project Overview

This project implements a minimal server-like architecture in modern C++ for managing an inventory system.

The application simulates request handling similar to a backend server. It processes requests, routes them to the appropriate handler, and returns responses.

The goal of this project is to demonstrate:

Object Oriented Design

Modular Architecture

Separation of Concerns

Clean project structure

Basic request/response flow

The system allows managing inventory items through a routing mechanism similar to web servers.

2. Technologies Used

Language: C++17

Compiler: GCC / MSVC

Build System: Makefile (or Visual Studio build)

Architecture Style: Modular OOP

Concepts used:

Classes

Encapsulation

Composition

Basic routing logic

Separation of modules

3. Project Architecture

The project is divided into multiple modules where each component has a clear responsibility.

Client Request
      │
      ▼
   ServerApp
      │
      ▼
    Router
      │
      ▼
   Inventory
      │
      ▼
     Item

Supporting modules:

Request
Response
RequestParser
4. Project Structure
InventoryProject
│
├── main.cpp
│
├── ServerApp.h
├── ServerApp.cpp
│
├── Router.h
├── Router.cpp
│
├── Inventory.h
├── Inventory.cpp
│
├── Item.h
│
├── Request.h
├── Response.h
│
├── RequestParser.h
└── RequestParser.cpp
5. Components Description
5.1 main.cpp

Entry point of the application.

It creates the server instance and starts the application.

Example:

int main()
{
    ServerApp app;
    app.run();
    return 0;
}
5.2 ServerApp

Responsible for starting the application and initializing core components.

Responsibilities:

Initialize router

Start request handling loop

Manage application lifecycle

5.3 Router

The router is responsible for handling incoming requests and dispatching them to the correct logic.

Example routes:

GET /items
POST /items
DELETE /items

Router interacts with:

Request

Response

Inventory

5.4 Inventory

Handles the business logic of inventory management.

Responsibilities:

Store items

Add new items

Remove items

List available items

Example operations:

addItem()
removeItem()
getItems()
5.5 Item

Represents a single inventory item.

Example fields:

id
name
quantity
5.6 Request

Represents a client request.

Example fields:

method
path
body

Example request:

GET /items
5.7 Response

Represents the server response.

Example fields:

status
body

Example:

200 OK
Items list returned
5.8 RequestParser

Responsible for parsing raw request strings and converting them into structured Request objects.

Example:

Input:

GET /items

Parsed into:

method = GET
path = /items
6. Request Flow (Sequence Diagram)

Typical request flow:

Client
   │
   │ Request
   ▼
ServerApp
   │
   ▼
Router
   │
   ▼
Inventory
   │
   ▼
Response
   │
   ▼
Client

Steps:

Client sends request

ServerApp receives it

Router determines handler

Inventory performs operation

Response returned

7. OOP Design Principles Used

The project follows several design principles:

Encapsulation

Each class manages its own data.

Example:

Inventory manages items
Single Responsibility Principle

Each module has a single responsibility.

Examples:

Router → routing
Inventory → data management
RequestParser → parsing
Modularity

Project is divided into independent modules.

8. How to Build

Using compiler:

g++ *.cpp -o inventory_app

Run:

./inventory_app

Or using Visual Studio:

Build Solution
Run
9. Example Execution

Program output example:

Server Started
Router Initialized
Inventory Ready
10. Future Improvements

Possible enhancements:

Real socket server

HTTP protocol support

Database storage

REST API implementation

JSON request parsing

Multithreading

11. Conclusion

This project demonstrates how to design a modular C++ backend-style architecture.

It focuses on:

clean architecture

modular components

OOP design

maintainable code structure
