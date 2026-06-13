#ifndef CONFIG_H
#define CONFIG_H

typedef enum ChangeStrategy {
    STATIC      = 1,
    ROUND_ROBIN = 2,
    RANDOM      = 3,
} ChangeStrategy;

typedef enum ScheduleType {
    MINUTE  = 1, 
    HOURLY  = 2, 
    DAILY   = 3,
    WEEKLY  = 4,
    MONTHLY = 5
} ScheduleType;

typedef struct Config {
    int interval;
    ChangeStrategy strategy;
    ScheduleType type;
    char source[4096];
    
} Config;

Config *read_config(Config *cfg); 
int write_config(Config *cfg);

#endif
