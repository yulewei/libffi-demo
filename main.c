#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <ffi.h>

int main() {
    void *lib_handle;
    int (*funcp)(void);

    ffi_cif cif;
    ffi_type *args[1];
    void *values[1];
    char *s;
    ffi_arg rc;

    // 加载 libc，并定位 getpid 的地址
    lib_handle = dlopen("libc.dylib", RTLD_LAZY);
    if (lib_handle == NULL)
        return -1;
    funcp = (void (*)(void)) dlsym(lib_handle, "getpid");

    // ffi 调用
    args[0] = &ffi_type_pointer;
    values[0] = &s;
    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint, args) == FFI_OK) {
        ffi_call(&cif, funcp, &rc, values);
        printf("%d\n", rc);
    }

    printf("%d\n", (*funcp)());    

    // 直接调用
    printf("%d\n", getpid());
    return 0;
}