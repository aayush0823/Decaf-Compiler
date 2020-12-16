clang -emit-llvm -c -g inbuiltFunc.c
# llvm-nm decaf_lib.bc
llvm-link output.txt inbuiltFunc.bc -o outputFinal.minic
# rm decaf_lib.bc
# rm output.txt
# lli output_final.bc
echo "Done linking MiniC code"