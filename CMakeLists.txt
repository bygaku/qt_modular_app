cmake_minimum_required(VERSION 3.16)

project(Modular VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(TEST "Test Mode." OFF)
set(EXE_NAME "appModular")
set(TEST_NAME "appTest")
set(TODO "todo")
set(TIMER "timer")
set(NOTE "note")
set(CALCULATOR "calculator")
set(SERIAL "serialize")

add_subdirectory(services/)
add_subdirectory(modules/)

if(${TEST})
    add_subdirectory(test/)
else()
    add_subdirectory(app/)

    set_target_properties(${EXE_NAME} PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${EXE_NAME}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )

    include(GNUInstallDirs)
    install(TARGETS ${EXE_NAME}
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
