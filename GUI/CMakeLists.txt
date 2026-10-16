cmake_minimum_required(VERSION 3.10)
project(zappy_gui)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
 
find_package(raylib REQUIRED)

include_directories(
    src
    src/Core
    src/Graphics/Rendering

    src/Graphics/Raylib
    src/Graphics/Raylib/Music
    src/Graphics/Raylib/Font
    src/Graphics/Raylib/Texture
    src/Graphics/Raylib/Rectangle
    src/Graphics/Raylib/Camera

    src/Graphics/Ui
    src/Graphics/Ui/Components
    src/World
    src/World/Map
    src/World/Entities
    src/World/Entities/Player
    src/World/Entities/Animations
    src/World/Entities/Food
    src/World/Entities/Stone
    src/World/Entities/Egg
    src/World/Entities/Prop
    src/World/Entities/ModelCache
    src/Utils
    src/Menu
    src/Network
    src/Parser
    src/MusicManager
)

set(SOURCE_FILES
    src/main.cpp
    src/Core/Core.cpp
    src/Core/KeyHandler.cpp
    src/Core/ActionMap.cpp

    src/Graphics/Raylib/Music/MusicSound.cpp
    src/Graphics/Raylib/Font/TextFont.cpp
    src/Graphics/Raylib/Texture/ImageTexture.cpp
    src/Graphics/Raylib/Rectangle/RectangleImage.cpp
    src/Graphics/Raylib/Camera/ViewCamera.cpp

    src/Graphics/Rendering/Renderer.cpp
    src/Graphics/Ui/SubWindow.cpp
    src/Graphics/Ui/SubWindowManager.cpp
    src/Graphics/Ui/BookHandler.cpp
    src/Graphics/Ui/PlayerPanelHandler.cpp
    src/Graphics/Ui/TilePanelHandler.cpp
    src/Graphics/Ui/ChatPanelHandler.cpp
    src/Graphics/Ui/Components/ASubWindowComponent.cpp
    src/Graphics/Ui/Components/TextureComponent.cpp
    src/Graphics/Ui/Components/LoopingComponent.cpp
    src/Graphics/Ui/Components/OneshotComponent.cpp
    src/Graphics/Ui/Components/ContainerComponent.cpp
    src/Graphics/Ui/Components/Button.cpp
    src/Graphics/Ui/Components/PlayerInfoComponent.cpp
    src/Graphics/Ui/Components/TileInfoComponent.cpp
    src/Graphics/Ui/Components/TextComponent.cpp
    src/Graphics/Ui/Components/ChatInfoComponent.cpp
    src/Graphics/Ui/Components/GameInfoComponent.cpp
    src/World/Map/Map.cpp
    src/World/Entities/AEntity.cpp
    src/World/Entities/Player/Player.cpp
    src/World/Entities/Egg/Egg.cpp
    src/World/Entities/Animations/AnimationHandler.cpp
    src/World/Entities/ModelCache/ModelCache.cpp
    src/Menu/menu.cpp
    src/World/Entities/Food/Food.cpp
    src/World/Entities/Stone/Stone.cpp
    src/World/Map/Tile.cpp
    src/World/Entities/Prop/Prop.cpp
    src/Network/Client.cpp
    src/Network/ProtocolHandler.cpp
    src/Parser/Parser.cpp
    src/MusicManager/MusicManager.cpp
)
 
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
 
set_target_properties(zappy_gui PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/..
)
 
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
