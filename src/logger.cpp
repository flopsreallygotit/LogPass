#include <cstdlib>
#include <iostream>

#include <unistd.h>

#ifndef CC_PATH
    #define CC_PATH ""
#endif

#ifndef CXX_PATH
    #define CXX_PATH ""
#endif

#ifndef LOG_PASS_PATH
    #define LOG_PASS_PATH ""
#endif

#ifndef LOG_FUNCS_PATH
    #define LOG_FUNCS_PATH ""
#endif

std::string get_compiler(std::string &callee_name) {
    if (callee_name.find("cxx") != std::string::npos)  // TODO[flops]: Add getenv, move to c++23
        return CXX_PATH;

    return CC_PATH;
}

int add_logger_deps(std::string &command) {
    std::string pass_plugin {LOG_PASS_PATH};
    std::string log_funcs_lib {LOG_FUNCS_PATH};

    if (pass_plugin.empty() || log_funcs_lib.empty())
        return -1;

    command += " -fpass-plugin=" + pass_plugin + " ";
    command += log_funcs_lib;

    return 0;
}

int main(int argc, char *argv[]) {
    std::string callee_name {argv[0]};
    std::string command = get_compiler(callee_name);

    if (command.empty()) {
        std::cerr << "Can't find compiler!\n";

        return -1;
    }

    for (int arg_idx = 1; arg_idx < argc; ++arg_idx) {
        command += " ";
        command += argv[arg_idx];
    }

    if (add_logger_deps(command)) {
        std::cerr << "Wrong logger dependencies!\n";

        return -1;
    }

    std::cerr << command << '\n';
    int result = system(command.c_str());

    if (WIFEXITED(result))
        return WEXITSTATUS(result);

    return result;
}
