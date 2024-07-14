cmake_minimum_required(VERSION 3.1.0) # Do not raise it without a reason. Bump only when you use some feature that is not supported by older verions

# set the project name
project(GoblinsLot C CXX)

add_executable("goblins-lot")

SET(GCAMP_VERSION "0.241")
SET(GCAMP_VERSION_IS_RELEASE YES)

TARGET_COMPILE_FEATURES("goblins-lot" PRIVATE cxx_std_17)

#  -DBOOST_NO_CXX11_SCOPED_ENUMS -DBOOST_NO_SCOPED_ENUMS  https://stackoverflow.com/questions/18783790/boostfilesystemcopy-file-missing-symbol-in-c11
# and Goblin Camp/src/data/Data.cpp fs::copy_file(source, target);
TARGET_COMPILE_DEFINITIONS("goblins-lot" PRIVATE "-DBOOST_NO_CXX11_SCOPED_ENUMS -DBOOST_NO_SCOPED_ENUMS")

# Add the path for the script to find libtcod
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#### Build with Address Sanitizer. Uncomment it manually
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fsanitize=address -g -O0")
#SET(CMAKE_CXX_COMPILER "/usr/bin/clang++-11")

SET(USE_THREADS TRUE CACHE BOOL "Enable threads")
IF (USE_THREADS)
  MESSAGE(STATUS "Using threads")
ELSE()
  MESSAGE(STATUS "Using no threads")
ENDIF()

SET(GOBLIN_CAMP_BINDIR ${CMAKE_INSTALL_PREFIX}/games CACHE PATH "Path to Goblins' Lot binary")
SET(GOBLIN_CAMP_DATA_BASE_DIR "${CMAKE_INSTALL_PREFIX}/share" CACHE PATH "Base Data Dir Path")
SET(GOBLIN_CAMP_SHAREDIR "${GOBLIN_CAMP_DATA_BASE_DIR}/games/goblins-lot" CACHE PATH "Path to Goblins' Lot shared files")

find_package(Boost REQUIRED COMPONENTS system filesystem serialization iostreams)
find_package(Boost COMPONENTS python REQUIRED)

find_package(Boost COMPONENTS python3 REQUIRED)
find_package(PythonLibs 3 REQUIRED)

if (POLICY CMP0072)
  set(OpenGL_GL_PREFERENCE GLVND)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(ZLIB)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(libtcod REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${PNG_INCLUDE_DIR})
include_directories(${libtcod_INCLUDE_DIR})

ADD_SUBDIRECTORY("game")

SET (data_SRC
"game/src/data/Config.cpp"
"game/src/data/Data.cpp"
"game/src/data/Mods.cpp"
"game/src/data/Paths.cpp"
"game/src/data/Serialization.cpp"
"game/src/data/Tilesets.cpp"
)
SET (main_SRC
"game/src/Announce.cpp"
"game/src/Attack.cpp"
"game/src/Blood.cpp"
"game/src/Camp.cpp"
"game/src/Construction.cpp"
"game/src/Container.cpp"
"game/src/Coordinate.cpp"
"game/src/Door.cpp"
"game/src/Entity.cpp"
"game/src/Events.cpp"
"game/src/Faction.cpp"
"game/src/Farmplot.cpp"
"game/src/Filth.cpp"
"game/src/Fire.cpp"
"game/src/GCamp.cpp"
"game/src/Game.cpp"
"game/src/Item.cpp"
"game/src/Job.cpp"
"game/src/JobManager.cpp"
"game/src/KuhnMunkres.cpp"
"game/src/Logger.cpp"
"game/src/Map.cpp"
"game/src/MapMarker.cpp"
"game/src/MapRenderer.cpp"
"game/src/NPC.cpp"
"game/src/NatureObject.cpp"
"game/src/Random.cpp"
"game/src/SpawningPool.cpp"
"game/src/Spell.cpp"
"game/src/Squad.cpp"
"game/src/Stats.cpp"
"game/src/StatusEffect.cpp"
"game/src/StockManager.cpp"
"game/src/Stockpile.cpp"
"game/src/TCODMapRenderer.cpp"
"game/src/Tile.cpp"
"game/src/Trap.cpp"
"game/src/UI.cpp"
"game/src/Water.cpp"
"game/src/Weather.cpp"
"game/src/Version.cpp"
)

SET (scripting_SRC
"game/src/scripting/API.cpp"
"game/src/scripting/Engine.cpp"
"game/src/scripting/Event.cpp"
"game/src/scripting/_gcampapi/Functions.cpp"
"game/src/scripting/_gcampapi/LoggerStream.cpp"
"game/src/scripting/_gcampapi/PyConstruction.cpp"
"game/src/scripting/_gcampapi/PyItem.cpp"
)

SET (UI_SRC
"game/src/UI/AnnounceDialog.cpp"
"game/src/UI/ConstructionDialog.cpp"
"game/src/UI/DevConsole.cpp"
"game/src/UI/JobDialog.cpp"
"game/src/UI/Menu.cpp"
"game/src/UI/MessageBox.cpp"
"game/src/UI/NPCDialog.cpp"
"game/src/UI/SideBar.cpp"
"game/src/UI/SquadsDialog.cpp"
"game/src/UI/StockManagerDialog.cpp"
"game/src/UI/Tooltip.cpp"
"game/src/UI/UIComponents.cpp"
)

SET (tileRenderer_SRC
"game/src/tileRenderer/ConstructionSprite.cpp"
"game/src/tileRenderer/DrawConstructionVisitor.cpp"
"game/src/tileRenderer/ItemSprite.cpp"
"game/src/tileRenderer/NatureObjectSpriteSet.cpp"
"game/src/tileRenderer/NPCSprite.cpp"
"game/src/tileRenderer/PermutationTable.cpp"
"game/src/tileRenderer/SpellSpriteSet.cpp"
"game/src/tileRenderer/Sprite.cpp"
"game/src/tileRenderer/SpriteSetFactories.cpp"
"game/src/tileRenderer/StatusEffectSprite.cpp"
"game/src/tileRenderer/TerrainSprite.cpp"
"game/src/tileRenderer/TileSet.cpp"
"game/src/tileRenderer/TileSetLoader.cpp"
"game/src/tileRenderer/TilesetParserV1.cpp"
"game/src/tileRenderer/TilesetParserV2.cpp"
"game/src/tileRenderer/TileSetRenderer.cpp"
"game/src/tileRenderer/TileSetTexture.cpp"

"game/src/tileRenderer/sdl/SDLSprite.cpp"
"game/src/tileRenderer/sdl/SDLTilesetRenderer.cpp"

"game/src/tileRenderer/ogl/OGLFunctionExt.cpp"
"game/src/tileRenderer/ogl/OGLResources.cpp"
"game/src/tileRenderer/ogl/OGLSprite.cpp"
"game/src/tileRenderer/ogl/OGLTilesetRenderer.cpp"
"game/src/tileRenderer/ogl/OGLViewportLayer.cpp"

)

SET (platform_SRC
"game/src/platform/linux/DataImpl.cpp"
)

# linxu specific code
target_sources("goblins-lot" PRIVATE
    "game/src/platform/unix/main.cpp"
)

target_sources("goblins-lot" PRIVATE ${main_SRC} ${data_SRC} ${scripting_SRC} ${libtcod_SRC} ${UI_SRC} ${tileRenderer_SRC} ${platform_SRC})


include_directories("goblins-lot" "game/include")
include_directories("goblins-lot" "vendor/python-modules")

# FIXME This is not recomended (see note here: https://cmake.org/cmake/help/latest/command/file.html#filesystem)
# Better find some other way. For example list them explicitly
file(GLOB_RECURSE game_headers CONFIGURE_DEPENDS "game/include/*.hpp")
target_sources("goblins-lot" PRIVATE ${game_headers})

target_compile_definitions("goblins-lot" PRIVATE GCAMP_USE_THREADS=$<BOOL:${USE_THREADS}>)
target_compile_definitions("goblins-lot" PRIVATE GCAMP_VERSION=\"${GCAMP_VERSION}\")
target_compile_definitions("goblins-lot" PRIVATE GCAMP_VERSION_IS_RELEASE=$<BOOL:${GCAMP_VERSION_IS_RELEASE}>)

target_link_libraries("goblins-lot"
  ${SDL2_LIBRARY}
  ${SDL2_IMAGE_LIBRARY}
  ${PYTHON_LIBRARIES}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SERIALIZATION_LIBRARY}
  ${Boost_IOSTREAMS_LIBRARY}
  ${ZLIB_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${libtcod_LIBRARIES}
)

# Explciitly include header-only Boost libraries for the configuration provider
target_include_directories("goblins-lot" PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries("goblins-lot" ${Boost_PYTHON3_LIBRARY})

INSTALL(TARGETS "goblins-lot" RUNTIME DESTINATION ${GOBLIN_CAMP_BINDIR})
