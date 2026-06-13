#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <windows.h>
#include <tchar.h>

#include "version.h"
#include "config.h"


#if defined (__linux__)
    #define PLATFORM "Linux"
#elif defined (_WIN32)
    #define PLATFORM "Windows"
#elif defined (MACOSX)
    #define PLATFORM "MacOS"
#else
    #define PLATFORM "Other"
#endif


char *select_random_image(Config *cfg, char *image_path, size_t image_path_size) {
    time_t timestamp = time(NULL); 
    srand(timestamp);
    
    DIR *dir = opendir(cfg->source);

    if (!dir) {
        fprintf(stderr, "Failed to read directory \"%s\"\n", image_path);
        return NULL;
    }
    
    struct dirent *ent;
    int files_size = 0;
    
    while ((ent = readdir(dir)) != NULL ) {
        if (ent->d_name[0] == '.') continue;
        files_size++;

        if (rand() % files_size == 0) {
            snprintf(image_path, image_path_size, cfg->source[strlen(cfg->source) - 1] != '\\' ? "%s\\%s" : "%s%s", cfg->source, ent->d_name);
        }
    }

    closedir(dir);
    return image_path;
}


int main(int argc, char *argv[]) {
    int opt;
    
    while((opt = getopt(argc, argv, "hv")) != -1) {
        switch (opt) {
            case 'h': printf("Wallpapers - utility for changing your wallpapers\nusage: wallpapers [-h] [-v]\n"); return 0;
            case 'v': { 
                char version[32];
                printf("%s", read_version(version, sizeof(version)) ? version : "Unknown");
            }
            return 0;
            break;
        }
    }

    Config cfg = {0};
    
    if (!read_config(&cfg)) {
        printf("[DEBUG] main.c -> Failed to read config. Creating default file \"config.ini\"\n");
        cfg.strategy = RANDOM;
        cfg.type = HOURLY;
        cfg.interval = 1;
        strcpy(cfg.source, "");
        if (write_config(&cfg) != 0) return 1;
        printf("[DEBUG] main.c -> Successfully created \"config.ini\"\n");
    }

    if (cfg.source[0] == '\0') {
        printf("Enter path to images: ");
        fgets(cfg.source, sizeof(cfg.source), stdin);
    }
    
    printf("[DEBUG] main.c -> Using \"%s\" as source\n", cfg.source);

    // Select image for background 
    char image_path[4096];
    select_random_image(&cfg, image_path, sizeof(image_path));

    printf("[DEBUG] main.c -> Using \"%s\" as background image\n", image_path);

    // Change background
    int success = SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)image_path, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

    if (!success) {
        printf("Failed to set background image via path: %s\n", image_path);
        return 1;
    }
    return 0;
}
