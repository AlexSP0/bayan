set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(HEADERS
    ihash.h
    md5hash.h
    crc32hash.h
)

set(SOURCES
    md5hash.cpp
    crc32hash.cpp
)

add_library(hash ${HEADERS} ${SOURCES})
