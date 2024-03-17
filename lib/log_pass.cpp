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

    static void make_function_log(Function &function, raw_fd_ostream &logfile) {
        auto module_name = function.getParent()->getName();

        function.getAttributes().print(logfile);
        function.getFunctionType()->print(logfile);
        logfile << ' ' << function.getName() << " (" << module_name << "): {\n";

        for (auto &basic_block : function) {
            logfile << "\tBasic block: " << &basic_block << " [\n";

            for (auto &instruction : basic_block) {
                DebugLoc debug_location = instruction.getDebugLoc();
                if (debug_location)
                    logfile << "\n\t\tLocation: " << module_name << ':' << debug_location.getLine() << '\n';

                logfile << "\t\tInstruction: ";
                instruction.print(logfile);
                logfile << '\n';
            }

            logfile << "\t]\n\n";
        }

        logfile << "}\n\n";
    }

    struct FunctionLogPass : public FunctionPass {
    public:
        static char ID;

        FunctionLogPass(): FunctionPass(ID), logfile("pass.log", logfile_error, sys::fs::OpenFlags::OF_Append) {
            if (logfile.has_error())
                errs() << logfile.error().message() << '\n';
        }

        bool runOnFunction(Function &function) override {
            if (function.isDeclaration())
                return false;

            make_function_log(function, logfile);

            return false;
        }

        void getAnalysisUsage(AnalysisUsage &analysis_usage) const override { analysis_usage.setPreservesAll(); }

    private:
        raw_fd_ostream  logfile;
        std::error_code logfile_error;
    };

}  // namespace

char FunctionLogPass::ID = 0;

static void registerFunctionLogPassPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
    PM.add(new FunctionLogPass());
}

static RegisterStandardPasses RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerFunctionLogPassPass);
