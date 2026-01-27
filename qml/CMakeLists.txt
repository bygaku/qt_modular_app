cmake_minimum_required(VERSION 3.16)
file(GLOB_RECURSE QML_SRC RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/**/*.qml"
)

qt_add_qml_module(${EXE_NAME}
    URI Modular VERSION 1.0
    QML_FILES
    ${QML_SRC}
)
