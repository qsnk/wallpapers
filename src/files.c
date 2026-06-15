#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>

#include "files.h"


int count_files_in_directory(const char *path) {
    DIR *dir = opendir(path);

    if (!dir) {
        fprintf(stderr, "Failed to open directory \"%s\"\n", path);
        return 0;
    }
    
    struct dirent *ent;
    int counter = 0;
    
    while ((ent = readdir(dir)) != NULL ) {
        if (ent->d_name[0] == '.') continue;
        counter++;
    }

    closedir(dir);
    return counter;
}

int read_images(Config *cfg, char *buf[]) {
    DIR *dir = opendir(cfg->source);

    if (!dir) {
        fprintf(stderr, "Failed to open directory \"%s\"\n", cfg->source);
        return 0;
    }
    
    struct dirent *ent;
    int index = 0;
    
    while ((ent = readdir(dir)) != NULL ) {
        if (ent->d_name[0] == '.') continue;
        const char *sep = cfg->source[strlen(cfg->source) - 1] == '\\' ? "" : "\\";
        int needed = snprintf(NULL, 0, "%s%s%s", cfg->source, sep, ent->d_name) + 1;
        char *s = malloc(needed);
        if (!s) break;
        snprintf(s, needed, "%s%s%s", cfg->source, sep, ent->d_name);
        buf[index++] = s;
    }

    closedir(dir);
    return index;
}

int get_image_index(char *images[], int images_count, const char *image) {
    if (!images || !image) return -1;
    for (int i = 0; i < images_count; i++) {
        if (!images[i]) continue;
        
        if (strcmp(images[i], image) == 0) {
            return i;
        }
    }
    return -1;
}

const char *select_random_image(const char *base_path, char *images[], int images_count, char *image_path, size_t image_path_size) {
    printf("[DEBUG] files.c -> Selecting random image as background\n");

    time_t timestamp = time(NULL); 
    int remainder;
    srand(timestamp);

    do {
        remainder = rand() % images_count;
    } while (remainder < 0 || remainder >= images_count);
    
    snprintf(image_path, image_path_size, "%s", images[remainder]);
    return image_path;
}

const char *select_next_image(char *images[], int images_count, char *image_path, size_t image_path_size) {
    printf("[DEBUG] files.c -> Selecting next image as background\n");

    if (!images || images_count <= 0 || !image_path || image_path_size == 0) return NULL;

    wchar_t current_wpath[MAX_PATH];
    if (!SystemParametersInfoW(SPI_GETDESKWALLPAPER, MAX_PATH, current_wpath, 0)) return NULL;
    if (wcsnlen_s(current_wpath, MAX_PATH) == 0) {
        printf("[DEBUG] files.c -> No wallpaper image is set (it might be a solid color)\n");
        snprintf(image_path, image_path_size, "%s", images[0]);
        return NULL;
    }

    int needed = WideCharToMultiByte(CP_UTF8, 0, current_wpath, -1, NULL, 0, NULL, NULL);
    if (needed <= 0) return NULL;

    char *cur_path_utf8 = NULL;
    char stack_buf[1024];
    if ((size_t)needed <= sizeof(stack_buf)) {
        if (WideCharToMultiByte(CP_UTF8, 0, current_wpath, -1, stack_buf, (int)sizeof(stack_buf), NULL, NULL) == 0)
            return NULL;
        cur_path_utf8 = stack_buf;
    } else {
        cur_path_utf8 = (char *)malloc((size_t)needed);
        if (!cur_path_utf8) return NULL;
        if (WideCharToMultiByte(CP_UTF8, 0, current_wpath, -1, cur_path_utf8, needed, NULL, NULL) == 0) {
            free(cur_path_utf8);
            return NULL;
        }
    }

    int current_index = get_image_index(images, images_count, cur_path_utf8);

    if ((char *)cur_path_utf8 != stack_buf) free(cur_path_utf8);

    if (current_index < 0) {
        printf("[DEBUG] files.c -> Current background image not found in source directory. Using first image as background image\n");
        snprintf(image_path, image_path_size, "%s", images[0]);
        return images[0];
    }

    int next = (current_index + 1) % images_count;
    if (snprintf(image_path, image_path_size, "%s", images[next]) < 0) return NULL;
    
    image_path[image_path_size - 1] = '\0';
    return images[next];
}
