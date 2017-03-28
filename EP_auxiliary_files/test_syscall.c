#include<stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

#define TEST_SYSCALL_NO 336

int main() {

	printf("Calling sys_test_syscall. Returned %x\n", (unsigned int) syscall(TEST_SYSCALL_NO));
	return 0;

}
