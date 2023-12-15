file(
        GLOB Sources
        "include/*.h"
        "include/*.inl"
        "source/*.cpp"
)

add_library(Socket ${Sources})

target_include_directories(Socket PUBLIC ./include)

target_link_libraries(Socket PUBLIC Utils)
