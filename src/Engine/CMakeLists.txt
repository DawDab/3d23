cmake_minimum_required(VERSION 3.15)
project(Engine CXX)

add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}" PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

add_library(engine
        Mesh.h Mesh.cpp
        Material.h
        texture.h texture.cpp
        ColorMaterial.h ColorMaterial.cpp
        PhongMaterial.h PhongMaterial.cpp
        mesh_loader.h mesh_loader.cpp
        Light.h
        )
        
target_link_libraries(engine PUBLIC objreader)
target_link_libraries(engine PUBLIC spdlog::spdlog)