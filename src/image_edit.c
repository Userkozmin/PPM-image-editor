#include "image_edit.h"

#include <stdlib.h>

#include "util.h"

void rotate_counterclockwise(image_t *img) {
    int old_width = img->w, old_height = img->h;
    pixel_t *old_img = img->img;

    img->w = old_height;
    img->h = old_width;
    img->img = (pixel_t *)malloc(sizeof(pixel_t) * img->w * img->h);
    if (img->img == NULL) {
        free(old_img);
        return;
    }

    for (int i = 0; i < old_height; i++) {
        for (int j = 0; j < old_width; j++) {
            img->img[(old_width - 1 - j) * img->w + i] = old_img[i * old_width + j];
        }
    }

    free(old_img);
}

void rotate_clockwise(image_t *img) {
    int old_width = img->w, old_height = img->h;
    pixel_t *old_img = img->img;

    img->w = old_height;
    img->h = old_width;
    img->img = (pixel_t *)malloc(sizeof(pixel_t) * img->w * img->h);
    if (img->img == NULL) {
        free(old_img);
        return;
    }

    for (int i = 0; i < old_height; i++) {
        for (int j = 0; j < old_width; j++) {
            img->img[j * img->w + (old_height - 1 - i)] = old_img[i * old_width + j];
        }
    }

    free(old_img);
}

void mirror_horizontal(image_t *img) {
    pixel_t temp;

    for (int i = 0; i < img->h; i++) {
        for (int j = 0; j < img->w / 2; j++) {
            temp = img->img[i * img->w + j];
            img->img[i * img->w + j] = img->img[i * img->w + (img->w - 1 - j)];
            img->img[i * img->w + (img->w - 1 - j)] = temp;
        }
    }
}

void mirror_vertical(image_t *img) {
    pixel_t temp;

    for (int i = 0; i < img->h / 2; i++) {
        for (int j = 0; j < img->w; j++) {
            temp = img->img[i * img->w + j];
            img->img[i * img->w + j] = img->img[(img->h - 1 - i) * img->w + j];
            img->img[(img->h - 1 - i) * img->w + j] = temp;
        }
    }
}

void resize(image_t *img, int new_width, int new_height) {
    int i, j;
    pixel_t *new_img = (pixel_t *)malloc(sizeof(pixel_t) * new_width * new_height);
    if (new_img == NULL) {
        return;
    }

    // Fill the new image with black pixels
    for (i = 0; i < new_height; i++) {
        for (j = 0; j < new_width; j++) {
            new_img[i * new_width + j].r = 0;
            new_img[i * new_width + j].g = 0;
            new_img[i * new_width + j].b = 0;
        }
    }

    // Copy the old image into the new one
    int copy_width = new_width < img->w ? new_width : img->w;
    int copy_height = new_height < img->h ? new_height : img->h;
    for (i = 0; i < copy_height; i++) {
        for (j = 0; j < copy_width; j++) {
            new_img[i * new_width + j] = img->img[i * img->w + j];
        }
    }

    // Update the image data
    free(img->img);
    img->img = new_img;
    img->w = new_width;
    img->h = new_height;
}


