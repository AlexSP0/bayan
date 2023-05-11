#ifndef BAYANTYPES_H
#define BAYANTYPES_H

#include <boost/algorithm/string/replace.hpp>
#include <regex>
#include <string>

class Mask
{
public:
    Mask(std::string mask)
    {
        boost::replace_all(mask, ".", "\\.");
        boost::replace_all(mask, "*", "\\*");
        boost::replace_all(mask, "?", "\\?");
        boost::replace_all(mask, "\\?", ".");
        boost::replace_all(mask, "\\*", ".*");

        m_regex = std::regex(mask, std::regex::icase);
    }

    bool operator()(const std::string &strValue) { return std::regex_match(strValue, m_match, m_regex); }

private:
    std::regex m_regex;
    std::smatch m_match;
};

#endif // BAYANTYPES_H
