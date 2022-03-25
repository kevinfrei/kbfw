for /F "usebackq" %%D in `git ls-files *.cpp *.ino testing/*.cpp *.h */*.h testing/*/*.h` do clang-format -i %%~D
