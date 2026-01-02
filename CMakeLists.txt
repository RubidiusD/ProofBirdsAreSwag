cmake_minimum_required(VERSION 3.14)
project(BirdsAreSwag)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

#---- File management & .exe creation ----#

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES
    src/main.cpp
    src/Game.h src/Game.cpp

    src/managers/InputManager.h src/managers/InputManager.cpp
    src/managers/ActionManager.h src/managers/ActionManager.cpp
    src/managers/MenuManager.h src/managers/MenuManager.cpp
    src/managers/AssetManager.h src/managers/AssetManager.cpp
    src/managers/Settings.h src/managers/Settings.cpp

    src/abstracts/AbstractMenu.h src/abstracts/AbstractMenu.cpp
    src/abstracts/AbstractAction.h src/abstracts/AbstractAction.cpp
    src/abstracts/AbstractChoice.h src/abstracts/AbstractChoice.cpp

    src/abstracts/ScreenElements/AbstractButton.h src/abstracts/ScreenElements/AbstractButton.cpp

    src/birds/menus/SplashScreen.h src/birds/menus/SplashScreen.cpp
    src/birds/menus/MainMenu.h src/birds/menus/MainMenu.cpp
)
add_executable(BirdsAreSwag ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (BirdsAreSwag sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)