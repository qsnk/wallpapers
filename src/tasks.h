#ifndef TASKS_H
#define TASKS_H
#include "config.h"

int windows_create_scheduler_task(const char *name, const char *exec_path, const char *exec_args, ScheduleType type, int interval);
int linux_create_cron_job();
int macos_create_cron_job();

#endif
