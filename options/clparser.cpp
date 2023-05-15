#include "clparser.h"
#include "../hash/crc32hash.h"
#include "../hash/md5hash.h"
#include "cloptions.h"

#include <iostream>

CLParser::CLParser()
    : optionsDescription("Options")
{
    using path    = std::filesystem::path;
    namespace bpo = boost::program_options;

    optionsDescription.add_options()
            (
                "includes,i",
                bpo::value<std::vector<path>>()
                ->default_value(std::vector<path>(1, "./"), "./")
                ->multitoken()
                ->zero_tokens()
                ->composing(),
                "Include path for scanning"
            )
            (
                "excludes, e",
                bpo::value<std::vector<path>>()
                ->default_value(std::vector<path>(), "empty")
                ->multitoken()
                ->zero_tokens()
                ->composing(),
                "Include path for scanning"
            )
            (
                "level,l",
                bpo::value<long>()->default_value(0L),
                "Scan nesting level.")("min-size,s",
                bpo::value<long>()->default_value(1L),
                "Minimum file size in bytes for scanning."
            )
            (
                "masks,m",
                bpo::value<std::vector<std::string>>()
                ->default_value(std::vector<std::string>(), "'*'")
                ->multitoken()
                ->zero_tokens()
                ->composing(),
                "Masks for comparison."
            )
            (
                "block-size,b",
                bpo::value<long>()->default_value(512L),
                "Block size for reading file."
            )
            (   "algorithm,a",
                bpo::value<std::string>()->default_value("crc32"),
                "Hash algorithm: md5 or crc32."
            )
            (
                "help,h",
                "Show this page."
            );
}

std::shared_ptr<IOptions> CLParser::getOptions(int argc, char **argv)
{
    using path    = std::filesystem::path;
    namespace bpo = boost::program_options;

    try
    {
        bpo::store(bpo::parse_command_line(argc, argv, optionsDescription), variablesMap);

        bpo::notify(variablesMap);

        std::shared_ptr<CLOptions> options = std::make_shared<CLOptions>();

        if (variablesMap.count("help"))
        {
            std::cout << optionsDescription << "\n";
            return options;
        }

        if (variablesMap.count("includes"))
        {
            options->m_includePaths = variablesMap["includes"].as<std::vector<path>>();

            for (auto &path : options->m_includePaths)
            {
                if (path.is_relative())
                {
                    path = std::filesystem::canonical(path);
                }
            }
        }

        if (variablesMap.count("excludes"))
        {
            options->m_excludePaths = variablesMap["excludes"].as<std::vector<path>>();

            for (auto &path : options->m_excludePaths)
            {
                if (path.is_relative())
                {
                    path = std::filesystem::canonical(path);
                }
            }
        }

        if (variablesMap.count("level"))
        {
            long nLevel = variablesMap["level"].as<long>();

            if (nLevel < 0)
            {
                throw std::logic_error("Level scanning must be unsigned integer");
            }

            options->m_levelScanning = nLevel + 1;
        }

        if (variablesMap.count("min-size"))
        {
            long nMinSize = variablesMap["min-size"].as<long>();

            if (nMinSize < 1)
            {
                throw std::logic_error("Minimum file size must be greater than 0");
            }

            options->m_minFileSize = static_cast<std::size_t>(nMinSize);
        }

        if (variablesMap.count("masks"))
        {
            for (auto &mskStr : variablesMap["masks"].as<std::vector<std::string>>())
                options->m_masks.emplace_back(std::string(mskStr));
        }

        if (variablesMap.count("block-size"))
        {
            long nBlockSize = variablesMap["block-size"].as<long>();

            if (nBlockSize < 1)
            {
                throw std::logic_error("Minimum block size must be greater than 0");
            }

            options->m_blockSize = static_cast<size_t>(nBlockSize);
        }

        if (variablesMap.count("algorithm"))
        {
            std::string strHash = variablesMap["algorithm"].as<std::string>();

            if (strHash != "crc32" && strHash != "md5")
            {
                throw std::logic_error("The hash algorithm '" + strHash + "' not supported");
            }
            if (strHash == "crc32")
                options->m_hash = std::make_shared<CRC32Hash>();
            else
                options->m_hash = std::make_shared<MD5Hash>();
        }

        return options;
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl << std::endl;
        std::cout << optionsDescription << std::endl;
        return std::shared_ptr<CLOptions>();
    }
}
