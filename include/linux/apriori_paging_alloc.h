#ifndef __APRIORI_PAGING_ALLOC_H__
#define __APRIORI_PAGING_ALLOC_H__

#define MAX_PROC_NAME_LEN 50

char apriori_paging_process[CONFIG_NR_CPUS][MAX_PROC_NAME_LEN];

int is_process_of_apriori_paging(const char* proc_name);

#endif
