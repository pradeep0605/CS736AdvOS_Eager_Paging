#include <linux/identity_mapping.h>
#include <linux/syscalls.h>

/* Identity Mapping
 * !!!!
 * This system has two functionalities depending on the value of the option variable
 *
 * if ( option > 0 )
 * It will take the process name as an argument and
 * every process which will be created with
 * this name will use our allocation mechanism
 *
 * if ( option < 0 )
 * It will take the pid as an argument and will force the process that has
 * this pid to use our allocation mechanism
 * option < 0 is useless as we want the segments to be randomized at elf loading time
 */

SYSCALL_DEFINE3(init_identity_map, const char __user**, proc_name, unsigned int, num_procs, int, option)
{
    unsigned int i;
    char *temp;
    char proc[MAX_PROC_NAME_LEN];
    unsigned long ret = 0;

    struct task_struct *tsk;
    unsigned long pid;


<<<<<<< HEAD
    if ( option > 0 ) {
=======
    if ( option == 1 ) {
	start_tracking = 1;
>>>>>>> 0b79b7e023a8dc682e37f825b38b50926d9d5700
        for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ ) {
            if ( i < num_procs )
                ret = strncpy_from_user(proc, proc_name[i], MAX_PROC_NAME_LEN);
            else
                temp = strncpy(proc,"",MAX_PROC_NAME_LEN);
<<<<<<< HEAD
            temp = strncpy(identity_mapping_process[i], proc, MAX_PROC_NAME_LEN-1);
=======
            temp = strncpy(identity_mapping_process_stable[i], proc, MAX_PROC_NAME_LEN-1);
        }
    }
    else if ( option > 1 ) {
	    start_tracking = 1;
	    for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ ) {
            if ( i < num_procs )
                ret = strncpy_from_user(proc, proc_name[i], MAX_PROC_NAME_LEN);
            else
                temp = strncpy(proc,"",MAX_PROC_NAME_LEN);
            temp = strncpy(identity_mapping_process_testing[i], proc, MAX_PROC_NAME_LEN-1);
>>>>>>> 0b79b7e023a8dc682e37f825b38b50926d9d5700
        }
    }

    if ( option < 0 ) {
        for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ ) {
            if( i < num_procs ) {
                ret = kstrtoul(proc_name[i],10,&pid);
                if ( ret == 0 ) {
                    tsk = find_task_by_vpid(pid);
                    tsk->mm->identity_mapping_en = 1;
                }
            }
        }
    }

 
    printk("Identity Mapping enabled!\n");
    return 0;
}

/*
 * This function checks whether a process name provided matches from the list
 *
 */

<<<<<<< HEAD
int is_process_of_identity_mapping(const char* proc_name)
{

    unsigned int i;

    for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ )     {
        if (!strncmp(proc_name,identity_mapping_process[i],MAX_PROC_NAME_LEN))
=======
int is_process_of_identity_mapping_stable(const char* proc_name)
{

    unsigned int i;
	
    if (start_tracking == 0)
	return 0;

    for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ )     {
        if (!strncmp(proc_name,identity_mapping_process_stable[i],MAX_PROC_NAME_LEN))
            return 1;
    }

    return 0;
}

int is_process_of_identity_mapping_testing(const char* proc_name)
{

    unsigned int i;
	
    if (start_tracking == 0)
	return 0;

    for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ )     {
        if (!strncmp(proc_name,identity_mapping_process_testing[i],MAX_PROC_NAME_LEN))
>>>>>>> 0b79b7e023a8dc682e37f825b38b50926d9d5700
            return 1;
    }

    return 0;
}
