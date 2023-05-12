#ifndef HANDLER_H
#define HANDLER_H

#include <fstream>
#include <iostream>

#include "ihandler.h"
#include "options/ioptions.h"

struct File
{
    std::filesystem::path path;

    std::unique_ptr<std::ifstream> readerStream;

    std::vector<std::string> hashesOfBlocks;

    size_t fileSize;
};

class Handler : public IHandler
{
public:
    Handler(std::shared_ptr<IOptions> options);

    virtual ~Handler();

    void addFile(const std::filesystem::path &path, size_t size) override;

private:
    void searchEqualFiles();

    std::string readBlock(File &file);

    std::string readNextBlock(File &file, size_t size);

private:
    std::shared_ptr<IOptions> m_options;

    size_t m_blockSize;

    std::unique_ptr<char[]> m_buffer;

    std::vector<File> m_fileList;
};

#endif // HANDLER_H
