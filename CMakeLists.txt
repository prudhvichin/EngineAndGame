cmake_minimum_required(VERSION 3.27.7)

project(Spaceship_Warfare
	VERSION 1.0.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS       OFF)

# creates a variable. 
set(LIGHT_YEARS_ENGINE_TARGET_NAME Engine) 
set(LIGHT_YEARS_GAME_TARGET_NAME Game) 

add_subdirectory(Engine)
add_subdirectory(Game)