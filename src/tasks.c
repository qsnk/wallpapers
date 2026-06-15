#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tasks.h"


int create_windows_scheduler_task(const char *name, const char *exec_path, const char *exec_args, const char *work_directory, Config *cfg) {
    char command[2048]      = {0};
    char exec_buff[1024]    = {0};
    char sch_type_buff[50]  = {0};

    switch (cfg->type) {
        case MINUTE:  snprintf(sch_type_buff, sizeof(sch_type_buff), "MINUTE");  break;
        case HOURLY:  snprintf(sch_type_buff, sizeof(sch_type_buff), "HOURLY");  break;
        case DAILY:   snprintf(sch_type_buff, sizeof(sch_type_buff), "DAILY");   break;
        case WEEKLY:  snprintf(sch_type_buff, sizeof(sch_type_buff), "WEEKLY");  break;
        case MONTHLY: snprintf(sch_type_buff, sizeof(sch_type_buff), "MONTHLY"); break;
        default: return 1;
    }

    if (cfg->interval != 0) {
        snprintf(sch_type_buff + strlen(sch_type_buff), sizeof(sch_type_buff) - strlen(sch_type_buff), " /mo %d", cfg->interval);
    }
    
    if (exec_args != NULL) {
        snprintf(exec_buff, sizeof(exec_buff), "\"%s %s\"", exec_path, exec_args);
    } else {
        snprintf(exec_buff, sizeof(exec_buff), "\"%s\"", exec_path);
    }
    
    snprintf(command, sizeof(command), "schtasks /create /tn \"%s\" /tr %s /sc %s /f", name, exec_buff, sch_type_buff);

    // snprintf(command, sizeof(command),
    //     "schtasks /create /tn \"%s\" "
    //     "/tr \"cmd /c cd /d \\\"%s\\\" && \\\"%s\\\"\" "
    //     "/sc %s /f",
    //     name,
    //     work_directory,
    //     exec_buff,
    //     sch_type_buff);
    
    printf("[DEBUG] tasks.c -> Registering scheduled task in Windows Task Scheduler\n");    
    return system(command);
}

int create_linux_cron_job(void) { return 0; }
int create_macos_cron_job(void) { return 0; }
