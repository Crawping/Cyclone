
file(COPY "Shaders" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

include_directories(Shaders)


add_library(DisunityOpenGL SHARED
    CleanupGL.h
    EnumerationsGL.h
    FrameBuffer.cpp
    GLX.cpp
    OpenGL.c
    Shader.cpp
    ShaderPipeline.cpp
    TextureSampler.cpp
    Vertex.h
    VertexBuffer.cpp
)

target_link_libraries(DisunityOpenGL
    GL
    DisunityUtilities
)

