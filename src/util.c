#include <math.h>
#include <stdbool.h>
#include "include/util.h"

int util_rnd_number(int min, int max)
{
    return rand() % ((max + 1) - min) + min;
}

bool util_rectangles_overlap(int rect_1_start_x, int rect_1_end_x, int rect_1_start_y, int rect_1_end_y,
                             int rect_2_start_x, int rect_2_end_x, int rect_2_start_y, int rect_2_end_y)
{
    if (rect_1_start_x >= rect_2_end_x || rect_1_end_x <= rect_2_start_x) {
        return false;
    }

    if (rect_1_start_y >= rect_2_end_y || rect_1_end_y <= rect_2_start_y) {
        return false;
    }

    return true;
}