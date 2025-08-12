# Fast LSP
A fast light-weight, compilation free LSP server for C and C++ workspace. Mainly designed for NeoVim.

## Project Setup
1. Clone the repository
   ```
    git clone git@github.com:ashikur-rahman-fh/fast_lsp.git
   ```
2. Update the submodule
   ```
    git submodule update --init --recursive
   ```

## Build
### Requirement
- cmake
- ninja-build

### Build Script
```
./build.sh

# ./build.sh -h for more info
```

Binary after build found under `target/fast_lsp`.  
Entrypoint of the program is `fast_lsp.cpp`
