#include <iostream>

// #include <nlohmann/json.hpp>

// nlohmann::json json_data;
// std::fstream   of_file;

extern "C" void log_function_init() { std::cout << "~~LOG INIT~~" << std::endl; }

// extern "C" void log_function_call(const char *filename, const char *function, const int line) {
//     std::cout << "[LOGGER]: Right now at: " << filename << ":" << line << "\n";
// }

extern "C" void log_function_call(char *function) { std::cout << "~~LOG CALL~~: `" << function << "`" << std::endl; }
