#ifndef REQUEST_H
#define REQUEST_H

#include <string>

struct Request
{
    std::string method;
    std::string path;
    std::string body;
};

#endif#pragma once
