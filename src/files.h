#ifndef FILES_H
#define FILES_H

#include "config.h"


int count_files_in_directory(const char *path);
int read_images(Config *cfg, char *buf[]);
int get_image_index(char *images[], int images_count, const char *image);
const char *select_random_image(const char *base_path, char *images[], int images_count, char *image_path, size_t image_path_size);
const char *select_next_image(char *images[], int images_count, char *image_path, size_t image_path_size);

#endif
