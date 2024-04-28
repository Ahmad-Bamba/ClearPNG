# CppCheck
# =========
# 
# Adds running cppcheck to a target if enabled.
#

function(ADDCPPCHECK target)
    find_program(CPPCHECK_EXE 
        NAMES cppcheck
        REQUIRED
    )
    message(STATUS "cppcheck=${CPPCHECK_EXE}")
    set_target_properties(${target}
        PROPERTIES CXX_CPPCHECK "${CPPCHECK_EXE};"
    )
endfunction()
