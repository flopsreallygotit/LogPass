set(LOG_PASS_PATH_DEF  "${CMAKE_BINARY_DIR}/lib/lib${LOG_PASS_NAME}.so")
set(LOG_FUNCS_PATH_DEF "${CMAKE_BINARY_DIR}/lib/lib${LOG_FUNCS_NAME}.a")

# TODO[flops]: Add normal depenedencies system

add_executable(loggercc
    logger.cpp
)

target_compile_definitions(loggercc PRIVATE 
    CC_PATH="${CMAKE_C_COMPILER}" LOG_PASS_PATH="${LOG_PASS_PATH_DEF}" LOG_FUNCS_PATH="${LOG_FUNCS_PATH_DEF}"
)

add_executable(loggercxx
    logger.cpp
)

target_compile_definitions(loggercxx PRIVATE 
    CXX_PATH="${CMAKE_CXX_COMPILER}" LOG_PASS_PATH="${LOG_PASS_PATH_DEF}" LOG_FUNCS_PATH="${LOG_FUNCS_PATH_DEF}"
)
