include(ExternalProject)

ExternalProject_Add(
    args_build
    GIT_REPOSITORY https://github.com/p-ranav/argparse
    GIT_TAG v2.9
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(args_build source_dir)

add_library(argparse INTERFACE)
add_dependencies(argparse args_build)
set_target_properties(argparse PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${source_dir}"
)
message("source_dir = ${source_dir}")