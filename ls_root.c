#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

#include "ls_root.h"

void ls_root() {

 	DIR* dp = opendir("/");
	if (dp == NULL) {
		return;
	}

	struct dirent *ent;
	for (int i = 0; i < 5 && (ent = readdir(dp)); ++i) {
		if (i >= 2) {
			printf("- %s\n",ent->d_name);
		}
    }

	closedir(dp);
   
}
