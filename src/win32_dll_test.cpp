#include <Windows.h>

// for making easy the declaration of a pointer
#define DLLFUNC(name) void name(int value)
typedef DLLFUNC(dll_func);
// an aux do nothing method matching
// the signature of the dll function
DLLFUNC(dll_funcStub)
{}

const char *dllName = "Dummy.dll";
struct DllCode
{
    bool valid;
    HMODULE dllHandle;
    dll_func *funcPtr;
};

DllCode LoadDll()
{
    DllCode code = {};
    code.dllHandle = LoadLibraryA(dllName);
    if( code.dllHandle != NULL )
    {
        // else couldn't load the library
        code.funcPtr = (dll_func*)GetProcAddress(code.dllHandle, "dllFunc");
        code.valid = code.funcPtr != NULL;
    }

    if( !code.valid )
    {
        // we ensure that we can always call to this function
        code.funcPtr = dll_funcStub;
    }
    return(code);
}

void UnloadDll(DllCode *code)
{
    if( code->valid )
    {
        code->funcPtr = dll_funcStub;
        FreeLibrary(code->dllHandle);
    }
}

int main(int argc, char **argv)
{
    // always same seed to ensure same sequence
    srand(1);

    DllCode code;
    while(true)
    {
        // load at start
        code = LoadDll();
        // each second we call to the dll
        code.funcPtr( rand()%10 );
        // unload at end
        UnloadDll(&code);
        // in this time frame we could replace the dll
        Sleep(1000);
    }
}