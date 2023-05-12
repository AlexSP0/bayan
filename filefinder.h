#ifndef FILEFINDER_H
#define FILEFINDER_H

#include <filesystem>
#include <memory>

#include <options/ioptions.h>

class FileFinder
{
public:
    FileFinder(std::shared_ptr<IOptions> options);

    void scan();

    void out();

private:
    bool isMatchMasks(const std::string &filename) const;

    bool isPathExcluded(const std::filesystem::recursive_directory_iterator &it);

private:
    std::shared_ptr<IOptions> m_options;

    std::vector<std::pair<std::filesystem::path, size_t>> m_fileList;
};

#endif // FILEFINDER_H
