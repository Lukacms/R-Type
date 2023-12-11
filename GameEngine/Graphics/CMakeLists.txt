##
## CMakeLists: RType/Client
##

add_library(r-type-graphics SHARED
    src/Manager/AudioManager.cpp
    src/Manager/InputManager.cpp
    src/Manager/SceneManager.cpp
    src/Manager/SpriteManager.cpp
    src/Manager/WindowManager.cpp
    src/Manager/TextureManager.cpp
)


target_include_directories(r-type-graphics PRIVATE ./include)
target_compile_options(r-type-graphics PRIVATE ${WARNING_FLAGS})
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD 20)
set_property(TARGET r-type-graphics PROPERTY CXX_STANDARD_REQUIRED ON)