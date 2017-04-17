#ifndef __APRIORI_PAGING_ALLOC_H__
#define __APRIORI_PAGING_ALLOC_H__

#define MAX_PROC_NAME_LEN 50

extern char apriori_paging_process[CONFIG_NR_CPUS][MAX_PROC_NAME_LEN];

extern unsigned char enable_dump_stack;
int is_process_of_apriori_paging(const char* proc_name);
extern unsigned char enable_mmap_prints;

#define ep_mmap_print(...) if (enable_mmap_prints) \
							pr_err(__VA_ARGS__)

#endif
