#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"


static char *trim(char *s) {
    char *end;
    while (*s && isspace((unsigned char)*s)) s++;
    if (*s == 0) return s;
    end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) *end-- = '\0';
    return s;
}

Config *read_config(Config *cfg) {
    printf("[DEBUG] config.c -> Reading \"config.ini\"\n");
    
    FILE *f = fopen("config.ini", "r");

    if (!f) return NULL;

    char buf[1024];

    while (fgets(buf, sizeof(buf), f)) {
        buf[strcspn(buf, "\r\n")] = '\0';
        char *eq = strchr(buf, '=');
        if (!eq) continue;
    
        *eq = '\0';
        char *param = trim(buf);
        char *value = trim(eq + 1);
        if (!*param) continue;

        if (strcmp(param, "strategy")  == 0) {
            if (strcmp(value, "1")      == 1) cfg->strategy = STATIC;
            else if (strcmp(value, "2") == 2) cfg->strategy = ROUND_ROBIN;
            else if (strcmp(value, "3") == 3) cfg->strategy = RANDOM;
            else {}
        } else if (strcmp(param, "type")  == 0) {
            if (strcmp(value, "1")      == 0) cfg->type = MINUTE;
            else if (strcmp(value, "2")      == 0) cfg->type = HOURLY;
            else if (strcmp(value, "3") == 0) cfg->type = DAILY;
            else if (strcmp(value, "4") == 0) cfg->type = WEEKLY;
            else if (strcmp(value, "5") == 0) cfg->type = MONTHLY;
            else {}
        } else if (strcmp(param, "interval") == 0) {
            cfg->interval = (int)strtol(value, NULL, 10);
        } else if (strcmp(param, "source")     == 0) { 
            snprintf(cfg->source, sizeof(cfg->source), "%s", value);
        } else continue;
    }

    fclose(f);
    return cfg;
}


int write_config(Config *cfg) {
    FILE *f = fopen("config.ini", "w");

    if (!f) {
        fprintf(stderr, "Failed to open \"config.ini\" file\n");
        return 1;
    }
    
    fprintf(f, "[settings]\n");
    fprintf(f, "strategy = %d\n", cfg->strategy);
    fprintf(f, "type = %d\n", cfg->type);
    fprintf(f, "interval = %d\n", cfg->interval);
    fprintf(f, "source = \"%s\"\n", cfg->source);
    fclose(f);
    return 0;
}