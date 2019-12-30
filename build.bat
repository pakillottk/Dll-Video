@echo off

call ".\shell.bat"
:: Debug flags
:: set compiler_flags=/Zi /D_DEBUG /Od
:: Release flags
set compiler_flags=/O2

pushd ".\build"
    :: Compile a DLL called Dummy.dll
    cl %compiler_flags% /D_USRDLL /D_WINDLL ..\src\dll.cpp /link /DLL /EXPORT:dllFunc /OUT:Dummy.dll 

    :: Compile a .exe file linked to the dll
    cl %compiler_flags% ..\src\win32_dll_test.cpp Dummy.lib
popd