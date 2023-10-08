include(ExternalProject)

ExternalProject_Add(
    spdlog_build
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
    UPDATE_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE:STRING=Release
        -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
        -DSPDLOG_BUILD_SHARED:BOOL=OFF
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    BUILD_BYPRODUCTS
        <INSTALL_DIR>/lib/libspdlog.a
)

ExternalProject_Get_Property(spdlog_build install_dir)
file(MAKE_DIRECTORY "${install_dir}/include")

# message(${install_dir})
add_library(spdlog STATIC IMPORTED GLOBAL)
add_dependencies(spdlog spdlog_build)
set_target_properties(spdlog PROPERTIES
    IMPORTED_LOCATION "${install_dir}/lib/libspdlog.a"
    INTERFACE_INCLUDE_DIRECTORIES "${install_dir}/include"
)