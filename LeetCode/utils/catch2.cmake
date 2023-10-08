include(ExternalProject)

ExternalProject_Add(
    catch2_build
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
    UPDATE_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE:STRING=Release
        -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    BUILD_BYPRODUCTS
        <INSTALL_DIR>/lib/libCatch2.a
)

ExternalProject_Get_Property(catch2_build install_dir)
file(MAKE_DIRECTORY "${install_dir}/include")

# message(${install_dir})
add_library(catch2 STATIC IMPORTED GLOBAL)
add_dependencies(catch2 catch2_build)
set_target_properties(catch2 PROPERTIES
    IMPORTED_LOCATION "${install_dir}/lib/libCatch2.a"
    INTERFACE_INCLUDE_DIRECTORIES "${install_dir}/include"
)
