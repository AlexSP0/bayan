#ifndef CRC32HASH_H
#define CRC32HASH_H

#include "ihash.h"

class CRC32Hash : public IHash
{
public:
    std::string hashAsString(const char *data, size_t size);
};

#endif // CRC32HASH_H
