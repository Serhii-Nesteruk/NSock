file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(Utils ${Sources})

target_include_directories(Utils PUBLIC ./include)