find_package (PkgConfig)

set (L-SYSTEM_REQUIRED
     sdl2
     libxml-2.0
    )

pkg_check_modules(L-SYSTEM REQUIRED ${L-SYSTEM_REQUIRED})

set (L-SYSTEM_LOADER_SRC
     LSystem.cpp
     main.cpp
     XMLParser.cpp
    )

set (L-SYSTEM_LOADER_HDR
     LSystem.h
     XMLParser.h
    )

include_directories (${L-SYSTEM_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})

add_executable (l-system ${L-SYSTEM_LOADER_SRC} ${L-SYSTEM_LOADER_HDR})

target_link_libraries (l-system ${L-SYSTEM_LIBRARIES} ${L-SYSTEM_LDFLAGS})
