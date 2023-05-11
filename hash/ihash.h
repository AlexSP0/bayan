#ifndef IHASH_H
#define IHASH_H

#include <memory>
#include <string>

class IHash
{
public:
    virtual ~IHash() = default;

    virtual std::string hasAsString(const char *data, size_t size) = 0;
};

#endif
