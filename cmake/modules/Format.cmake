# ClangFormat
# ===========
# 
# This program runs clang-format on all the cpp files in the given directory
#

function(FORMATDIR target directory)
    find_program(CLANG-FORMAT_EXE 
        NAMES clang-format-15 clang-format
        REQUIRED
    )
    message(STATUS "clang-format=${CLANG-FORMAT_EXE}")
    set(EXPRESSION h hpp hh c cc cxx cpp c)
    list(TRANSFORM EXPRESSION PREPEND "${directory}/*.")
    file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
        LIST_DIRECTORIES false ${EXPRESSION}
    )
    add_custom_command(TARGET ${target} PRE_BUILD COMMAND
        ${CLANG-FORMAT_EXE} -i --style=file ${SOURCE_FILES}
    )
endfunction()
