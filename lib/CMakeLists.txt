add_library(log_pass MODULE
    log_pass.cpp
)

target_compile_features(log_pass PRIVATE cxx_range_for cxx_auto_type)

set_target_properties(log_pass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

add_library(log_funcs.o OBJECT 
    log_funcs.cpp
)

# Special thanks to Dkay7

add_custom_command(TARGET OUTPUT "${CMAKE_BINARY_DIR}/log_funcs.o"
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_OBJECTS:log_funcs.o>" "${CMAKE_BINARY_DIR}/log_funcs.o"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/log_funcs.cpp"
)

add_custom_target(log_funcs ALL 
    DEPENDS "${CMAKE_BINARY_DIR}/log_funcs.o"
)
