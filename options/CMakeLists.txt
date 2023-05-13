set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(HEADERS
    ioptions.h
    cloptions.h
    clparser.h
)

set(SOURCES
    cloptions.cpp
    clparser.cpp
)

add_library(options STATIC ${HEADERS} ${SOURCES})
target_link_libraries(options PUBLIC ${Boost_LIBRARIES})
