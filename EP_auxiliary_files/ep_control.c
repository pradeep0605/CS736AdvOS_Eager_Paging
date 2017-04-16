#include<stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>

#define LIST_EP_APPS 336
#define CLEAR_EP_APPS_LIST 337

int main(int argc, char **argv) {

	if (argc < 2) {
		printf("Usage: ./ep_control [--list | --clear]\n");
		return 0;
	}
	
	if (strcmp(argv[1], "--list") == 0) {
		printf("Calling sys_list_ep_apps syscall. Returned %x\n",
			(unsigned int) syscall(LIST_EP_APPS));
	} else if (strcmp(argv[1], "--clear") == 0) {
		printf("Calling sys_clear_ep_list syscall. Returned %x\n",
			(unsigned int) syscall(CLEAR_EP_APPS_LIST));
	} else {
		printf("Invalid argument %s\n", argv[1]);
	}
	
	return 0;

}
