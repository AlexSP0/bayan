#ifndef CLOPTIONS_H
#define CLOPTIONS_H

#include "../hash/ihash.h"
#include "ioptions.h"

class CLOptions : public IOptions
{
public:
    CLOptions();

public:
    void printOpt() override;

    std::string getHashOffBuffer(const char *inBuffer) override;

    size_t getBlockSize() override;

    size_t getMinFileSize() override;

    long getLevelScanning() override;

    std::vector<std::filesystem::path> getIncludePath() override;

    std::vector<std::filesystem::path> getExcludePath() override;

    std::vector<Mask> getMasks() override;

private:
    std::vector<std::filesystem::path> m_includePaths;
    std::vector<std::filesystem::path> m_excludePaths;

    long m_levelScannig;

    std::size_t m_minFileSize;

    std::vector<Mask> m_masks;

    std::size_t m_blockSize;

    std::shared_ptr<IHash> m_hash;
};

#endif // CLOPTIONS_H
