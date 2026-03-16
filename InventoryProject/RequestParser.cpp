#include "RequestParser.h"
#include <sstream>

Request RequestParser::parse(const std::string& input)
{
    Request req;
    std::istringstream stream(input);

    stream >> req.method >> req.path;
    std::getline(stream, req.body);

    if (!req.body.empty() && req.body[0] == ' ')
    {
        req.body.erase(0, 1);
    }

    return req;
}