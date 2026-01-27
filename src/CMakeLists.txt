cmake_minimum_required(VERSION 3.16)

# wild card.
file(GLOB_RECURSE LIB_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/module/audio/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/module/clicker/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/module/timer/*.cpp"
)

qt_add_library(${LIB_NAME}
    STATIC
    ${LIB_SRC}
)

target_include_directories(${LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
