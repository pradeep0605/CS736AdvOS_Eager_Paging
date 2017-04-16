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

asmlinkage long sys_test_syscall(void) {
}

// asmlinkage long sys_list_ep_apps(void) {
asmlinkage long sys_list_ep_apps(void) {
	pr_err("\n\n======================\npr_err: Inside system calls (%s)"
		"\n============================\n\n", __func__);
	
	int i = 0;
	pr_err("\n\n =================== Listing all Eager Paging Enabled"
		"pplications =========================\n");
    for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ ) {
		if (apriori_paging_process[i][0] == '\0') {
			break;
		}
		pr_err("%s\n", apriori_paging_process[i]);
    }
	return 0xdeadbeef;
}

asmlinkage long sys_clear_ep_apps_list(void) {
	pr_err("\n\n======================\npr_err: Inside system calls (%s)"
		"\n============================\n\n", __func__);

	int i = 0;
	pr_err("\n\n =================== Clearing all Eager Paging Enabled"
		"pplications =========================\n");
    for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ ) {
		if (apriori_paging_process[i][0] != '\0') {
			pr_err("%s\n", apriori_paging_process[i]);
			apriori_paging_process[i][0] = '\0';
		}
	}

	return 0xdeadbeef;
}


SYSCALL_DEFINE3(apriori_paging_alloc, const char __user**, proc_name, unsigned int, num_procs, int, option)
{
    unsigned int i;
    char *temp;
    char proc[MAX_PROC_NAME_LEN];
    unsigned long ret = 0;

    struct task_struct *tsk;
    unsigned long pid;

	
	printk(KERN_ALERT "\n\n======================\nInside system calls (%s)"
		"\n============================\n\n", __func__);
    if ( option > 0 ) {
        for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ ) {
            if ( i < num_procs )
                ret = strncpy_from_user(proc, proc_name[i], MAX_PROC_NAME_LEN);
            else
                temp = strncpy(proc,"",MAX_PROC_NAME_LEN);
            temp = strncpy(apriori_paging_process[i], proc, MAX_PROC_NAME_LEN-1);
        }
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


    return 0;
}

/*
 * This function checks whether a process name provided matches from the list
 *
 */

int is_process_of_apriori_paging(const char* proc_name)
{

    unsigned int i;

    for ( i = 0 ; i < CONFIG_NR_CPUS ; i++ )     {
        if (!strncmp(proc_name,apriori_paging_process[i],MAX_PROC_NAME_LEN))
            return 1;
    }

    return 0;
}
