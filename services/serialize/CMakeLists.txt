# add target library
qt_add_library(${SERIAL}
    STATIC
    ./include/i_serializable.h
    ./include/serializer.h
)

# add target include directories to Serialize library.
target_include_directories(${SERIAL}
    PUBLIC
    ./include/
)

# link library to this target.
target_link_libraries(${SERIAL}
    PRIVATE
        Qt6::Core
)
