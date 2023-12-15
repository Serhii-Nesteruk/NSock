file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(Socket ${Sources}
        include/Socket.inl
        include/Socket.h
        source/Address.cpp
        include/Address.h)

target_include_directories(Socket PUBLIC ./include)

target_link_libraries(Socket PUBLIC Utils)
