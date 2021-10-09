#include <Python.h>


/* 主函数入口，不需要改动 */

int main(int argc, char *argv[]) {
    Py_Initialize();
    if(!Py_IsInitialized()) {
        printf("failed to initialize python interpreter\n");
        return -1;
    }

    // Remember Py_Initialize() doesnt set sys.argv
    wchar_t* args[argc];
    for(int i = 0; i < argc; ++i) {
        args[i] = Py_DecodeLocale(argv[i], nullptr);
    }
    auto result = Py_Main(argc, args);
    if(result == 0) {
        printf("Py_Main exited successfully\n");
    } else {
        printf("Py_Main exited with error: %d\n", result);
    }

    for(auto&& mem : args) {
        PyMem_RawFree(mem);
    }
    Py_Finalize();
}
