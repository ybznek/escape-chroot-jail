#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

typedef void (*func_ptr)(void);

int main(int argc, char* argv[]) {

	int file_des = open("/", O_RDONLY);

	chdir(NEW_ROOT);
	chroot(NEW_ROOT);

		// Load evil library from new root
		void *handle = dlopen("libevil.so", RTLD_LAZY);

		func_ptr f = (func_ptr)dlsym(handle, "action");

		// Run library code
		f();

	dlclose(handle);
	close(file_des);
	return 0;
}
