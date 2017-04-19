#include <linux/apriori_paging_alloc.h>
#include <linux/syscalls.h>

/*
 * !!_AprioriPaging_!!
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
 *
 */

/* ALL golbals here */
char apriori_paging_process[CONFIG_NR_CPUS][MAX_PROC_NAME_LEN];
unsigned char enable_dump_stack;
unsigned char enable_prints;



int indexof_apriori_paged_process(const char* proc_name);

asmlinkage long sys_ep_control_syscall(int val) {

	pr_err("\n======================Inside system calls (%s)"
		"============================", __func__);

	switch (val) {
		case 1:
			enable_dump_stack = 1;
			pr_err("EP: Enabled stack dump");
			break;
		case -1:
			enable_dump_stack = 0;
			pr_err("EP: Disabled stack dump");
			break;

		case 2:
			enable_prints = 1;
			pr_err("EP: Enabled mmap prints");
			break;
		case -2:
			enable_prints = 0;
			pr_err("EP: disabled mmap prints");
			break;
	}
	return 0;
}

// asmlinkage long sys_list_ep_apps(void) {
asmlinkage long sys_list_ep_apps() {
	pr_err("\n====================== Inside system calls (%s)"
		"============================", __func__);
	
		int i = 0;
		pr_err(" =================== Listing all Eager Paging Enabled"
			"pplications =========================\n");
		for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ ) {
			if (apriori_paging_process[i][0] != '\0') {
				pr_err("%s\n", apriori_paging_process[i]);
			}
		}
	return 0xdeadbeef;
}

asmlinkage long sys_clear_ep_apps_list(const char __user* process_name) {
	pr_err("\n======================Inside system calls (%s)"
		"============================", __func__);

	int i = 0;
	pr_err("\n\n =================== Clearing all Eager Paging Enabled"
		"pplications =========================\n");
	if (process_name == NULL) {
		for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ ) {
			if (apriori_paging_process[i][0] != '\0') {
				pr_err("%s\n", apriori_paging_process[i]);
				apriori_paging_process[i][0] = '\0';
			}
		}
	} else {
		int ret = indexof_apriori_paged_process(process_name);
		if (ret != -1) {
			apriori_paging_process[ret][0] = '\0';
		} else {
			pr_err("Application name %s not found in the list\n", process_name);
		}
	}
	
	sys_list_ep_apps();
	return 0xdeadbeef;
}


SYSCALL_DEFINE3(apriori_paging_alloc, const char __user**, proc_name, unsigned int, num_procs, int, option)
{
    unsigned int i = 0;
    char *temp;
    char proc[MAX_PROC_NAME_LEN];
    unsigned long ret = 0;

    struct task_struct *tsk;
    unsigned long pid;

	
	printk(KERN_ALERT "\n\n======================\nInside system calls (%s)"
		"\n============================\n\n", __func__);
    if ( option > 0 ) {
		i = 0;
		if (num_procs == 1) {
			while(apriori_paging_process[i][0] != '\0') {
				i++;
			}
			
			ret = strncpy_from_user(apriori_paging_process[i], proc_name[0],
				MAX_PROC_NAME_LEN);
		}
		/*
        for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ ) {
            if ( i < num_procs )
                ret = strncpy_from_user(proc, proc_name[i], MAX_PROC_NAME_LEN);
            else
                temp = strncpy(proc,"",MAX_PROC_NAME_LEN);
            temp = strncpy(apriori_paging_process[i], proc, MAX_PROC_NAME_LEN-1);
        }
		*/
    }

    if ( option < 0 ) {
        for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ ) {
            if( i < num_procs ) {
                ret = kstrtoul(proc_name[i],10,&pid);
                if ( ret == 0 ) {
                    tsk = find_task_by_vpid(pid);
                    tsk->mm->apriori_paging_en = 1;
                }
            }
        }
    }

    return ret;
}

/*
 * This function checks whether a process name provided matches from the list
 *
 */

int indexof_apriori_paged_process(const char* proc_name)
{
    unsigned int i;
    for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ )     {
        if (!strncmp(proc_name, apriori_paging_process[i], MAX_PROC_NAME_LEN))
            return i;
    }

    return -1;
}

int is_process_of_apriori_paging(const char* proc_name)
{
    unsigned int i;
    for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ )     {
        if (!strncmp(proc_name, apriori_paging_process[i], MAX_PROC_NAME_LEN))
            return 1;
    }

    return 0;
}
