#include <stdio.h>
#include <fcntl.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define LIST_EP_APPS 336
#define CLEAR_EP_APPS_LIST 337
#define CONTROL_EP 338
#define __NR_apriori_paging_alloc 333

int main(int argc, char **argv) {

	if (argc < 2) {
		printf("Usage: ./ep_control [--add | --list | --clear app_name |"
		" --clear-all | --ctrl #number ]\n");
		printf("--ctrl #number options: \n1) enabled stack dump (-1) for disabling ]\n");
		printf("2) enabled mmap prints (-2) for disabling ]\n");
		return 0;
	}
	
	if (strcmp(argv[1], "--add") == 0) {
	 	if (argc == 3) {
			syscall(__NR_apriori_paging_alloc, &argv[2], argc-2, 1);
		} else {
			printf("Invalid number of arguments for %s\n", argv[1]);
		}

	} else if (strcmp(argv[1], "--list") == 0) {
		printf("Calling sys_list_ep_apps syscall. Returned %x\n",
			(unsigned int) syscall(LIST_EP_APPS));
	} else if (strcmp(argv[1], "--clear-all") == 0) {
		printf("Calling sys_clear_ep_list syscall. Returned %x\n",
			(unsigned int) syscall(CLEAR_EP_APPS_LIST, NULL));
	} else if (strcmp(argv[1], "--clear") == 0) {
	 	if (argc == 3) {
			printf("Calling sys_clear_ep_list syscall. Returned %x\n",
				(unsigned int) syscall(CLEAR_EP_APPS_LIST, argv[2]));
		} else {
			printf("Invalid number of arguments for %s\n", argv[1]);
		}
	} else if (strcmp(argv[1], "--ctrl") == 0) {
		if (argc == 3) {
			int cmd = atoi(argv[2]);
			printf("Calling sys_clear_ep_list syscall. Returned %x\n",
				(unsigned int) syscall(CONTROL_EP, cmd));

		} else {
			printf("Invalid number of arguments for %s\n", argv[1]);
		}
	} else {
		printf("Invalid argument %s\n", argv[1]);
	}
	
	return 0;

}
