#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ffi.h>

int sum(int a, int b) {
    return a + b;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        return -1;
    }

    ffi_cif cif;
    int arg_count = argc - 1;
    void *fn = &sum;  // 函数地址
    ffi_type *return_type = &ffi_type_sint;
    ffi_type **arg_types = (ffi_type **) alloca(arg_count * sizeof(ffi_type *));
    void **arg_values = (void **) alloca(arg_count * sizeof(void *));
    int *values = (int *) alloca(arg_count * sizeof(int));
    int return_value = -1;

    for (int i = 0; i < arg_count; i++) {
        arg_types[i] = &ffi_type_sint;
        values[i] = atoi(argv[i + 1]);
        arg_values[i] = &values[i];
    }

    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, arg_count, return_type, arg_types) == FFI_OK) {
        ffi_call(&cif, fn, &return_value, arg_values);
        printf("%d\n", return_value);
    }

    return EXIT_SUCCESS;
}