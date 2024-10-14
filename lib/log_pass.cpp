#include <llvm-14/llvm/IR/DerivedTypes.h>
#include <llvm-14/llvm/Transforms/Utils/ModuleUtils.h>
#include <iostream>

#include "llvm/Pass.h"

#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/DerivedTypes.h"

#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"

#include "llvm/Transforms/Utils/ModuleUtils.h"

using namespace llvm;

namespace {
    struct LogPass final : public PassInfoMixin<LogPass> {
        PreservedAnalyses run(Module &module, ModuleAnalysisManager &module_analysis_manager) {
            LLVMContext &llvm_context = module.getContext();
            IRBuilder<>  builder(llvm_context);

            Type *llvm_void_t = Type::getVoidTy(llvm_context);
            Type *llvm_str_t  = Type::getInt8PtrTy(llvm_context);

            FunctionType  *log_init_function_t = FunctionType::get(llvm_void_t, false);
            FunctionCallee log_init_function   = module.getOrInsertFunction(log_init_function_name, log_init_function_t);

            FunctionType  *log_call_function_t = FunctionType::get(llvm_void_t, {llvm_str_t}, false);
            FunctionCallee log_call_function   = module.getOrInsertFunction(log_call_function_name, log_call_function_t);

            FunctionType *log_deinit_function_t = FunctionType::get(llvm_void_t, false);
            Function     *log_deinit_function =
                Function::Create(log_deinit_function_t, Function::ExternalLinkage, log_deinit_function_name, module);
            appendToGlobalDtors(module, log_deinit_function, 0);

            for (auto &function : module) {
                std::string function_name = function.getName().str();

                if (function.isDeclaration())
                    continue;

                std::cout << "Instrumenting: `" << function_name << "`\n";

                auto &first_instruction = *function.getEntryBlock().getFirstInsertionPt();
                builder.SetInsertPoint(&first_instruction);

                if (function_name == "main")
                    builder.CreateCall(log_init_function);

                else {
                    Value *function_name_value = builder.CreateGlobalStringPtr(function_name.c_str());
                    builder.CreateCall(log_call_function, {function_name_value});
                }
            }

            return PreservedAnalyses::all();
        }

    private:
        const std::string log_init_function_name   = "log_function_init";
        const std::string log_call_function_name   = "log_function_call";
        const std::string log_deinit_function_name = "log_function_deinit";
    };
}  // end of anonymous namespace

extern "C" PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "Log-Pass", "v1.0", [](PassBuilder &PB) {
            PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM, OptimizationLevel O0) { MPM.addPass(LogPass()); });
        }};
}
