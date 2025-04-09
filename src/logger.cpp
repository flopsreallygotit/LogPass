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

std::string get_compiler(std::string &callee_name, bool use_cxx_version) {
    std::string compiler_path     = use_cxx_version ? CXX_PATH : CC_PATH;
    char       *env_compiler_path = use_cxx_version ? getenv("LOGGER_CXX") : getenv("LOGGER_CC");

    if (env_compiler_path)
        compiler_path = env_compiler_path;  // User always right

    if (access(compiler_path.c_str(), F_OK) == -1)  // Maybe not always...
        return "";

    return compiler_path;
}

int add_logger_deps(std::string &command, bool use_cxx_version) {  // Real compiler will check existence of libs by itself
    std::string pass_plugin {LOG_PASS_PATH};
    std::string log_funcs_lib {LOG_FUNCS_PATH};

    if (pass_plugin.empty() || log_funcs_lib.empty())
        return -1;

    command += " -fpass-plugin=" + pass_plugin + " ";
    command += log_funcs_lib;

    if (!use_cxx_version)  // In C-mode we need to tell compiler to link cpp lib for log_funcs
        command += " -lstdc++";

    return 0;
}

int main(int argc, char *argv[]) {
    std::string callee_name {argv[0]};
    bool        use_cxx_version {callee_name.contains("cxx")};

    std::string command = get_compiler(callee_name, use_cxx_version);

    if (command.empty()) {
        std::cerr << "Can't find compiler!\n";

        return -1;
    }

    for (int arg_idx = 1; arg_idx < argc; ++arg_idx) {
        command += " ";
        command += argv[arg_idx];
    }

    if (add_logger_deps(command, use_cxx_version)) {
        std::cerr << "Wrong logger dependencies!\n";

        return -1;
    }

    int result = system(command.c_str());
    if (WIFEXITED(result))
        return WEXITSTATUS(result);

    return result;
}
