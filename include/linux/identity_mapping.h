#ifndef __IDENTITY_MAPPING_H__
#define __IDENTITY_MAPPING_H__

#define MAX_PROC_NAME_LEN 16

<<<<<<< HEAD
char identity_mapping_process[CONFIG_NR_CPUS][MAX_PROC_NAME_LEN];

=======
char identity_mapping_process_testing[CONFIG_NR_CPUS][MAX_PROC_NAME_LEN];
char identity_mapping_process_stable[CONFIG_NR_CPUS][MAX_PROC_NAME_LEN];
int start_tracking = 0;
>>>>>>> 0b79b7e023a8dc682e37f825b38b50926d9d5700
int is_process_of_identity_mapping(const char* proc_name);

#endif
