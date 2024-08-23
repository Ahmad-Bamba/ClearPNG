# ClangTidy
# =========
# 
# Adds running clang-tidy to a target if enabled.
#

function(ADDCLANGTIDY target)
    find_program(CLANG-TIDY_EXE 
        NAMES clang-tidy clang-tidy-18 clang-tidy-17
        clang-tidy-16 clang-tidy-15 clang-tidy-14
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
