# CHANGELOG
# Written by Josh Grooms on 20151102

add_library(Disunity2D SHARED
    Entity2D.cpp
    Texture2D.cpp
)

target_link_libraries(Disunity2D
    DisunityOpenGL
    DisunityUtilities
)
