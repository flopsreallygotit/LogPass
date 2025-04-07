add_library(${LOG_PASS_NAME} MODULE
    log_pass.cpp
)

target_compile_features(${LOG_PASS_NAME} PRIVATE cxx_range_for cxx_auto_type)

set_target_properties(${LOG_PASS_NAME} PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

add_library(${LOG_FUNCS_NAME} STATIC 
    log_funcs.cpp
)
