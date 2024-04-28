# ClangTidy
# =========
# 
# Adds running clang-tidy to a target if enabled.
#

function(ADDCLANGTIDY target)
    find_program(CLANG-TIDY_EXE 
        NAMES clang-tidy clang-tidy-10 clang-tidy-11
        clang-tidy-12 clang-tidy-13 clang-tidy-14
        REQUIRED
    )
    message(STATUS "clang-tidy=${CLANG-TIDY_EXE}")
    if(TIDY_EXTRA)
        set_target_properties(${target}
            PROPERTIES CXX_CLANG_TIDY
            "${CLANG-TIDY_EXE};--config-file=${PROJECT_SOURCE_DIR}/extra.clang-tidy"
        )
    else()
        set_target_properties(${target}
            PROPERTIES CXX_CLANG_TIDY "${CLANG-TIDY_EXE};"
        )
    endif()
endfunction()
