set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(HEADERS
    ioptions.h
    cloptions.h
)

set(SOURCES
    cloptions.cpp
)

add_library(options STATIC ${HEADERS} ${SOURCES})
