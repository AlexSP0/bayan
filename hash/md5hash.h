#ifndef MD5HASH_H
#define MD5HASH_H

#include "ihash.h"

#include <string>

class MD5Hash : public IHash
{
public:
    std::string hashAsString(const char *data, size_t size);
};

#endif
