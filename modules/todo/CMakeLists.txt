# add target library
qt_add_library(${TODO}
    STATIC
    ./include/task.h
    ./include/task_manager.h
    ./task_manager.cpp
)

# add target include directories to ToDo library.
target_include_directories(${TODO}
    PUBLIC
    ./include/
)

# link library to this target.
target_link_libraries(${TODO}
    PRIVATE
        Qt6::Core
        ${SERIAL}
)
