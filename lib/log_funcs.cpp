#include <fstream>
#include <iostream>

class LoggerSingleton {  // TODO[flops]: Add summary
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

template<typename T>
LoggerSingleton &operator<<(LoggerSingleton &logger, T &val) {
    std::ofstream &output = logger.get_output();

    if (output.is_open()) {
        output << val << '\n';
        output.flush();
    }

    else
        std::cerr << val << '\n';

    return logger;
}

LoggerSingleton LoggerSingleton::instance;

extern "C" void log_function_init() {
    LoggerSingleton &logger = LoggerSingleton::get_instance();

    std::ofstream &output = logger.get_output();
    output.open("logger.log", std::ios_base::app);
}

extern "C" void log_function_call(const char *function) {
    LoggerSingleton &logger = LoggerSingleton::get_instance();

    logger << function;
}

extern "C" void log_function_deinit() {
    LoggerSingleton &logger = LoggerSingleton::get_instance();

    std::ofstream &output = logger.get_output();
    output.close();
}
