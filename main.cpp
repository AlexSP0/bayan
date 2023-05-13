#include "options/clparser.h"

#include "filefinder.h"
#include "handler.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<IOptions> options = CLParser().getOptions(argc, argv);

    if (!options)
    {
        return 0;
    }

    std::shared_ptr<Handler> handler = std::make_shared<Handler>(options);

    FileFinder finder(options);

    finder.scan();
    finder.out(handler);

    return 0;
}
