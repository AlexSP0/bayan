#include "filefinder.h"

FileFinder::FileFinder(std::shared_ptr<IOptions> options)
    : m_options(options)
    , m_fileList()
{}

void FileFinder::scan()
{
    for (const auto &currentIncludePath : m_options->getIncludePath())
    {
        auto curIter = std::filesystem::recursive_directory_iterator(currentIncludePath);
        auto endIter = std::filesystem::recursive_directory_iterator();

        for (; curIter != endIter; curIter++)
        {
            if (curIter.depth() < m_options->getLevelScanning() && !(isPathExcluded(curIter))
                && curIter->is_regular_file() && curIter->file_size() > m_options->getMinFileSize()
                && isMatchMasks(curIter->path().filename().string()))
            {
                m_fileList.emplace_back(curIter->path(), curIter->file_size());
            }
        }
    }
}

void FileFinder::out() {}

bool FileFinder::isMatchMasks(const std::string &filename) const
{
    auto masks = m_options->getMasks();

    bool result = !masks.size();

    for (Mask currentMask : masks)
    {
        if (currentMask(filename))
        {
            result = true;
            break;
        }
    }

    return result;
}

bool FileFinder::isPathExcluded(const std::filesystem::recursive_directory_iterator &it)
{
    bool result = false;

    for (const auto &currentMask : m_options->getExcludePath())
    {
        if (it->path().parent_path() == currentMask)
        {
            result = true;
            break;
        }
    }

    return result;
}
