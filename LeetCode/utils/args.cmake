include(ExternalProject)

ExternalProject_Add(
    args_build
    GIT_REPOSITORY https://github.com/Taywee/args.git
    GIT_TAG 6.4.6
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(args_build source_dir)

add_library(args INTERFACE)
add_dependencies(args args_build)
set_target_properties(args PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${source_dir}"
)
message("source_dir = ${source_dir}")