#include "llvm/Pass.h"

#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/DerivedTypes.h"

#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"

#include "llvm/Transforms/Utils/ModuleUtils.h"

#if LLVM_VERSION_MAJOR < 17
    #include "llvm/InitializePasses.h"
#endif

namespace {
    using namespace llvm;

    struct LogPass final : public PassInfoMixin<LogPass> {
        using func_set_t = std::set<Function *>;

        void add_ctors_deps(Function *ctor, func_set_t &global_ctors) {
            for (BasicBlock &basic_block : *ctor) {
                for (Instruction &instr : basic_block) {
                    CallInst *call_instr = dyn_cast<CallInst>(&instr);

                    if (!call_instr)
                        continue;

                    global_ctors.insert(call_instr->getCalledFunction());
                }
            }
        }

        func_set_t get_global_ctors(Module *module) {
            func_set_t global_ctors = {};

            GlobalVariable *ctors_var = module->getGlobalVariable("llvm.global_ctors");

            if (!ctors_var)
                return global_ctors;  // No constructors in this module

            ConstantArray *constant_array = llvm::dyn_cast<llvm::ConstantArray>(ctors_var->getInitializer());
            if (!constant_array)
                return global_ctors;

            for (unsigned int i = 0; i < constant_array->getNumOperands(); ++i) {
                llvm::ConstantStruct *constant_struct = llvm::dyn_cast<llvm::ConstantStruct>(constant_array->getOperand(i));

                if (!constant_struct || constant_struct->getNumOperands() < 2)
                    continue;

                llvm::Function *ctor = llvm::dyn_cast<llvm::Function>(constant_struct->getOperand(1)->stripPointerCasts());

                if (!ctor)
                    continue;

                global_ctors.insert(ctor);
                add_ctors_deps(ctor, global_ctors);
            }

            return global_ctors;
        }

        PreservedAnalyses run(Module &module, ModuleAnalysisManager &module_analysis_manager) {
            LLVMContext &llvm_context = module.getContext();
            IRBuilder<>  builder(llvm_context);

            Type *llvm_void_t = Type::getVoidTy(llvm_context);
#if LLVM_VERSION_MAJOR < 16
            Type *llvm_str_t = Type::getInt8PtrTy(llvm_context);
#else
            Type *llvm_str_t = builder.getPtrTy();
#endif

            FunctionCallee log_init_function = module.getOrInsertFunction(log_init_function_name, llvm_void_t);
            FunctionCallee log_call_function = module.getOrInsertFunction(log_call_function_name, llvm_void_t, llvm_str_t);

            FunctionType *log_deinit_function_t = FunctionType::get(llvm_void_t, false);
            Function     *log_deinit_function =
                Function::Create(log_deinit_function_t, Function::ExternalLinkage, log_deinit_function_name, module);
            appendToGlobalDtors(module, log_deinit_function, 0);

            func_set_t global_ctors = get_global_ctors(&module);

            for (auto &function : module) {
                if (function.isDeclaration() || global_ctors.contains(&function))
                    continue;

                BasicBlock  &entry_bb          = function.getEntryBlock();
                Instruction &first_instruction = *entry_bb.getFirstInsertionPt();
                builder.SetInsertPoint(&first_instruction);

                std::string function_name = function.getName().str();

                if (function_name == "main") {
                    errs() << "Inserting logger init in main...\n";
                    builder.CreateCall(log_init_function);
                }

                errs() << "Inserting logger call in " << function_name << "...\n";
                Value *function_name_value = builder.CreateGlobalStringPtr(function_name.c_str());
                builder.CreateCall(log_call_function, {function_name_value});
            }

            return PreservedAnalyses::all();
        }

    private:
        const std::string log_init_function_name   = "log_function_init";
        const std::string log_call_function_name   = "log_function_call";
        const std::string log_deinit_function_name = "log_function_deinit";
    };
}  // end of anonymous namespace

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "LogPass", "v0.3",
        /* lambda to insert our pass into the pass pipeline. */
        [](PassBuilder &PB) {
            PB.registerOptimizerLastEPCallback([](ModulePassManager &MPM, OptimizationLevel OL) { MPM.addPass(LogPass()); });
        }};
}
