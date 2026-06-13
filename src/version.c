#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "version.h"


char *read_version(char *buf, size_t buf_size) {
    FILE *f = fopen("VERSION", "r");

    if (!f) {
        fprintf(stderr, "Failed to read file \"VERSION\": %s\n", strerror(errno));
        return NULL;
    }

    fgets(buf, buf_size, f);
    fclose(f);
    return buf;
}
