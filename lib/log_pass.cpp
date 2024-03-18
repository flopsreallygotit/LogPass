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

    struct FunctionLogPass : public FunctionPass {  // TODO Version with new PM
    public:
        static char ID;

        FunctionLogPass(): FunctionPass(ID), logfile("pass.log", logfile_error, sys::fs::OpenFlags::OF_Append) {
            if (logfile.has_error())
                errs() << logfile.error().message() << '\n';
        }

        static void log_function_ir_info(Function &function, raw_fd_ostream &logfile) {
            auto &&module_name = function.getParent()->getName();

            function.getAttributes().print(logfile);
            function.getFunctionType()->print(logfile);
            logfile << ' ' << function.getName() << " (" << module_name << "): {\n";

            for (auto &basic_block : function) {
                logfile << "\tBasic block: " << &basic_block << " [\n";

                for (auto &instruction : basic_block) {
                    auto &debug_location = instruction.getDebugLoc();

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

        bool runOnFunction(Function &function) override final {
            if (function.isDeclaration())
                return false;

            log_function_ir_info(function, logfile);

            return false;
        }

        void getAnalysisUsage(AnalysisUsage &analysis_usage) const override final { analysis_usage.setPreservesAll(); }

    private:
        raw_fd_ostream  logfile;  // TODO Maybe use standart file stream instead of llvm's one, because of llvm instability
        std::error_code logfile_error;
    };

}  // namespace

char FunctionLogPass::ID = 0;

static void registerFunctionLogPassPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
    PM.add(new FunctionLogPass());
}

static RegisterStandardPasses RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerFunctionLogPassPass);
