#include <fstream>
#include <iostream>

class LoggerSingleton {
private:
    std::ofstream output;

    static LoggerSingleton instance;
    LoggerSingleton() {}

public:
    LoggerSingleton(const LoggerSingleton &)            = delete;
    LoggerSingleton &operator=(const LoggerSingleton &) = delete;

    static LoggerSingleton &get_instance() { return instance; }
    std::ofstream          &get_output() { return output; }
};

LoggerSingleton LoggerSingleton::instance;

extern "C" void log_function_init() {
    LoggerSingleton &logger = LoggerSingleton::get_instance();

    std::ofstream &output = logger.get_output();
    output.open("logger.log", std::ios_base::app);

    output << "main" << std::endl;
}

extern "C" void log_function_call(char *function) {  // TODO[flops]: Add const qualifier
    LoggerSingleton &logger = LoggerSingleton::get_instance();

    std::ofstream &output = logger.get_output();
    output << function << std::endl;  // Force flush
}

extern "C" void log_function_deinit() {
    LoggerSingleton &logger = LoggerSingleton::get_instance();

    std::ofstream &output = logger.get_output();
    output.close();
}
