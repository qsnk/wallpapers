#ifndef TASKS_H
#define TASKS_H

#include "config.h"

int create_windows_scheduler_task(const char *name, const char *exec_path, const char *exec_args, const char *work_directory, Config *cfg);
int create_linux_cron_job(void);
int create_macos_cron_job(void);

#endif
