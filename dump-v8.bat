@echo off
build\llvm\llvm\Debug\bin\clang.exe -x c++ v8\include\v8.h -fsyntax-only -Xclang -ast-dump=json 
