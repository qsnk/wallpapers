#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tasks.h"


int windows_create_scheduler_task(const char *name, const char *exec_path, const char *exec_args, ScheduleType type, int interval) {
    char command[2048];
    char sch_type_buff[50];

    switch (type) {
        case MINUTE:  snprintf(sch_type_buff, sizeof(sch_type_buff), "MINUTE"); break;
        case HOURLY:  snprintf(sch_type_buff, sizeof(sch_type_buff), "HOURLY"); break;
        case DAILY:   snprintf(sch_type_buff, sizeof(sch_type_buff), "DAILY"); break;
        case WEEKLY:  snprintf(sch_type_buff, sizeof(sch_type_buff), "WEEKLY"); break;
        case MONTHLY: snprintf(sch_type_buff, sizeof(sch_type_buff), "MONTHLY"); break;
        default: return 1;
    }

    if (interval != 0) {
        snprintf(sch_type_buff + strlen(sch_type_buff), sizeof(sch_type_buff) - strlen(sch_type_buff), "/mo %d", interval);
    }
    
    snprintf(command, sizeof(command), "schtasks /create /tn \"%s\" /tr \"\\\"%s\\\" %s\" /sc %s /f", name, exec_path, exec_args, sch_type_buff);
    printf("[DEBUG] tasks.c -> Registering scheduled task %s in Windows Task Scheduler...\n", name);    
    return system(command);
}
