set(LOG_PASS_PATH_DEF  "$<TARGET_FILE:log_pass>")
set(LOG_FUNCS_PATH_DEF "$<TARGET_FILE:log_funcs>")

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
