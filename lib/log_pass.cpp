#include <llvm/Pass.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/DebugLoc.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

using namespace llvm;

namespace {

    static void make_function_log(Function &function, raw_fd_ostream &logfile) { // TODO Why isn't it a member of pass class?
        auto module_name = function.getParent()->getName(); // TODO unnecessary copy ctor. Pls don't use `auto`, use `auto&`

        function.getAttributes().print(logfile); // TODO There's function.dump() method)
        function.getFunctionType()->print(logfile);
        logfile << ' ' << function.getName() << " (" << module_name << "): {\n";

        for (auto &basic_block : function) { 
            logfile << "\tBasic block: " << &basic_block << " [\n";

            for (auto &instruction : basic_block) {
                DebugLoc debug_location = instruction.getDebugLoc(); // TODO unnecessary copy-ctor.

                if (debug_location)
                    logfile << "\n\t\tLocation: " << module_name << ':' << debug_location.getLine() << '\n';

                logfile << "\t\tInstruction: ";
                instruction.print(logfile); //TODO: There's .dump() method
                logfile << '\n';
            }

            logfile << "\t]\n\n";
        }

        logfile << "}\n\n";
    }
                                    // TODO: no final modifier
    struct FunctionLogPass : public FunctionPass { // TODO: You should NEVER use Function, Module, Loop and other depricated pass classes.
                                                   // They've been depricated for several years. Use new pass manager as documentations describes.
    public:
        static char ID; // TODO It looks like something that should not be public

        FunctionLogPass(): FunctionPass(ID), logfile("pass.log", logfile_error, sys::fs::OpenFlags::OF_Append) {
            if (logfile.has_error())
                errs() << logfile.error().message() << '\n';
        }

        bool runOnFunction(Function &function) override {
            if (function.isDeclaration())
                return false;

            make_function_log(function, logfile); // TODO Poor name. Are you making any function here?

            return false;
        }

        void getAnalysisUsage(AnalysisUsage &analysis_usage) const override { analysis_usage.setPreservesAll(); }

    private:
        raw_fd_ostream  logfile; // It's usually better not to use llvm's stdlib bc its as unstable as llvm is))
        std::error_code logfile_error;
    };

}  // namespace

char FunctionLogPass::ID = 0;
static void registerFunctionLogPassPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) { //TODO: old pass manager is depricated
//                                                                  ^^^^^^^^
//                                                          TODO:   It's even in LEGACY namespace
PM.add(new FunctionLogPass());
}

static RegisterStandardPasses RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerFunctionLogPassPass);
