default: ffidemo fficlosuredemo

CFLAGS = -g -I/usr/local/opt/libffi/lib/libffi-3.2.1/include  \
		-L/usr/local/opt/libffi/lib -lffi

ffidemo:
	gcc $(CFLAGS) main_ffi.c -o ffidemo

fficlosuredemo:
	gcc $(CFLAGS) main_closure.c -o fficlosuredemo

clean:
	rm ffidemo
	rm fficlosuredemo