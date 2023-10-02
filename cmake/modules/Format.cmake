# ClangFormat
# ===========
# 
# This program runs clang-format on all the cpp files in the given directory
#

function(FORMATDIR target directory)
    find_program(CLANG-FORMAT_EXE 
        NAMES clang-format clang-format-10 clang-format-11
        clang-format-12 clang-format-13 clang-format-14
        REQUIRED
    )
    set(EXPRESSION h hpp hh c cc cxx cpp c)
    list(TRANSFORM EXPRESSION PREPEND "${directory}/*.")
    file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
        LIST_DIRECTORIES false ${EXPRESSION}
    )
    add_custom_command(TARGET ${target} PRE_BUILD COMMAND
        ${CLANG-FORMAT_EXE} -i --style=file ${SOURCE_FILES}
    )
endfunction()
