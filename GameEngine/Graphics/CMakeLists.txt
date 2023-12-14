##
## CMakeLists: RType/Client
##

add_library(r-type-graphics SHARED
    src/rtype/AudioManager.cpp
    src/rtype/InputManager.cpp
    src/rtype/SceneManager.cpp
    src/rtype/SpriteManager.cpp
    src/rtype/WindowManager.cpp
    src/rtype/TextureManager.cpp
)


target_include_directories(r-type-graphics PRIVATE ./include)
target_compile_options(r-type-graphics PRIVATE ${WARNING_FLAGS})
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD_REQUIRED ON)