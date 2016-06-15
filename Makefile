NEW_ROOT=/tmp/myroot

CFLAGS= -std=c99 -D_GNU_SOURCE -DNEW_ROOT=\"$(NEW_ROOT)\"

show_simple_filedes: create_root simple_filedes
	@echo -e "\n\n----------- SIMPLE EXAMPLE FILEDES ---------------------------------\n"
	sudo ./simple_filedes

show_simple_current_dir: create_root simple_current_dir
	@echo -e "\n\n----------- SIMPLE EXAMPLE CURRENT DIR -----------------------------\n"
	sudo ./simple_current_dir

show_vulnerability: create_root vulnerable
	@echo -e "\n\n----------- VULNERABILITY EXAMPLE ---------------------------------\n"
	sudo ./vulnerable

########################################################################

simple_filedes: temporary_chroot.o ls_root.o simple_filedes.o
	$(CC) $(CFLAGS) $^ -o $@

simple_current_dir: temporary_chroot.o ls_root.o simple_current_dir.o
	$(CC) $(CFLAGS) $^ -o $@

vulnerable: vulnerable_program.o 
	$(CC) -ldl -Wall -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

ls_root_pic.o: ls_root.c
	$(CC) -fPIC $(CFLAGS) -c -o $@ $<
	
libevil.o: libevil.c
	$(CC) -fPIC $(CFLAGS) -c -o $@ $<

libevil.so: libevil.o ls_root_pic.o
	$(CC) -shared -o $@ $^

create_root: libevil.so
	mkdir -p $(NEW_ROOT)/usr/lib
	touch $(NEW_ROOT)/new_root_file_1
	touch $(NEW_ROOT)/new_root_file_2
	cp libevil.so $(NEW_ROOT)/usr/lib/libevil.so
	
clean:
	rm -rf $(NEW_ROOT)
	rm -f ./*.o ./vulnerable ./simple_filedes ./simple_current_dir ./*.so
