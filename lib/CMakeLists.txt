add_library(log_pass MODULE
    log_pass.cpp
)

target_compile_features(log_pass PRIVATE cxx_range_for cxx_auto_type)

set_target_properties(log_pass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)
