#include "flood_fill.h"
#include <stdbool.h>
#include <stdlib.h>

#include "util.h"

// Compare two pixels
bool pixel_equal(pixel_t *pixel1, pixel_t *pixel2) {
    return pixel1->r == pixel2->r && pixel1->g == pixel2->g && pixel1->b == pixel2->b;
}

// Recursive function to perform the flood-fill
void flood_fill(image_t *img, int x, int y, pixel_t target_color, pixel_t original_color) {
    // Base case: If the pixel is out of bounds or is not the original color, return
    if (x < 0 || y < 0 || x >= img->w || y >= img->h || !pixel_equal(&img->img[y * img->w + x], &original_color)) {
        return;
    }

    // Set the color of the pixel to the target color
    img->img[y * img->w + x] = target_color;

    // Recurse on the neighboring pixels
    flood_fill(img, x + 1, y, target_color, original_color);
    flood_fill(img, x - 1, y, target_color, original_color);
    flood_fill(img, x, y + 1, target_color, original_color);
    flood_fill(img, x, y - 1, target_color, original_color);
}

void flood(image_t *img, int x, int y, pixel_t *target_color) {
    if (x < 0 || y < 0 || x >= img->w || y >= img->h) return;

    // Get the original color of the pixel at (x, y)
    pixel_t original_color = img->img[y * img->w + x];

    // If the target color is the same as the original color, there's nothing to do
    if (pixel_equal(&original_color, target_color)) {
        return;
    }

    // Perform the flood-fill
    flood_fill(img, x, y, *target_color, original_color);
}