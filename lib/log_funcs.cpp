#include <iostream>

extern "C" void log_function_init() { std::cout << "~~LOG~INIT~~" << std::endl; }

extern "C" void log_function_call(char *function) { std::cout << "~~LOG~CALL~~: `" << function << "`" << std::endl; }

extern "C" void log_function_deinit() { std::cout << "~~LOG~DEINIT~~" << std::endl; }
