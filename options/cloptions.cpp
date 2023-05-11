#include "cloptions.h"

CLOptions::CLOptions() {}

void CLOptions::printOpt() {}

std::string CLOptions::getHashOffBuffer(const char *)
{
    return "";
}

size_t CLOptions::getBlockSize()
{
    return 0L;
}

size_t CLOptions::getMinFileSize()
{
    return 0L;
}

long CLOptions::getLevelScanning()
{
    return 0L;
}

std::vector<std::filesystem::path> CLOptions::getIncludePath()
{
    return {};
}

std::vector<std::filesystem::path> CLOptions::getExcludePath()
{
    return {};
}

std::vector<Mask> CLOptions::getMasks()
{
    return {};
}
