#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <windows.h>
#include <tchar.h>

#include "version.h"
#include "config.h"
#include "tasks.h"
#include "files.h"


int main(int argc, char *argv[]) {
    int opt;
    int task = 0;
    Config cfg = {0};
    
    while((opt = getopt(argc, argv, "hvt")) != -1) {
        switch (opt) {
            case 'h': printf("Wallpapers - utility for changing your wallpapers\nusage: wallpapers [-h] [-v]\n"); return 0;
            case 'v': { 
                char version[32];
                printf("%s", read_version(version, sizeof(version)) ? version : "Unknown");
            }
            case 't': {
                task = 1;
                break;
            }
            return 0;
            break;
        }
    }
    
    if (!read_config(&cfg)) {
        printf("[DEBUG] main.c -> Failed to read config. Creating default file \"config.ini\"\n");
        if (create_default_config(&cfg) != 0) {
            fprintf(stderr, "Failed to create default config file\n");
            return 1;
        }
        printf("[DEBUG] main.c -> Successfully created \"config.ini\"\n");
    }

    if (task != 0) {
        printf("[DEBUG] main.c -> Setting up windows scheduler task\n");
        create_windows_scheduler_task("Wallpapers changing", cfg.exe_path, NULL, NULL, &cfg);
        return 0;
    }
    
    if (cfg.source[0] == '\0') {
        printf("Enter path to images: ");
        fgets(cfg.source, sizeof(cfg.source), stdin);
    }
    
    printf("[DEBUG] main.c -> Using \"%s\" as source\n", cfg.source);

    // Select image for background 
    char image_path[MAX_PATH];
    
    int files_count = count_files_in_directory(cfg.source);
    printf("[DEBUG] main.c -> Files count: %d\n", files_count);
    
    char *images[files_count];
    read_images(&cfg, images);
    
    switch (cfg.strategy) {
        case STATIC: {
            printf("[DEBUG] main.c -> Selected \"static\" mode. Background image not changed\n"); 
            return 0;
        }
        case ROUND_ROBIN: {
            select_next_image(images, files_count, image_path, sizeof(image_path));
            break;
        }
        case RANDOM: {
            select_random_image(cfg.source, images, files_count, image_path, sizeof(image_path)); 
            break;
        }
        default: return 0;
    }

    printf("[DEBUG] main.c -> Using \"%s\" as background image\n", image_path);

    // Change background
    int success = SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)image_path, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

    if (!success) {
        printf("Failed to set background image via path: %s\n", image_path);
        return 1;
    }
    return 0;
}
