#include "handler.h"

#include <fstream>

Handler::Handler(std::shared_ptr<IOptions> options)
    : m_options(options)
    , m_blockSize(options->getBlockSize())
    , m_buffer(std::make_unique<char[]>(m_blockSize))
    , m_fileList()
{}

Handler::~Handler() {}

void Handler::addFile(const std::filesystem::path &path, size_t size)
{
    m_fileList.emplace_back(File{path, std::unique_ptr<std::ifstream>(), std::vector<std::string>(), size});

    if (m_fileList.size() > 1)
    {
        searchEqualFiles();
    }
}

void Handler::searchEqualFiles()
{
    auto currentIter = m_fileList.rbegin();

    auto nextBlockExits = [this](auto &it) { return it->hashesOfBlocks.size() * m_blockSize < it->fileSize; };

    for (auto nextIter = std::next(currentIter); nextIter != m_fileList.rend(); ++nextIter)
    {
        if (currentIter->fileSize == nextIter->fileSize)
        {
            for (size_t i = 0; currentIter->fileSize / m_blockSize; i++)
            {
                if (nextBlockExits(currentIter) && readNextBlock(*currentIter, i) != readNextBlock(*nextIter, i))
                {
                    break;
                }
            }

            if (currentIter->hashesOfBlocks.size()
                && currentIter->hashesOfBlocks.size() == nextIter->hashesOfBlocks.size()
                && currentIter->hashesOfBlocks.back() == nextIter->hashesOfBlocks.back())
            {
                std::cout << currentIter->path.string() << "\n" << nextIter->path.string() << "\n\n";
            }
        }
    }
}

std::string Handler::readBlock(File &file)
{
    auto &currentStream = file.readerStream;

    if (!currentStream)
    {
        currentStream = std::make_unique<std::ifstream>(file.path, std::ios::binary);
    }

    size_t currentBlock    = file.hashesOfBlocks.size();
    size_t currentPosition = currentBlock * m_blockSize;

    currentStream->seekg(currentPosition, std::ios_base::beg);
    currentStream->read(m_buffer.get(), m_blockSize);

    if (currentStream->eof())
    {
        size_t noUsedReminder = file.fileSize - currentPosition;
        std::memset(m_buffer.get() + noUsedReminder, 0, m_blockSize - noUsedReminder);
    }

    std::string result = m_options->getHashOffBuffer(m_buffer.get());

    file.hashesOfBlocks.push_back(result);

    return result;
}

std::string Handler::readNextBlock(File &file, size_t size)
{
    if (file.hashesOfBlocks.size() > size)
    {
        return file.hashesOfBlocks.at(size);
    }
    else
    {
        return readBlock(file);
    }
}
