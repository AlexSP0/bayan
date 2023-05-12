#ifndef IHANDLER_H
#define IHANDLER_H

#include <filesystem>

class IHandler
{
public:
    virtual ~IHandler() = default;

    virtual void addFile(const std::filesystem::path &path, size_t size) = 0;
};

#endif // IHANDLER_H
