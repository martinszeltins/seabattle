#ifndef __UTIL_H__
#define __UTIL_H__

int util_rnd_number(int min, int max);

bool util_rectangles_overlap(int rect_1_start_x, int rect_1_end_x, int rect_1_start_y, int rect_1_end_y,
                             int rect_2_start_x, int rect_2_end_x, int rect_2_start_y, int rect_2_end_y);

#endif