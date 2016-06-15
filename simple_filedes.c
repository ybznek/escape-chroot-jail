#include <stdlib.h>
#include <stdio.h>

#include "temporary_chroot.h"
#include "ls_root.h"

int main() {
	printf("--- My root:\n");
	ls_root();


	int fildes = temporary_chroot(NEW_ROOT);
		printf("\n\n--- New root:\n");
		ls_root();
	temporary_chroot_escape(fildes);
	
	
	printf("\n\n--- My root, again:\n");
	ls_root();

	return 0;
}
