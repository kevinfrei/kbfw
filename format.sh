#!/bin/sh
git ls-files | grep -E '\.(h|hpp|c|cpp|ino)$' | xargs clang-format -i
git ls-files | grep -E '\.(js|md|html)$' | xargs npx prettier -w