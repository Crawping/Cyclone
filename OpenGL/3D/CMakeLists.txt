
add_library(Disunity3D SHARED
    Entity3D.cpp
    Quad.cpp
)

target_link_libraries(Disunity3D
    Disunity2D
    DisunityOpenGL
    DisunityUtilities
)
