#include <iostream>

extern "C" void log_function_init() { std::cerr << "~~LOG~INIT~~\n"; }

extern "C" void log_function_call(char *function) { std::cerr << "~~LOG~CALL~~: `" << function << "`\n"; }

extern "C" void log_function_deinit() { std::cerr << "~~LOG~DEINIT~~\n"; }
