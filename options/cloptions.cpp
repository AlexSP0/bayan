#include "cloptions.h"
#include <iostream>

CLOptions::CLOptions() {}

void CLOptions::printOpt()
{
    for (const auto &currentPath : m_includePaths)
    {
        std::cout << "IPath: " << currentPath << std::endl;
    }

    for (const auto &currentPath : m_excludePaths)
    {
        std::cout << "EPath: " << currentPath << std::endl;
    }

    std::cout << m_masks.size() << std::endl;

    std::cout << m_levelScanning << std::endl;

    std::cout << getMinFileSize() << std::endl;

    std::cout << m_blockSize << std::endl;

    std::cout << m_hash->hashAsString("0", 3) << std::endl;
}

std::string CLOptions::getHashOffBuffer(const char *inBuffer)
{
    return m_hash->hashAsString(inBuffer, m_blockSize);
}

size_t CLOptions::getBlockSize()
{
    return m_blockSize;
}

size_t CLOptions::getMinFileSize()
{
    return m_minFileSize;
}

long CLOptions::getLevelScanning()
{
    return m_levelScanning;
}

std::vector<std::filesystem::path> CLOptions::getIncludePath()
{
    return m_includePaths;
}

std::vector<std::filesystem::path> CLOptions::getExcludePath()
{
    return m_excludePaths;
}

std::vector<Mask> CLOptions::getMasks()
{
    return m_masks;
}
