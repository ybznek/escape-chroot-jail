#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "ls_root.h"

int main() {
	printf("--- My root:\n");
	ls_root();
	chdir("/");


	chroot(NEW_ROOT);
		printf("\n\n--- New root:\n");
		ls_root();
	chroot(".");
	
	printf("\n\n--- My root, again:\n");
	ls_root();

	return 0;
}
