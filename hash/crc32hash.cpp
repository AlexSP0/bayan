#include <boost/crc.hpp>

#include "crc32hash.h"

std::string CRC32Hash::hashAsString(const char *data, size_t size)
{
    boost::crc_32_type result;

    result.process_bytes(data, size);

    return std::to_string(result.checksum());
}
