#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "temporary_chroot.h"

int temporary_chroot(const char* new_root) {
	int fildes = open("/", O_RDONLY);
	chdir(new_root);
	chroot(new_root);
	return fildes;
}

void temporary_chroot_escape(int fildes) {
	fchdir(fildes);
	chroot(".");
	
	close(fildes);
}

