#include<stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

int main()
{
	int n = 100;
	int k = 1;
	int * ptr = NULL;
	/*
	int *ptr = mmap(NULL, n, PROT_READ | PROT_WRITE, MAP_PRIVATE |
	MAP_ANONYMOUS, -1, 0);
	*/

	while (k--) {
		scanf("%d", &n);
		ptr = malloc(n * sizeof(int));

		int i = 0;
		for(i = 0; i < n; ++i)
			ptr[i] = i;
	}
	printf("Returned address %p\n", ptr);
	return 0;

}
