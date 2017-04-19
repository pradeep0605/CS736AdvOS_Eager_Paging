#ifndef __APRIORI_PAGING_ALLOC_H__
#define __APRIORI_PAGING_ALLOC_H__

#define MAX_PROC_NAME_LEN 50

#include <linux/timex.h>

#define BILLION (1000000000)
#define MILLION (1000000)
#define THOUSANDS (1000)

extern char apriori_paging_process[CONFIG_NR_CPUS][MAX_PROC_NAME_LEN];

extern unsigned char enable_dump_stack;
int is_process_of_apriori_paging(const char* proc_name);
extern unsigned char enable_mmap_prints;

#define ep_print(...) if (enable_mmap_prints) \
							pr_err(__VA_ARGS__)


/* All three macros assume that time is give in nano seconds */
#define IN_SECONDS(time)  ((double(time)) / (double(BILLION)))

#define IN_MICROSECS(time)  ((double(time)) / (double(MILLION)))

#define IN_MICROSECS(time)  ((double(time)) / (double(MILLION)))

/*
inline void get_current_time() {
	unsigned long int time = 0;
	struct timespec tv;

	if (time == NULL) {
		return;
	}

	getnstimeofday(&tv);

	return ((tv.tv_sec * BILLION) + tv.tv_nsec);
}
*/
#endif
