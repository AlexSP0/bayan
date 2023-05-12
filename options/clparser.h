#ifndef CLPARSER_H
#define CLPARSER_H

#include "ioptions.h"

#include <boost/program_options.hpp>
#include <memory>

class CLParser
{
public:
    CLParser();

    std::shared_ptr<IOptions> getOptions(int, char **);

private:
    boost::program_options::options_description optionsDescription;

    boost::program_options::variables_map variablesMap;
};

#endif // CLPARSER_H
