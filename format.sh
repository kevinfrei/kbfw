#!/bin/sh
# Use clang-format for c/c++ files
git ls-files | grep -E '\.(h|hpp|c|cpp|ino)$' | xargs clang-format -i
# Use prettier for other stuff
git ls-files | grep -E '\.(js|md|html)$' | xargs npx prettier -w