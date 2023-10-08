include(ExternalProject)

ExternalProject_Add(
    yamlcpp_build
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG 0.8.0
    # URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/0.8.0.tar.gz
    # URL_HASH SHA1=3d2184792ce0749ca8efaa7c4b01f6333125b411
    UPDATE_COMMAND ""
    CMAKE_ARGS
        -DYAML_BUILD_SHARED_LIBS=OFF
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
    BUILD_BYPRODUCTS
        <INSTALL_DIR>/lib/libyaml-cpp.a
)

ExternalProject_Get_Property(yamlcpp_build install_dir)
file(MAKE_DIRECTORY "${install_dir}/include")

# message(${install_dir})
add_library(yamlcpp STATIC IMPORTED GLOBAL)
add_dependencies(yamlcpp yamlcpp_build)
set_target_properties(yamlcpp PROPERTIES
    IMPORTED_LOCATION "${install_dir}/lib/libyaml-cpp.a"
    INTERFACE_INCLUDE_DIRECTORIES "${install_dir}/include"
)