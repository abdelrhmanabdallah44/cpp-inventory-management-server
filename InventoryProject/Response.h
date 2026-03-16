#pragma once
#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>
#include <string>

struct Response
{
    int status;
    std::string statusText;
    std::string body;

    void print() const
    {
        std::cout << "HTTP/1.1 " << status << ' ' << statusText << "\n";
        std::cout << body << "\n";
        std::cout << "-------------------------\n";
    }
};

#endif