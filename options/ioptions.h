#ifndef IOPTIONS_H
#define IOPTIONS_H

#include <filesystem>
#include <vector>

#include "../bayantypes.h"

class IOptions
{
public:
    virtual ~IOptions() = default;

    virtual void printOpt() = 0;

    virtual std::string getHashOffBuffer(const char *inBuffer) = 0;

    virtual size_t getBlockSize() = 0;

    virtual size_t getMinFileSize() = 0;

    virtual long getLevelScanning() = 0;

    virtual std::vector<std::filesystem::path> getIncludePath() = 0;

    virtual std::vector<std::filesystem::path> getExcludePath() = 0;

    virtual std::vector<Mask> getMasks() = 0;
};

#endif
