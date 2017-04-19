#ifndef __APRIORI_PAGING_ALLOC_H__
#define __APRIORI_PAGING_ALLOC_H__

#define MAX_PROC_NAME_LEN 50

#include <linux/time.h>
//#include <linux/timekeeping.h>

#define BILLION (1000000000)
#define MILLION (1000000)
#define THOUSANDS (1000)

extern char apriori_paging_process[CONFIG_NR_CPUS][MAX_PROC_NAME_LEN];

extern unsigned char enable_dump_stack;
extern unsigned char enable_prints;

int is_process_of_apriori_paging(const char* proc_name);
long get_current_time(void);

#define ep_print(...) if (enable_prints) \
							pr_err(__VA_ARGS__)


#define ep_dump_stack() if (enable_dump_stack) \
							dump_stack()

/* All three macros assume that time is give in nano seconds */
#define IN_SECONDS(time)  ((double(time)) / (double(BILLION)))

#define IN_MICROSECS(time)  ((double(time)) / (double(MILLION)))

#define IN_MICROSECS(time)  ((double(time)) / (double(MILLION)))


typedef struct eager_paging_statistics {
	char process_name[MAX_PROC_NAME_LEN]; /* Name of the process */
	unsigned long kernel_time;  /* Amount of time spent in kernel for allocation */
	unsigned long kernel_entry; /* Number of time we entered kernel for allocation */
} ep_stats_t;

#endif
