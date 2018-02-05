#include <stdio.h>
#include <ffi.h>
#include <alloca.h>
#include <stdlib.h>

void closure_func(ffi_cif *cif, void *ret, void **args, void *user_data) {
    int a = *(int *) args[0];
    int b = *(int *) args[1];
    *(ffi_arg *) ret = sum(a, b);
}

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
    ffi_type **arg_types = (ffi_type **) alloca(arg_count * sizeof(ffi_type *));
    void **arg_values = (void **) alloca(arg_count * sizeof(void *));
    int *values = (int *) alloca(arg_count * sizeof(int));
    int return_value = -1;

    void *code;
    ffi_closure *closure = ffi_closure_alloc(sizeof(ffi_closure), &code);
    if (!closure) return -1;

    for (int i = 0; i < arg_count; i++) {
        arg_types[i] = &ffi_type_sint;
        values[i] = atoi(argv[i + 1]);
        arg_values[i] = &values[i];
    }

    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, arg_count, &ffi_type_sint, arg_types) == FFI_OK) {
        // FFI 方式调用
        ffi_call(&cif, fn, &return_value, arg_values);
        printf("%d\n", return_value);

        // FFI 闭包方式调用
        if (ffi_prep_closure_loc(closure, &cif, closure_func, NULL, code) == FFI_OK) {
            ffi_call(&cif, code, &return_value, arg_values);
            printf("%d\n", return_value);
        }
    }
    ffi_closure_free(closure);
    return 0;
}